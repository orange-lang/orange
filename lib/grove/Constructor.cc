/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/Constructor.h>

#include <util/assertions.h>

const ClassDecl* Constructor::getClass() const
{
	return m_class;
}

Constructor::Constructor(const ClassDecl* theClass, OString name,
						 std::vector<Parameter *> params)
: Function(name, params)
{
	assertExists(theClass, "Constructor created with no class");
	m_class = theClass;
}