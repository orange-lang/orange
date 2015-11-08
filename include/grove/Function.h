/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include <string>

#include "Block.h"
#include "Typed.h"

class Function : public Block, public Typed {
private:
	std::string m_name;
public:
	/// Gets the name of the function
	std::string getName() const;
	
	/// Constructs a new function that exists in a parent
	Function(ASTNode* parent, std::string name);
	
	/// Constructs a new global function.
	Function(Module* module, std::string name);
};
