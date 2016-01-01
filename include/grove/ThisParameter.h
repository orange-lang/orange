/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include "Parameter.h"

class ClassDecl;

class ThisParameter : public Parameter {
private:
	ClassDecl* m_class = nullptr;
public:
	virtual std::vector<ObjectBase**> getMemberNodes() override;
	
	virtual ASTNode* copy() const override;
	
	virtual void findDependencies() override;
	virtual void resolve() override;
	
	ThisParameter(ClassDecl* theClass);
	ThisParameter(const ThisParameter& other);
};
