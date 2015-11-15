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
#include "Named.h"
#include "Valued.h"

namespace llvm { class Function; }
namespace llvm { class BasicBlock; }
namespace llvm { class Value; }

class Type;
class Parameter;

class Function : public Block, public Valued, public Typed, public Named {
private:
	llvm::BasicBlock* m_entry = nullptr;
	llvm::BasicBlock* m_exit = nullptr;
	
	llvm::Value* m_ret_value = nullptr;
	llvm::Function* m_function = nullptr;
	
	std::vector<Parameter *> m_params;
protected:
	virtual void createFunction();
	virtual void createReturn();
	virtual void setupFunction();
	virtual void optimize();
public:
	/// Get the entry block for this function
	llvm::BasicBlock* getEntry() const;
	
	/// Get the exit block for this function.
	llvm::BasicBlock* getExit() const;
	
	/// Gets the LLVM return value.
	llvm::Value* getRetValue() const;
	
	/// Gets the LLVM function.
	llvm::Function* getLLVMFunction() const;
	
	/// Gets the parameters of this function.
	std::vector<Parameter *> getParams() const;
	
	/// Gets this function's return type.
	Type* getReturnType();
	
	/// Indicates whether or not this function returns void.
	bool isVoidFunction();
	
	virtual void resolve() override;
	
	virtual void build() override;
	
	/// Constructs a new orphaned function 
	Function(std::string name, std::vector<Parameter *> params);
	
	/// Constructs a new global function.
	Function(Module* module, std::string name, std::vector<Parameter *> params);
};
