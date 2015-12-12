/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "CodeBase.h"

class Expression;
class ASTNode;

class ExprFactory : public CodeBase
{
public:
	/// Produce a new expression from a given context.
	virtual Expression* produce(const ASTNode* context);
};