#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Lexer.h"
#include "Parser.h"

std::string getFileContents(std::string fileName) {
	std::ifstream file(fileName);
	if (file.is_open() == false) {
		std::cerr << "fatal: file " << fileName << " not found.\n";
		throw new std::invalid_argument("fileName not found.");
	}

	std::stringstream buffer;
	buffer << file.rdbuf();

	std::string fileSource(buffer.str());
	return fileSource;
}

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("usage: %s [filename]\n", argv[0]);
	}

	std::string fileContents = getFileContents(argv[1]);
	std::vector<Lexeme*> lexemes = Lex(fileContents);
	// PrintLexemes(lexemes);

	Parser parser(lexemes);
	OBlock *b = parser.Parse(); 

	std::cout << b->string() << std::endl;
	b->Codegen();

	parser.Dump();

	return 0;
}
