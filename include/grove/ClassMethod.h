/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "Function.h"
#include "ClassTopLevel.h"

class ClassDecl;

/**
 * Represents a method for a class.
 * Provides a hint that is the this parameter.
 */
class ClassMethod : public Function, public ClassTopLevel
{
private:
	ClassDecl* m_class = nullptr;
	Parameter* m_this_param = nullptr;
public:
	virtual void findDependencies() override;
	
	Parameter* getThisParam() const;
	
	ClassMethod(OString name, ClassDecl* theClass,
				std::vector<Parameter *> params);
};