/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "Function.h"

class ClassDecl;
class Parameter;
class ClassMethod;

class Constructor : public Function
{
private:
	ClassDecl* m_class = nullptr;
	ClassMethod* m_method = nullptr;
public:
	ClassDecl* getClass() const;
	ClassMethod* getMethod() const;
	
	virtual ASTNode* copy() const override;
	
	virtual void findDependencies() override;
	
	virtual Genericable* createInstance(const Orange::Type* type) override;
	
	virtual std::vector<ObjectBase**> getMemberNodes() override;
	
	virtual std::vector<std::vector<ObjectBase *>*> getMemberLists() override;
	
	Constructor(ClassDecl* theClass, ClassMethod* method,
				OString name, std::vector<Parameter *> params);
	Constructor(const Constructor& other);
};