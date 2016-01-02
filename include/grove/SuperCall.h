/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include "ExpressionCall.h"

class ClassDecl;

/**
 * Represents calling a constructor of the parent class 
 */
class SuperCall : public ExpressionCall {
private:
	ClassDecl* m_class;
protected:
	virtual void findNode();
public:
	virtual void initialize() override;
	virtual void findDependencies() override;
	
	virtual void resolve() override;
	
	virtual ASTNode* copy() const override;
	
	SuperCall(std::vector<Expression *> args);
	SuperCall(const SuperCall& other);
};
