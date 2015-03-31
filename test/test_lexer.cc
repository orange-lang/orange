#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

extern FILE* yyin;
extern int yylex();

int testLexer(int, char**);

int main(int argc, char **argv){

	return testLexer(argc, argv);
}

int testLexer(int argc, char **argv){

	if (argc < 2) {
		return 1;
	}

	std::string baselineDir = argc >= 3 ? argv[2] : "";
	std::string file = argv[1];
	std::vector<std::string> outputV;


	yyin = fopen(file.c_str(), "r");

	if (yyin == nullptr) {
		std::cerr << "fatal: file " << file.c_str() << " not found.\n";
		return 1;
	}

	int slash = 0, dot = 0;
	slash = file.find_last_of('/');
	dot = file.find_last_of('.');

	std::string outputFilePath = "LexOutput_" + file.substr(slash + 1, dot - slash - 1) + ".txt";

	remove(outputFilePath.c_str());

	std::ofstream output(outputFilePath, std::ofstream::out | std::ofstream::app);

	if (!output.is_open()){
		std::cerr << "fatal:output file could not be opened." << std::endl;
		return 1;
	}

	int lexVal = yylex();
	output << lexVal << "\n";
	outputV.push_back(std::to_string(lexVal));

	while (lexVal != 0){
		lexVal = yylex();
		output << lexVal << "\n";
		outputV.push_back(std::to_string(lexVal));
	}

	output.close();

	std::ifstream baseline(baselineDir + outputFilePath, std::ifstream::in);
	if (baseline.is_open()){
		std::string line;
		int count = 0;
		while (std::getline(baseline, line)){
			if (outputV[count] != line){
				std::cout << outputV[count] << " == " << line << std::endl;
				return 1;
			}
			count += 1;
		}
	}
	else
		rename(outputFilePath.c_str(), (baselineDir + outputFilePath).c_str());
	
	return 0;
}