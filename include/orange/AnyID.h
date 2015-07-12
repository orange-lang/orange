/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_ANY_ID_H__
#define __ORANGE_ANY_ID_H__

#include "AST.h"

/**
 * The AnyID class is used as the strategy design pattern to 
 * call methods from VarExpr or other structures that use IDs as their 
 * only methods of creation. 
 */
class AnyID : public Expression {
private:
	Expression* m_any_expr = nullptr; 
	std::string m_name = "";
protected:
	/**
	 * Ensures that m_any_expr is not nullptr, throwing an exception otherwise.
	 */
	void ensureValid();
public:
	virtual std::string getClass() { return "AnyID"; }

	virtual Value* Codegen();

	virtual Value* getValue();

	virtual ASTNode* clone();

	virtual std::string string();

	virtual bool returnsPtr();

	virtual bool isBlock();

	virtual OrangeTy* getType();

	virtual void mapDependencies();

	virtual void resolve();

	virtual bool isSigned();

	virtual bool isConstant();

	virtual Expression* expression(); 

	AnyID(std::string name);
};

#endif 
