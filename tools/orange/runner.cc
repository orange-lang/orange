/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/
#include <orange/runner.h>
#include <orange/generator.h>
#include <orange/OrangeTypes.h>

#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/MC/SubtargetFeature.h>
#include <llvm/CodeGen/Passes.h>
#include <llvm/Support/FormattedStream.h>
#include <llvm/Transforms/IPO/InlinerPass.h>
#include <llvm/Transforms/IPO.h>
#include <llvm/Transforms/Vectorize.h>
#include <llvm/Transforms/Utils/UnifyFunctionExitNodes.h>
#include <llvm/Analysis/Passes.h>

void Runner::init() {
	bool added = GeneratingEngine::sharedEngine()->addRunner(this);

	m_context = new LLVMContext();
	GeneratingEngine::sharedEngine()->setActive(this);

	// Create the global block
	SymTable *globalSymtab = new SymTable(true);
	m_function = new FunctionStmt("__INTERNAL_main", IntTy::getSigned(64), ParamList(), globalSymtab);
	m_function->disableMangle();
	pushBlock(m_function);

	// Create LLVM stuff; module, builder, etc
	m_module = new Module("orange", context());

	std::string triple = sys::getProcessTriple();

	#ifdef _WIN32
		// This is required to run JIT on windows
		triple += "-elf";
	#endif

	m_module->setTargetTriple(triple);

	m_builder = new IRBuilder<>(context());

	m_functionOptimizer = new FunctionPassManager(m_module);
	m_functionOptimizer->doInitialization();

	GeneratingEngine::sharedEngine()->setActive(nullptr);
}

Runner::Runner() {
	init();
}

Runner::Runner(std::string pathname) {
	m_pathname = pathname;

	init();
}

Runner::~Runner() {
	delete m_function;
	delete m_builder;
	delete m_context;
	delete m_functionOptimizer;
	delete m_module;
}

void Runner::setTarget(std::string filename) {
	m_pathname = filename;
}

void Runner::haltRun() {
	m_isRunning = false;
}

bool Runner::hasError() {
	for (auto msg : m_messages) {
		if (msg.type() == ERROR) return true;
	}

	return false;
}

void Runner::compile() {
	// First, set us to running and activate us as the current runner.
	m_isRunning = true;
	GeneratingEngine::sharedEngine()->setActive(this);

	// Try to find our file...
	FILE *file = fopen(pathname().c_str(), "r");
	if (file == nullptr) {
		// Halt our current run and return an error.
		haltRun();

		CompilerMessage msg(NO_FILE, "file " + pathname() + " not found.", pathname(), -1, -1, -1, -1);
		m_result = new RunResult(pathname(), false, 1, msg);
		return;
	}

	// Parse the file. get yyin and yyparse and use them
	extern FILE* yyin;
	extern int yyparse();
	extern int yyonce; // used to get the endline
	extern void yyflushbuffer();

	m_result = new BuildResult(pathname());
	m_result->start();

	try {
		yyflushbuffer(); // reset buffer
		yyonce = 0; // reset yyonce
		yyin = file; // give flex the file
		yyparse(); // and do our parse.

		// Analysis pass 
		mainFunction()->resolve();

		if (hasError()) {
			m_result->finish(false, m_messages);
			return;
		}

		if (debug()) {
			std::cout << mainFunction()->dump() << std::endl;
			std::cout << mainFunction()->string() << std::endl;
		}

		mainFunction()->Codegen();

		if (hasError()) {
			m_result->finish(false, m_messages);
			return;
		}

		if (debug())
			m_module->dump();

		optimizeModule();

		if (debug())
			m_module->dump();

		fclose(file);
	} catch (CompilerMessage& e) {
		std::cerr << "fatal: " << e.what() << std::endl;
		exit(1);
	} catch (std::runtime_error& e) {
		std::cerr << "fatal: " << e.what() << std::endl;
		exit(1);
	}
}

void Runner::build() {
	if (m_result == nullptr) {
		std::cerr << "fatal: program not compiled.\n";
		exit(1);
	}

	if (m_result->finished() == true) return;

	buildModule();

	m_isRunning = false;

	m_result->finish(hasError() == false, m_messages);
}

void Runner::run() {
	if (m_result == nullptr) {
		std::cerr << "fatal: program not compiled.\n";
		exit(1);
	}

	RunResult* new_result = new RunResult(*m_result);

	delete m_result;
	m_result = new_result;

	if (m_result->finished() == true) return;

	int retCode = hasError() == false ? runModule((Function *)mainFunction()->getValue()) : 1;

	// Do cleanup.
	m_isRunning = false;

	if (debug() && hasError() == false)
		std::cout << "Program returned " << retCode << std::endl;

	bool succeeded = (retCode == 0) && (hasError() == false);

	new_result->finish(succeeded, retCode, m_messages);
}

void Runner::buildModule() {
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();

	std::string err = "";
	Triple triple = Triple(m_module->getTargetTriple());

	auto target = TargetRegistry::lookupTarget(m_module->getTargetTriple(), err);
	if (target == nullptr) {
		throw std::runtime_error(err);
	}

	StringRef name = sys::getHostCPUName();
  SubtargetFeatures Features;

	Features.getDefaultSubtargetFeatures(triple);
	std::string FeaturesStr = Features.getString();

	TargetOptions options;

	TargetMachine *tm = target->createTargetMachine(triple.getTriple(), name, FeaturesStr, options, Reloc::Default, CodeModel::Default);

	if (tm == nullptr) {
		throw std::runtime_error("could not create target marchine.");
	}

	std::string loutput = sys::fs::directory_entry(pathname()).path();

#if defined(__linux__) || defined(__APPLE__)
		loutput += ".o";
#elif defined(_WIN32)
		loutput += ".obj";
#endif

	std::error_code ec;
	raw_fd_ostream raw(loutput.c_str(), ec, llvm::sys::fs::OpenFlags::F_RW);

	if (ec) {
		throw std::runtime_error(ec.message());
	}

	formatted_raw_ostream strm(raw);

  PassManager* ThePM = new PassManager;
	ThePM->add(new DataLayoutPass());

	bool b = tm->addPassesToEmitFile(*ThePM, strm, LLVMTargetMachine::CGFT_ObjectFile, false);

	if (b == true) {
		throw std::runtime_error("emission is not supported.\n");
	}

	ThePM->run(*m_module);
	strm.flush();
	raw.flush();
	raw.close();

	std::vector<const char *> voptions;

#if defined(__APPLE__) || defined(__linux__)
		std::string root = INSTALL_LOCATION;
		root += "/lib/libor/boot.o";

		voptions.push_back(root.c_str());

#ifdef __APPLE__
		voptions.push_back("-w");
#endif

#ifdef __linux__
		voptions.push_back("-I/lib64/ld-linux-x86-64.so.2");
#endif

		voptions.push_back("-lc");
		voptions.push_back("-o");
		voptions.push_back(m_output_name.c_str());

#elif defined(_WIN32)
		// This code needs some work
		voptions.push_back("-LC:/Windows/System32");
		voptions.push_back("-lmsvcrt");

		std::string root = "\"";
		root += INSTALL_LOCATION;
		root += "/lib/libor/boot.obj\"";

		voptions.push_back(root.c_str());

		voptions.push_back("-o");
		voptions.push_back(m_output_name.c_str());
#endif

		voptions.push_back(loutput.c_str());

		invokeLinkerWithOptions(voptions);

		remove(loutput.c_str());
}

int Runner::runModule(Function *function) {
	// MCJIT requires the target & asm printer to be initalized
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();

  // Create our builder & engine to run the function
	EngineBuilder builder((std::unique_ptr<Module>(m_module)));

	std::string error = "";

	ExecutionEngine* engine = builder
		.setErrorStr(&error)
		.setVerifyModules(true)
		.setEngineKind(EngineKind::Kind::JIT)
		.create();

	if (engine == nullptr) {
		std::cerr << "Fatal: could not create engine: " << error << std::endl;
		exit(1);
	}

	// MCJIT requires the engine to be finalized before running it.
	engine->clearAllGlobalMappings();
	engine->finalizeObject();

  std::vector<GenericValue> args;
  return engine->runFunction((Function *)function, args).IntVal.getSExtValue();
}

void Runner::optimizeModule() {
	static PassManager* MPM = nullptr;
	if (MPM == nullptr) {
		MPM = new PassManager;

		MPM->add(createVerifierPass(true));
		MPM->add(createUnreachableBlockEliminationPass());
		MPM->add(createGCLoweringPass());
		MPM->add(createAlwaysInlinerPass());
		MPM->add(createPruneEHPass());
		MPM->add(createIPConstantPropagationPass());
		MPM->add(createIPSCCPPass());
		MPM->add(createMergeFunctionsPass());
		MPM->add(createStripDeadPrototypesPass());
		MPM->add(createConstantPropagationPass());
		MPM->add(createAliasAnalysisCounterPass());
		MPM->add(createBasicAliasAnalysisPass());
		MPM->add(createLazyValueInfoPass());
		MPM->add(createDependenceAnalysisPass());
		MPM->add(createCostModelAnalysisPass());
		MPM->add(createDelinearizationPass());
		MPM->add(createInstCountPass());
		MPM->add(createInstructionCombiningPass());
		MPM->add(createInstructionSimplifierPass());
		MPM->add(createReassociatePass());
		MPM->add(createGVNPass());
		MPM->add(createCFGSimplificationPass());
		MPM->add(createBBVectorizePass());
		MPM->add(createCodeGenPreparePass());
		MPM->add(createGVNPass());
		MPM->add(createSinkingPass());
		MPM->add(createUnifyFunctionExitNodesPass());
		MPM->add(createAggressiveDCEPass());
		MPM->add(createDeadInstEliminationPass());
		MPM->add(createDeadCodeEliminationPass());
		MPM->add(createDeadStoreEliminationPass());
		MPM->add(createGlobalsModRefPass());
		MPM->add(createModuleDebugInfoPrinterPass());
		MPM->add(createArgumentPromotionPass());
		MPM->add(createGlobalOptimizerPass());
		MPM->add(createConstantMergePass());
		MPM->add(createGlobalsModRefPass());
		MPM->add(createPartialInliningPass());
		MPM->add(createFunctionInliningPass());
	}

	MPM->run(*m_module);
	MPM->run(*m_module);
}

void Runner::log(CompilerMessage message) {
	// We only want to log if we're currently running.
	if (m_isRunning == false) return;

	m_messages.push_back(message);
}

std::string Runner::pathname() const {
	return m_pathname;
}

void Runner::pushBlock(Block* block) {
	// We don't want to push anything if it's nullptr.
	if (block == nullptr) return;

	m_blocks.push(block);
}

Block* Runner::popBlock() {
	if (m_blocks.empty()) return nullptr;
	Block* top = m_blocks.top();
	m_blocks.pop();
	return top;
}

Block* Runner::makeBlock() {
	// First, get the top block
	Block* top = topBlock();

	// Create a new block with a new symtable, linked to the top block.
	SymTable *newSymtab = new SymTable(top->symtab());
	Block* newBlock = new Block(new SymTable(newSymtab));

	pushBlock(newBlock);
	return newBlock;
}

Block* Runner::topBlock() const {
	if (m_blocks.empty()) return nullptr;

	return m_blocks.top();
}

SymTable* Runner::symtab() const {
	if (topBlock()) return topBlock()->symtab();
    throw std::runtime_error("No symtab!");
	return nullptr;
}


FunctionStmt* Runner::mainFunction() const {
	return m_function;
}

Module* Runner::module() const {
	return m_module;
}

IRBuilder<>* Runner::builder() const {
	return m_builder;
}

LLVMContext& Runner::context() {
	return getGlobalContext();
	return *m_context;
}

FunctionPassManager* Runner::functionOptimizer() const {
	return m_functionOptimizer;
}
