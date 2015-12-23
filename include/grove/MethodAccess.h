/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "NodeReference.h"

class ClassDecl;

class MethodAccess : public NodeReference
{
private:
	const ClassDecl* m_class = nullptr;
	OString m_name;
public:
	/// Depends on all methods with the given name in class.
	virtual void findDependencies() override;
	
	/// Finds the exact method.
	virtual void resolve() override;
	
	virtual ASTNode* copy() const override;
	
	MethodAccess(const ClassDecl* theClass, OString name);
	MethodAccess(const MethodAccess& other);
};