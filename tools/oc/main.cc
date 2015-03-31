#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <helper/link.h> 
#include <gen/AST.h>
#include <gen/generator.h>
#include <helper/args.h>
#include <llvm/Support/CommandLine.h>
#include <gen/Block.h>

extern FILE* yyin;
extern int yylex();

extern Block *globalBlock;
extern int yyparse();

#include <string>

int main(int argc, char **argv) {
	DEBUG_MSG("OC STARTED");

	if (linkerPath() == nullptr) {
		std::cerr << "fatal: linker not found in $PATH.\n"; 
		return 1;
	}

	if (argc < 2) {
		printf("fatal: no input file specified.\n");
		return 1;
	}

	// this is a really unintelligent hack 
	// i don't know how to set a command line option otherwise, 
	// and for the moment i don't want to switch over to LLVM's confusing 
	// arg system with very little documentation 
	std::vector<const char *> forced_args; 
	forced_args.push_back(argv[0]);

	bool outputSet = false;
	std::string assemblySet = "";

	getArgs(argc, argv, [&] (std::vector<std::string> a, int loc) {
		// a[0] has the argument 
		if (a[0] == "-o") {
			const char *param = getParameter(a, argc, argv, loc);
			if (param == nullptr) {
				std::cerr << "fatal: -o included but no output file specified.\n";  
				exit(1);
			} 

			CodeGenerator::outputFile = param;
			outputSet = true; 
		} else if (a[0] == "-S") {
			CodeGenerator::outputAssembly = true; 

			if (outputSet == false) {
				CodeGenerator::outputFile = "a.s";						
			}
		} else if (a[0] == "-V" || a[0] == "--verbose") {
			CodeGenerator::verboseOutput = true;
		} else if (a[0] == "-c") {
			CodeGenerator::doLink = false;
		} else if (a[0] == "-v" || a[0] == "--version") {
			std::cout << "Orange Compiler version 0.0" << std::endl;
			exit(0);
		} else if (a[0] == "-h" || a[0] == "--help") {
			std::cerr << "OVERVIEW: Orange Compiler version 0.0\n\n";
			std::cerr << "USAGE: " << argv[0] << " [options] <input>\n\n";
			std::cerr << "OPTIONS:\n";
			std::cerr << "\t-c\t\t\tOnly output an .o file (do not link)\n";
			std::cerr << "\t-o <file>\t\tWrite output to <file>\n";
			std::cerr << "\t-S\t\t\tWrite output as assembly (implies -c)\n";
			std::cerr << "\t-32\t\t\tCompile in 32 bits\n";
			std::cerr << "\t-masm\t\t\tSets an assembly style (defaults to intel)\n";
			std::cerr << "\t\t=intel\t\tSets style to intel (default)\n";
			std::cerr << "\t\t=att\t\tSets style to AT&T\n";
			std::cerr << "\t--triple\t\t\tSets triple type (defaults to host)\n";
			std::cerr << "\t--model\t\t\tSets code model (default, kernel, large, etc)\n";
			std::cerr << "\t-v | --version\t\tPrints version\n";
			std::cerr << "\t-V | --verbose\t\tEnable verbose output\n";
			std::cerr << "\t-h | --help\t\tGet this help message\n";
			exit(1); 
		} else if (a[0] == "-m") {
			if (a[1] == "asm=intel") {
				assemblySet = "intel";
				forced_args.push_back("-x86-asm-syntax=intel");
			} else if (a[1] == "asm=att") {
				assemblySet = "att";
				forced_args.push_back("-x86-asm-syntax=att");
			} 
		} else if (a[0] == "--triple") {
			if (loc + 1 >= argc) {
				std::cerr << "fatal: missing triple tyoe.\n";
				exit(1);
			}
			CodeGenerator::tripleName = argv[loc + 1];
		}	else if (a[0] == "--model") {
			if (loc + 1 >= argc) {
				std::cerr << "fatal: missing model tyoe.\n";
				exit(1);
			}

			std::string setModel = argv[loc + 1];

			if (setModel == "default") CodeGenerator::model = llvm::CodeModel::Default;
			else if (setModel == "small") CodeGenerator::model = llvm::CodeModel::Small;
			else if (setModel == "kernel") CodeGenerator::model = llvm::CodeModel::Kernel;
			else if (setModel == "medium") CodeGenerator::model = llvm::CodeModel::Medium;
			else if (setModel == "large") CodeGenerator::model = llvm::CodeModel::Large;
			else {
				std::cerr << "fatal: unknown code model " << setModel << std::endl;
				exit(1);
			}
		}	 else if (a[0] == "--32") {
			CodeGenerator::bits32 = true;
		}	else {
			std::cerr << "fatal: option " << a[0] << " is not recognized.\n";
			exit(1);
		}
	});

	if (assemblySet == "") {
		forced_args.push_back("-x86-asm-syntax=intel");
	}

	llvm::cl::ParseCommandLineOptions(forced_args.size(),&forced_args[0]);

	std::string file = argv[1];
	if (file[0] == '-') 
		file = argv[argc-1];
	if (file[0] == '-') {
		std::cerr << "fatal: no input file specified.\n";
		return 1;
	}

	yyin = fopen(file.c_str(), "r");

	if (yyin == nullptr) {
		std::cerr << "fatal: file " << file << " not found.\n";
		return 1;
	}

	// get file base 
	std::string stripped = file; 
	size_t loc = stripped.find_last_of('/');
	if (loc != std::string::npos) {
		stripped = stripped.substr(loc+1);
	}

	loc = stripped.find('.');
	if (loc == std::string::npos) {
		CodeGenerator::fileBase = stripped; 
	} else {
		CodeGenerator::fileBase = stripped.substr(0, loc);
	}

	DEBUG_MSG("STARTING PARSE");

	yyparse();

	if (globalBlock == nullptr) {
		std::cerr << "fatal: some parsing issue occured...\n";
		return 1;
	}

	DEBUG_MSG("PERFORMING SEMANTIC ANALYSIS");

	globalBlock->resolve();

	DEBUG_MSG("PRINTING AST");

	if (CodeGenerator::verboseOutput) {
		std::cout << globalBlock->string() << std::endl;
	}

	DEBUG_MSG("STARTING CODE GENERATION");

	CodeGenerator::init();
	CodeGenerator::Generate(globalBlock);

	fclose(yyin);

	delete globalBlock;

	return 0;
}
