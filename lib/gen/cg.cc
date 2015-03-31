#include <llvm/MC/MCObjectFileInfo.h>
#include <llvm/MC/MCContext.h>
#include <llvm/MC/MCAsmInfo.h>
#include <llvm/CodeGen/AsmPrinter.h>
#include <llvm/Support/FormattedStream.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/raw_os_ostream.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Target/TargetLibraryInfo.h>
#include <llvm/Target/TargetMachine.h>

#include <gen/AST.h>
#include <gen/generator.h>
#include <helper/link.h>

using namespace llvm::sys::fs;

Module *CodeGenerator::TheModule;
IRBuilder<> CodeGenerator::Builder(getGlobalContext());
SymTable* CodeGenerator::Symtab = nullptr;
FunctionPassManager* CodeGenerator::TheFPM;
std::string CodeGenerator::outputFile = "a.out";
bool CodeGenerator::outputAssembly = false;
bool CodeGenerator::verboseOutput = false;
bool CodeGenerator::doLink = true;
std::string CodeGenerator::fileBase = "";

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
	TheModule->setTargetTriple(sys::getProcessTriple());

	OurFPM->add(createBasicAliasAnalysisPass());
	OurFPM->add(createInstructionCombiningPass());
	OurFPM->add(createReassociatePass());
	OurFPM->add(createGVNPass());
	OurFPM->add(createCFGSimplificationPass());
	OurFPM->add(createDeadCodeEliminationPass());
	OurFPM->doInitialization();
	
	TheFPM = OurFPM;
}


// linking on mac: 
// ld -arch x86_64 -macosx_version_min 10.10 a.out -lSystem -o a 
void CodeGenerator::Generate(Block *globalBlock) {
	std::vector<Type*> Args;
	FunctionType *FT = FunctionType::get(Type::getVoidTy(getGlobalContext()),
		Args, false);
	Function *TheFunction = Function::Create(FT, Function::ExternalLinkage, "@main", TheModule);

	BasicBlock *BB = BasicBlock::Create(getGlobalContext(), "entry", TheFunction);
	Builder.SetInsertPoint(BB);

	CG::Symtab = globalBlock->symtab;
	
	globalBlock->Codegen();
	CG::Builder.CreateRetVoid();

	GenerateObject();
}

void CodeGenerator::GenerateObject() {
	std::string err; 
	Triple triple = Triple(sys::getProcessTriple());
	const Target *target = TargetRegistry::lookupTarget("x86-64", triple, err);
	if (target == nullptr) {
		std::cerr << "fatal: " << err << std::endl;
		exit(1);
	}

	StringRef name = sys::getHostCPUName();

  SubtargetFeatures Features;
  Features.AddFeature("64bit");
  Features.AddFeature("64bit-mode");
	std::string FeaturesStr = Features.getString();

	TargetOptions options;
	options.PrintMachineCode = 0;

	if (verboseOutput == true) {
		std::cout << "Detected CPU " << name.str() << std::endl; 
		std::cout << "Detected Host " << triple.getTriple() << std::endl; 
		std::cout << "Features: " << FeaturesStr << std::endl; 

		// TheModule->dump();
	}

	TargetMachine *tm = target->createTargetMachine(triple.getTriple(), name, FeaturesStr, options);
	if (tm == nullptr) {
		std::cerr << "fatal: could not create target machine\n";
		exit(1);
	}

	// local output file
	std::string loutput = fileBase;
	if (outputAssembly == true) {
		loutput += ".s";
	} else {
		loutput += ".o";
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
	ThePM->add(TLI);
	ThePM->add(new DataLayoutPass(TheModule));

	LLVMTargetMachine::CodeGenFileType genType = outputAssembly ? LLVMTargetMachine::CGFT_AssemblyFile : LLVMTargetMachine::CGFT_ObjectFile;

	bool b = tm->addPassesToEmitFile(*ThePM, strm, genType, true);
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

		options.push_back("-o");
		options.push_back(outputFile.c_str()); // final output. defaults to a.out
#endif 

		// local output 
		options.push_back(loutput.c_str());

		invokeLinkerWithOptions(options);

		remove(loutput.c_str());
	}


}

