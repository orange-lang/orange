#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "AST.h"

extern FILE* yyin;
extern int yylex();

extern Block *globalBlock;
extern int yyparse();


int main(int argc, char **argv) {
	if (argc < 2) {
		printf("usage: %s [filename]\n", argv[0]);
		return 1;
	}

	yyin = fopen(argv[1], "r");
	// while (yylex() != 0);

	yyparse();

	printf("done parsing.\n");

	if (globalBlock == nullptr) {
		printf("an issue occured during parsing...\n");
		return 1;
	}

	// print out shit
	std::cout << globalBlock->string() << std::endl; 

	printf("generating code...\n");

	CodeGenerator::init();
	CodeGenerator::Generate(globalBlock);


	return 0;
}
