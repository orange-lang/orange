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

class Constructor : public Function
{
private:
	const ClassDecl* m_class = nullptr;
public:
	const ClassDecl* getClass() const;
	
	virtual ASTNode* copy() const override;
	
	virtual std::vector<ObjectBase**> getMemberNodes() override;
	
	virtual std::vector<std::vector<ObjectBase *>*> getMemberLists() override;
	
	Constructor(const ClassDecl* theClass, OString name,
				std::vector<Parameter *> params);
	Constructor(const Constructor& other);
};