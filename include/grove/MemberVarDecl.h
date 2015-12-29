/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "VarDecl.h"
#include "ClassTopLevel.h"
#include "Protectable.h"

/**
 * Represents a class member variable declaration.
 */	
class MemberVarDecl : public VarDecl, public ClassTopLevel, public Protectable
{
public:
  	virtual ProtectionLevel defaultProtectionLevel() const override;
	
	virtual llvm::Value* getValue() const override;
	virtual llvm::Value* getPointer() const override;
	
	virtual ASTNode* copy() const override;
	
	/// Gets the offset of this member in the list of members of the class.
	unsigned int getOffset() const;
	
	virtual void build() override;
	
	MemberVarDecl(const Type* type, OString name, Expression* expression);
	MemberVarDecl(const MemberVarDecl& other);
};