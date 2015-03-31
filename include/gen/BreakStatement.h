/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __BREAK_STATEMENT_H__ 
#define __BREAK_STATEMENT_H__

#include "AST.h"

class BreakStatement : public Expression {
public:
	Value* Codegen();

	virtual std::string getClass() { return "BreakStatement"; }

	virtual std::string string();

	virtual bool isConstant() { return false; }

	void resolve();

	virtual ASTNode* clone() { 
		return new BreakStatement(); 
	}
};


#endif 