/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <libast/Statement.h>

bool Statement::supportsRegistration() const
{
	return false;
}

void Statement::registerInLibrary(Library *library) const
{
	// Do nothing
}

bool Statement::isTerminator() const
{
	return false;
}

Statement::Statement(Module* module)
: ASTNode(module)
{
	// Do nothing 
}

Statement::Statement()
: ASTNode()
{
	
}