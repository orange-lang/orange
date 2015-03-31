#ifndef __PARSER_H__
#define __PARSER_H__

#include <vector> 
#include "lexer.h"

class ORoot {

};


// a statement has an expression 
class OStatement : public ORoot {

};

// expression encapsulates most things. 
// expression can boil down to a number and an ID.
// types of expressions: number, id, method call, op
class OExpression : public OStatement {

}; 

class OID : public OExpression {
public: 
	LexemeType type;
	std::string name; 
};

class OVariable : public OID {
public:
	OExpression *value; 
};

class ODeclaraions : public OExpression {
public:
	std::vector<OVariable*> vars; 
};

class OUint : public OExpression {
public:
	LexemeType type;
	uint64_t value;
};

class OInt : public OExpression {
public:
	LexemeType type;
	int64_t value; 
};

class OFloat : public OExpression {
public:
	LexemeType type;
	float value; 
};

class ODouble : public OExpression {
public:
	LexemeType type;
	double value;
};

class OBinopStatement : public OExpression {
public:
	OExpression *LHS;
	LexemeType op;
	OExpression *RHS;
};

class OBlock : public ORoot {
public:
	std::vector<OStatement*> Statements;
};

class OFunction : public OStatement {
public:
	std::string name; 
	std::vector<OID *> args; 
	OBlock *block;
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

	Parser(std::vector<Lexeme*> lexemes) : lexemes(lexemes) {}
}; 


#endif