#ifndef __PARSER_H__
#define __PARSER_H__

#include <vector> 
#include <sstream>
#include "llvm/Analysis/Passes.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/PassManager.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Transforms/Scalar.h"
using namespace llvm;

#include "lexer.h"

class ORoot {
public:
	virtual std::string string() { return "ROOT"; }
	virtual Value *Codegen() { return nullptr; }
};


// a statement has an expression 
class OStatement : public ORoot {
public:
	virtual std::string string() { return "STATEMENT"; }
};

// expression encapsulates most things. 
// expression can boil down to a number and an ID.
// types of expressions: number, id, method call, op
class OExpression : public OStatement {
public:
	virtual std::string string() { return "EXPRESSION"; }
}; 

class OID : public OExpression {
public: 
	LexemeType type;
	std::string name; 
	virtual std::string string() { return name; }
	virtual Value *Codegen();
};

class OVariable : public OID {
public:
	OExpression *value; 
	virtual std::string string() { 
		std::stringstream ss;
		ss << LexemeMap[type] << " " << name << " = " << value->string();
		return ss.str();
	}
	virtual Value *Codegen();
};

class ODeclaraions : public OExpression {
public:
	std::vector<OVariable*> vars; 
	virtual std::string string() { 
		std::stringstream ss; 
		for (OVariable *v : vars) {
			ss << v->string(); 
		}
		return ss.str();
 	}
	virtual Value *Codegen() {
		printf("Codegen declarations!\n");
		return nullptr; 
	}
};

class OUint : public OExpression {
public:
	LexemeType type;
	uint64_t value;
	virtual std::string string() { 
		std::stringstream ss; 
		ss << value;
		return ss.str();
	}
	virtual Value *Codegen() {
		printf("Codegen uint!\n");
		return nullptr; 
	}
};

class OInt : public OExpression {
public:
	LexemeType type;
	int64_t value; 
	virtual std::string string() {  
		std::stringstream ss; 
		ss << value;
		return ss.str();
	}
	virtual Value *Codegen();
};

class OFloat : public OExpression {
public:
	LexemeType type;
	float value; 
	virtual std::string string() { return "OFLOAT"; }
	virtual Value *Codegen() {
		printf("Codegen float!\n");
		return nullptr; 
	}
};

class ODouble : public OExpression {
public:
	LexemeType type;
	double value;
	virtual std::string string() { return "ODOUBLE"; }
	virtual Value *Codegen() {
		printf("Codegen double!\n");
		return nullptr; 
	}
};

class OFuncCall : public OExpression {
public: 
	std::string name;
	std::vector<OExpression*> args; 
	virtual std::string string() { 
		std::stringstream ss;
		ss << name << "("; 

		for (int i = 0; i < args.size(); i++) {
			ss << args[i]->string();
			if (i + 1 < args.size()) {
				ss << ", ";
			}
		}

		ss << ")";
		return ss.str();
	}
	virtual Value *Codegen() {
		printf("Codegen func call!\n");
		return nullptr; 
	}
};

class OBinopStatement : public OExpression {
public:
	OExpression *LHS;
	LexemeType op;
	OExpression *RHS;
	virtual std::string string() { return "(" + LHS->string() + " " + LexemeMap[op] + " " + RHS->string() + ")"; }
	virtual Value *Codegen();
};

class OBlock : public ORoot {
public:
	std::vector<OStatement*> Statements;
	std::string string() {
		std::stringstream ss;
		ss << "global: " << std::endl; 
		for (OStatement *s : Statements) {
			if (!s) continue;
			ss << "\t"; 
			for (char line : s->string()) {
				ss << line;
				if (line == '\n') 
					ss << "\t";
			}
			ss << std::endl;
		} 
		return ss.str();
	}

	virtual Function *Codegen();
};

class OFunction : public OStatement {
public:
	std::string name; 
	std::vector<OID *> args; 
	OBlock *block;
	virtual std::string string() {
		std::stringstream ss; 
		ss << name << ":" << std::endl;
		for (OStatement *s : block->Statements) {
			if (!s) continue;
			ss << "\t"; 
			for (char line : s->string()) {
				ss << line;
				if (line == '\n') 
					ss << "\t";
			}
			ss << std::endl;
		} 
		return ss.str();
	}
	virtual Function *Codegen();
}; 

class ODeclaration : public OStatement {

};

class Parser {
private:
	int lookahead = 0;
	std::vector<Lexeme*> lexemes;

	Lexeme* getLexeme() const;
	OFunction *parseFunction();
	std::vector<OID *> parseArgs();
	OExpression *parseExpression1(OExpression *LHS, int min_prec);
	OExpression *parseExpression();
	OExpression *parsePrimary();
	ODeclaraions *parseDeclaration();
public:
	// Parses a vector of lexemes and returns a global block.
	OBlock *Parse(bool=true); 

	void Dump();

	Parser(std::vector<Lexeme*> lexemes);
}; 


#endif