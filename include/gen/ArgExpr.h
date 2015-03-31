/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ARG_EXPR_H__
#define __ARG_EXPR_H__
#include "AST.h"
#include "AnyType.h"

/**
 * ArgExprs are represented by argument variables in function definitions. 
 * They don't need to have a type defined; if there's no type, then it is a 
 * generic argument.
 */
class ArgExpr : public Statement {
protected:
	AnyType *type;	
	std::string name;
	bool isLocked = false;
public:
	Type *getType();

	/**
	 * Gets the AnyType, if any, assigned to this instance.
	 *
	 * @return The AnyType assigned to this instance.
	 */
	AnyType *getAnyType() const;

	/**
	 * Sets the AnyType, replacing the current one, if any.
	 *
	 * @param newType The new type to assign.
	 */
	void setType(AnyType *newType);

	Statement *clone();

	/**
	 * Gets the name assigned to this parameter.
	 *
	 * @return The name of this parameter.
	 */
	std::string getName() const;

	virtual bool isSigned();

	virtual std::string string();

	ArgExpr(AnyType* type, std::string* name);
};

#endif 