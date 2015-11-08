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

namespace llvm { class Function; }
namespace llvm { class BasicBlock; }

class Function : public Block, public Typed {
private:
	std::string m_name;
	
	llvm::BasicBlock* m_entry = nullptr;
	llvm::BasicBlock* m_exit = nullptr;
public:
	/// Gets the name of the function
	std::string getName() const;
	
	/// Get the entry block for this function
	llvm::BasicBlock* getEntry() const;
	
	/// Get the exit block for this function.
	llvm::BasicBlock* getExit() const;
	
	virtual void build();
	
	/// Constructs a new function that exists in a parent
	Function(ASTNode* parent, std::string name);
	
	/// Constructs a new global function.
	Function(Module* module, std::string name);
};
