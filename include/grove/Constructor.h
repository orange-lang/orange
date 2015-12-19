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
	
	Parameter* m_this_param = nullptr;
public:
	const ClassDecl* getClass() const;
	
	// Returns true if parameters OTHER than this are var.
	virtual bool isGeneric() const override;
	
	virtual void resolve() override;
	
	Constructor(const ClassDecl* theClass, OString name,
				std::vector<Parameter *> params);
};