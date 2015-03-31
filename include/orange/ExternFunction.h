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
	AnyType* m_type;
	std::string m_name;
	ParamList m_parameters;
public:
	virtual std::string getClass() { return "ExternFunction"; }

	virtual Value* Codegen();

	virtual ASTNode* clone() {
		return new ExternFunction(m_type, m_name, m_parameters);
	}

	virtual void resolve();

	virtual AnyType* getType() { return m_type; }

	virtual bool isSigned() { return m_type->isSigned(); }

	ExternFunction(AnyType* returnType, std::string name, ParamList parameters);
};

#endif 