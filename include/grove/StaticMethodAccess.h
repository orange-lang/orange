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

/**
 * StaticMethodAccess refers to a static method OR a class method that is 
 * being accessed to via the class (e.g., &ClassName.classMethod)
 */
class StaticMethodAccess : public NodeReference
{
private:
	const ClassDecl* m_class = nullptr;
	OString m_name;
public:
	/// Depends on all methods with the given name in class.
	virtual void findDependencies() override;
	
	/// Finds the exact method.
	virtual void resolve() override;
	virtual void build() override;
	
	virtual ASTNode* copy() const override;
	
	virtual std::vector<ObjectBase**> getMemberNodes() override;
	
	virtual std::vector<std::vector<ObjectBase *>*> getMemberLists() override;
	
	StaticMethodAccess(const ClassDecl* theClass, OString name);
	StaticMethodAccess(const StaticMethodAccess& other);
};