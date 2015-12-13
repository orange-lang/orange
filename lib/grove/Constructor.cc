/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/Constructor.h>
#include <grove/ClassDecl.h>
#include <grove/Parameter.h>

#include <util/assertions.h>

const ClassDecl* Constructor::getClass() const
{
	return m_class;
}

void Constructor::resolve()
{
	auto this_type = getClass()->getType();
	assertExists(this_type, "Class has no defined type");
	
	auto this_param = new Parameter(this_type, "this");
	
	if (m_params.size() == 0)
	{
		addChild(this_param);
	}
	else
	{
		addChild(this_param, m_params.at(0), 0);
	}
	
	m_params.insert(m_params.begin(), this_param);
	
	Function::resolve();
}

Constructor::Constructor(const ClassDecl* theClass, OString name,
						 std::vector<Parameter *> params)
: Function(name, params)
{
	assertExists(theClass, "Constructor created with no class");
	m_class = theClass;
}