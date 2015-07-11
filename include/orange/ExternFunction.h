/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_EXTERN_FUNCTION_H__
#define __ORANGE_EXTERN_FUNCTION_H__

#include "AST.h"
#include "Values.h"
#include "FunctionStmt.h"

class ExternFunction : public Statement {
private:
	std::string m_name;
	ParamList m_parameters;
public:
	virtual std::string getClass() { return "ExternFunction"; }

	virtual std::string string();

	virtual Value* Codegen();

	virtual ASTNode* clone() {
		auto clone = new ExternFunction(m_type, m_name, m_parameters);
		clone->copyProperties(this);
		return clone; 
	}

	virtual void initialize();

	virtual void resolve();

	virtual bool isSigned() { return m_type->isSigned(); }

	ExternFunction(OrangeTy* returnType, std::string name, ParamList parameters);
};

#endif 