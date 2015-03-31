/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __CONTINUE_STATEMENT_H__ 
#define __CONTINUE_STATEMENT_H__

#include "AST.h"

class ContinueStatement : public Expression {
public:
	Value* Codegen();

	virtual std::string getClass() { return "ContinueStatement"; }

	virtual std::string string();

	virtual bool isConstant() { return false; }

	void resolve();

	virtual ASTNode* clone() { 
		return new ContinueStatement(); 
	}
};


#endif 