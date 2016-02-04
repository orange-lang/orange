/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "Type.h"
#include "../ASTNode.h"

/**
 * A type that is both a type and in the AST. Allows for resolving of type.
 */
class NodeType : public Orange::Type, public ASTNode
{
public:
	virtual bool isNodeTy() const override;
	
	virtual bool canInitializeVar() const;
	virtual Expression* initializeVar() const;
	
	virtual ASTNode* copy() const override = 0;
	
	NodeType(bool isConst);
};