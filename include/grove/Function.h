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
namespace llvm { class Value; }

class Type;

class Function : public Block, public Typed {
private:
	std::string m_name;
	
	llvm::BasicBlock* m_entry = nullptr;
	llvm::BasicBlock* m_exit = nullptr;
	
	llvm::Value* m_ret_value = nullptr;
	llvm::Function* m_function = nullptr;
protected:
	virtual void createFunction();
	virtual void createReturn();
	virtual void setupFunction();
	virtual void optimize();
public:
	/// Gets the name of the function
	std::string getName() const;
	
	/// Get the entry block for this function
	llvm::BasicBlock* getEntry() const;
	
	/// Get the exit block for this function.
	llvm::BasicBlock* getExit() const;
	
	llvm::Value* getRetValue() const;
	
	llvm::Function* getLLVMFunction() const;
	
	Type* getReturnType();
	
	bool isVoidFunction();
	
	virtual void resolve() override;
	
	virtual void build() override;
	
	/// Constructs a new orphaned function 
	Function(std::string name);
	
	/// Constructs a new global function.
	Function(Module* module, std::string name);
};
