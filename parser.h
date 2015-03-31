#ifndef __PARSER_H__
#define __PARSER_H__

#include <vector> 
#include "lexer.h"

class ORoot {

};

// expression encapsulates most things. 
// expression can boil down to a number and an ID.
// types of expressions: number, id, method call, op
class OExpression : public ORoot {

}; 

// a statement has an expression 
class OStatement : public ORoot {

};

class OFunction : public OStatement {

}; 

class ODeclaration : public OStatement {

};

class OBlock : public ORoot {
public:
	std::vector<OStatement*> Statements;
};


#endif