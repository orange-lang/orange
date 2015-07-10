/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __FUNC_CALL_H__ 
#define __FUNC_CALL_H__

#include "AST.h"

class FuncCall : public Expression {
private:
	std::string m_name; 

	ArgList m_arguments; 
public:
	virtual std::string getClass() { return "FuncCall"; }

	virtual Value* Codegen();

	virtual ASTNode* clone();

	virtual std::string string();

	virtual void resolve();

	/** 
	 * Returns true if the function it is calling returns 
	 * a signed value.
	 *
	 * @return True if the result of this function call is a signed value, false otherwise.
	 */
	virtual bool isSigned();

	std::string name() const { return m_name; }

	FuncCall(std::string name);
	FuncCall(std::string name, ArgList arguments);
}; 

#endif 
