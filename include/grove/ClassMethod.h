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

/**
 * Represents a method for a class.
 * Provides a hint that is the this parameter.
 */
class ClassMethod : public Function, public ClassTopLevel
{
public:
	/// Gets the type of this method without the this parameter
	virtual Type* getBasicType() const;
	
	/// Gets the parameter list without the this parameter
	virtual std::vector<Parameter *> getBasicParams() const;
	
	virtual void findDependencies() override;
	virtual void resolve() override;
	
	ClassMethod(OString name, std::vector<Parameter *> params);
};