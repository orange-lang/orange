#ifndef __GEN_GENERATOR_H__
#define __GEN_GENERATOR_H__

#include "AST.h"
#include "Symtab.h"

class CodeGenerator {
private:
	static void GenerateObject();
public:
	static std::string outputFile;
	static std::string fileBase;
	static bool outputAssembly;
	static bool verboseOutput;
	static bool doLink;

	static Module *TheModule;
	static IRBuilder<> Builder;
	static FunctionPassManager *TheFPM;
	
	static SymTable* Symtab;
	
	static void init();
	static void Generate(Block *globalBlock);
};

typedef CodeGenerator CG;

#endif 