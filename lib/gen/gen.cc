/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <llvm/PassManager.h>

#include <llvm/MC/MCObjectFileInfo.h>
#include <llvm/MC/MCContext.h>
#include <llvm/MC/MCAsmInfo.h>
#include <llvm/CodeGen/AsmPrinter.h>
#include <llvm/CodeGen/Passes.h>
#include <llvm/Support/FormattedStream.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/raw_os_ostream.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Target/TargetLibraryInfo.h>
#include <llvm/Analysis/Lint.h>
#include <llvm/Analysis/CFGPrinter.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Transforms/IPO/InlinerPass.h>
#include <llvm/Transforms/IPO.h>
#include <llvm/Transforms/Vectorize.h>
#include <llvm/Transforms/Utils/UnifyFunctionExitNodes.h>
#include <llvm/Analysis/InlineCost.h>

#include <gen/AST.h>
#include <gen/generator.h>
#include <helper/link.h>
#include <gen/Block.h>
#include <gen/FunctionStatement.h>

using namespace llvm::sys::fs;

Module *CodeGenerator::TheModule;
IRBuilder<> CodeGenerator::Builder(getGlobalContext());
std::stack<SymTable *> CodeGenerator::Symtabs;
FunctionPassManager* CodeGenerator::TheFPM;

#if defined(__linux__) || defined(__APPLE__)
	std::string CodeGenerator::outputFile = "a.out";
#elif defined(_WIN32)
	std::string CodeGenerator::outputFile = "out.exe";
#endif 

bool CodeGenerator::outputAssembly = false;
bool CodeGenerator::verboseOutput = false;
bool CodeGenerator::doLink = true;
bool CodeGenerator::bits32 = false;
std::string CodeGenerator::tripleName = sys::getProcessTriple();
std::string CodeGenerator::fileBase = "";
llvm::CodeModel::Model CodeGenerator::model = CodeModel::Default;

typedef CodeGenerator CG;
PassManager *ThePM = nullptr;

void CodeGenerator::init() {
  LLVMContext &Context = getGlobalContext();

  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();
  InitializeNativeTargetAsmParser();

  PassRegistry *Registry = PassRegistry::getPassRegistry();
  initializeCore(*Registry);
  initializeCodeGen(*Registry);
  initializeLoopStrengthReducePass(*Registry);
  initializeLowerIntrinsicsPass(*Registry);
  initializeUnreachableBlockElimPass(*Registry);

	TheModule = new Module("orange", getGlobalContext());
	
	FunctionPassManager *OurFPM = new FunctionPassManager(TheModule);
	TheModule->setTargetTriple(tripleName);

	OurFPM->doInitialization();
	
	TheFPM = OurFPM;
}

const char *MainFunctionName() {
	return "__INTERNAL_main";
}


// linking on mac: 
// ld -arch x86_64 -macosx_version_min 10.10 a.out -lSystem -o a 
void CodeGenerator::Generate(Block *globalBlock) {
	if (globalBlock->symtab == nullptr) {
		std::cerr << "fatal: no symbol table for global.\n";
		exit(1);
	} else {
		DEBUG_MSG("Using symtab ID " << globalBlock->symtab->ID);
	}

	CG::Symtabs.push(globalBlock->symtab);
	CG::Symtabs.top()->FunctionName = new std::string(MainFunctionName());

	// Create the global block as a function so we don't have to repeat the code here.
	FunctionStatement *fstmt = new FunctionStatement(CG::Symtabs.top()->FunctionName, nullptr, globalBlock);
	fstmt->Codegen();

	//CG::TheModule->dump();

	PassManager MPM;
	MPM.add(createVerifierPass(true));
	MPM.add(createUnreachableBlockEliminationPass());
	MPM.add(createGCLoweringPass());
	MPM.add(createAlwaysInlinerPass());
	MPM.add(createPruneEHPass());
	MPM.add(createIPConstantPropagationPass());
	MPM.add(createIPSCCPPass());
	MPM.add(createMergeFunctionsPass());
	MPM.add(createStripDeadPrototypesPass());
	MPM.add(createConstantPropagationPass());
	MPM.add(createAliasAnalysisCounterPass()); 
	MPM.add(createBasicAliasAnalysisPass());
	MPM.add(createLazyValueInfoPass());
	MPM.add(createDependenceAnalysisPass());
	MPM.add(createCostModelAnalysisPass());
	MPM.add(createDelinearizationPass());
	MPM.add(createInstCountPass());
	MPM.add(createInstructionCombiningPass());
	MPM.add(createInstructionSimplifierPass());
	MPM.add(createReassociatePass());
	MPM.add(createGVNPass());
	MPM.add(createCFGSimplificationPass());
	MPM.add(createBBVectorizePass());
	MPM.add(createCodeGenPreparePass());
	MPM.add(createGVNPass());
	MPM.add(createSinkingPass());
	MPM.add(createUnifyFunctionExitNodesPass());
	MPM.add(createAggressiveDCEPass());
	MPM.add(createDeadInstEliminationPass());
	MPM.add(createDeadCodeEliminationPass());
	MPM.add(createDeadStoreEliminationPass());
	MPM.add(createGlobalsModRefPass());
	MPM.add(createModuleDebugInfoPrinterPass());
	MPM.add(createArgumentPromotionPass());
	MPM.add(createGlobalOptimizerPass());
	MPM.add(createConstantMergePass());
	MPM.add(createGlobalsModRefPass());
	MPM.add(createPartialInliningPass());
	MPM.add(createFunctionInliningPass());
	MPM.run(*TheModule);
	MPM.run(*TheModule);


	GenerateObject();
}

void CodeGenerator::GenerateObject() {
	std::string err; 
	Triple triple = Triple(tripleName);

	std::string targetStr = "x86-64";
	if (bits32) {
		targetStr = "x86";
	}
	const Target *target = TargetRegistry::lookupTarget(targetStr, triple, err);
	if (target == nullptr) {
		std::cerr << "fatal: " << err << std::endl;
		exit(1);
	}

	StringRef name = sys::getHostCPUName();

  SubtargetFeatures Features;

	Features.getDefaultSubtargetFeatures(triple);

	if (bits32 == false) {
	  Features.AddFeature("64bit");
	} 

  // Features.AddFeature("64bit-mode");
	std::string FeaturesStr = Features.getString();

	TargetOptions options;
	options.NoFramePointerElim = true;

	options.MCOptions.MCRelaxAll = 1;
	options.MCOptions.SanitizeAddress = 1;
	options.MCOptions.MCNoExecStack = 1;
	options.MCOptions.ShowMCEncoding = 1;
	options.MCOptions.ShowMCInst = 1;
	options.DataSections = true;
	options.PositionIndependentExecutable = 1;

	if (verboseOutput == true) {
		std::cout << "Detected CPU " << name.str() << std::endl; 
		std::cout << "Detected Host " << triple.getTriple() << std::endl; 
		std::cout << "Features: " << FeaturesStr << std::endl; 

		TheModule->dump();
	}


	TargetMachine *tm = target->createTargetMachine(triple.getTriple(), name, FeaturesStr, options, Reloc::Default, model);

	if (tm == nullptr) {
		std::cerr << "fatal: could not create target machine\n";
		exit(1);
	}

	// local output file
	std::string loutput = fileBase;
	if (outputAssembly == true) {
		loutput += ".s";
	} else {
#if defined(__linux__) || defined(__APPLE__)
		loutput += ".o";
#elif defined(_WIN32)
		loutput += ".obj";
#endif 
	}

	std::string ec = "";
	raw_fd_ostream raw(loutput.c_str(), ec, OpenFlags::F_RW);

	if (ec != "") {
		std::cerr << "fatal: " << ec << std::endl;
		exit(1);
	}

	formatted_raw_ostream strm(raw);

	// can i disable TLI?
  TargetLibraryInfo *TLI = new TargetLibraryInfo(triple);

  const DataLayout *DL = tm->getDataLayout();
  TheModule->setDataLayout(DL);

  ThePM = new PassManager();
	ThePM->add(createVerifierPass(true));
	ThePM->add(TLI);
	ThePM->add(new DataLayoutPass(TheModule));

	LLVMTargetMachine::CodeGenFileType genType = outputAssembly ? LLVMTargetMachine::CGFT_AssemblyFile : LLVMTargetMachine::CGFT_ObjectFile;

	bool b = tm->addPassesToEmitFile(*ThePM, strm, genType, false);
	if (b == true) {
		std::cerr << "fatal: emission is not supported.\n";
		exit(1);
	}

	ThePM->run(*TheModule);
	strm.flush();
	raw.flush();
	raw.close();

	if (doLink && outputAssembly == false) {
		std::vector<const char *> options; 

#if defined(__APPLE__) || defined(__linux__)
		std::string root = INSTALL_LOCATION;
		root += "/lib/libor/boot.o";

		options.push_back(root.c_str());

#ifdef __APPLE__
		options.push_back("-w");
#endif

#ifdef __linux__
		options.push_back("-I/lib64/ld-linux-x86-64.so.2");
#endif 

		options.push_back("-lc");
		options.push_back("-o");
		options.push_back(outputFile.c_str()); // final output. defaults to a.out
#elif defined(_WIN32) 
		std::string root = "\"";
		root += INSTALL_LOCATION;
		root += "/lib/libor/boot.obj\"";

		options.push_back(root.c_str());

		options.push_back("-o");
		options.push_back(outputFile.c_str());
#endif 

		// local output 
		options.push_back(loutput.c_str());

		invokeLinkerWithOptions(options);

		remove(loutput.c_str());
	}


}

