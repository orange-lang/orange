/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/SuperReference.h>

ASTNode* SuperReference::copy() const
{
	return new SuperReference(*this);
}

// Internally, the search is for "this". The class type here will just
// be used for filtering members.
SuperReference::SuperReference()
: IDReference("this")
{
	// Do nothing.
}

SuperReference::SuperReference(const SuperReference& other)
: IDReference(other)
{
	// Do nothing.
}