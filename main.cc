#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

extern FILE* yyin;
extern int yylex();

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("usage: %s [filename]\n", argv[0]);
		return 1;
	}

	yyin = fopen(argv[1], "r");
	while (yylex() != 0);

	printf("done.\n");
	return 0;
}
