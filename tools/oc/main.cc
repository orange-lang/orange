#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <helper/link.h> 
#include <gen/AST.h>
#include <gen/generator.h>
#include <helper/args.h>

extern FILE* yyin;
extern int yylex();

extern Block *globalBlock;
extern int yyparse();

int main(int argc, char **argv) {
	if (linkerPath() == nullptr) {
		std::cerr << "fatal: linker not found in $PATH.\n"; 
		return 1;
	}

	if (argc < 2) {
		printf("fatal: no input file specified.\n");
		return 1;
	}

	bool outputSet = false;

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
		} else if (a[0] == "-v" || a[0] == "--verbose") {
			CodeGenerator::verboseOutput = true;
		} else if (a[0] == "-c") {
			CodeGenerator::doLink = false;
		} else if (a[0] == "-h" || a[0] == "--help") {
			std::cerr << "OVERVIEW: orange compiler\n\n";
			std::cerr << "USAGE: " << argv[0] << " [options] <input>\n\n";
			std::cerr << "OPTIONS:\n";
			std::cerr << "\t-c\t\t\tOnly output an .o file (do not link)\n";
			std::cerr << "\t-o <file>\t\tWrite output to <file>\n";
			std::cerr << "\t-S\t\t\tWrite output as assembly (implies -c)\n";
			std::cerr << "\t-v | --verbose\t\tEnable verbose output\n";
			std::cerr << "\t-h | --help\t\tGet this help message\n";
			exit(1); 
		} else {
			std::cerr << "fatal: option " << a[0] << " is not recognized.\n";
			exit(1);
		}
	});

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
	// while (yylex() != 0);

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

	yyparse();

	if (globalBlock == nullptr) {
		std::cerr << "fatal: some parsing issue occured...\n";
		return 1;
	}

	CodeGenerator::init();
	CodeGenerator::Generate(globalBlock);

	fclose(yyin);


	return 0;
}
