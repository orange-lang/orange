/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include "ASTNode.h"

class Library;

/**
 * Statement is the base class for elements that do not have values.
 */
class Statement : public ASTNode {
public:
	/**
	 * Whether or not this elements supports being registered. 
	 * Just supporting registration does not necessarily mean 
	 * an element will be registered; the main function of the module 
	 * decided which elements get registered (immediate children are 
	 * the first.
	 * @return Returns whether this element can be registered.
	 */
	virtual bool supportsRegistration() const;
	
	/// Register this statement as a LocalNamedType in the library.
	/// Override to add behavior.
	virtual void registerInLibrary(Library* library) const;
	
	/// Determins whether or not a statement is a terminator;
	/// e.g., if following the build of this statement, if other
	/// code can follow it.
	virtual bool isTerminator() const;
	
	virtual ASTNode* copy() const override = 0;
	
	Statement();
	Statement(Module* module);
};
