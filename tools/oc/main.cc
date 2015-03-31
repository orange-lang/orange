#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "gen/AST.h"
#include "helper/args.h"

extern FILE* yyin;
extern int yylex();

extern Block *globalBlock;
extern int yyparse();


int main(int argc, char **argv) {
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
		}
		
		if (a[0] == "-S") {
			CodeGenerator::outputAssembly = true; 

			if (outputSet == false) {
				CodeGenerator::outputFile = "a.s";						
			}
		}

		if (a[0] == "-h" || a[0] == "--help") {
			std::cerr << "OVERVIEW: orange compiler\n\n";
			std::cerr << "USAGE: " << argv[0] << " [options] <input>\n\n";
			std::cerr << "OPTIONS:\n";
			std::cerr << "\t-o <file>\t\tWrite output to <file>\n";
			std::cerr << "\t-S\t\t\tWrite output as assembly\n";
			std::cerr << "\t-h\t\t\tGet this help message\n";
			std::cerr << "\t--help\t\t\tAlias of -h\n";
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
	// while (yylex() != 0);

	yyparse();

	if (globalBlock == nullptr) {
		std::cerr << "fatal: some parsing issue occured...\n";
		return 1;
	}

	CodeGenerator::init();
	CodeGenerator::Generate(globalBlock);


	return 0;
}
