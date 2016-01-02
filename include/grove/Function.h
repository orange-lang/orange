/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include <string>

#include "Block.h"
#include "Named.h"
#include "Valued.h"
#include "Genericable.h"

namespace llvm { class Function; }
namespace llvm { class BasicBlock; }
namespace llvm { class Value; }

namespace Orange { class Type; }
class Parameter;

class Function : public Block, public Valued, public Genericable, public Named
{
private:
	llvm::BasicBlock* m_entry = nullptr;
	llvm::BasicBlock* m_exit = nullptr;
	
	llvm::Value* m_ret_value = nullptr;
	llvm::Function* m_function = nullptr;
protected:
	const Orange::Type* m_ret_type = nullptr;
	std::vector<Parameter *> m_params;
	
	virtual void createReturn();
	virtual void setupFunction();
	virtual void optimize();
public:
	/// Creates the value for this function.
	/// Called during the build process. 
	virtual void createFunction();
	
	/// Get the entry block for this function
	llvm::BasicBlock* getEntry() const;
	
	/// Get the exit block for this function.
	llvm::BasicBlock* getExit() const;
	
	/// Gets the LLVM return value.
	llvm::Value* getRetValue() const;
	
	/// Gets the LLVM function.
	llvm::Function* getLLVMFunction() const;
	
	/// Gets a parameter by a given name.
	Parameter* getParam(std::string name) const;
	
	/// Gets the list of parameters as a list of types.
	std::vector<const Orange::Type *> getParamTys() const;
	
	/// Gets the parameters of this function.
	std::vector<Parameter *> getParams() const;
	
	/// Gets this function's return type.
	const Orange::Type* getReturnType() const;
	
	void setReturnType(const Orange::Type* ty);
	
	virtual OString getMangledName() const override;
	
	/// Indicates whether or not this function returns void.
	bool isVoidFunction() const;
	
	virtual ASTNode* copy() const override;
	
	virtual std::vector<ObjectBase**> getMemberNodes() override;
	
	virtual std::vector<std::vector<ObjectBase *>*> getMemberLists() override;
	
	virtual bool isGeneric() const override;
	
	virtual Genericable* createInstance(const Orange::Type* type) override;
	
	virtual void findDependencies() override;
	
	virtual void resolve() override;
	
	virtual void prebuild() override;
	
	virtual void build() override;
	
	virtual bool matchesType(const Orange::Type* type) const override;
	
	virtual bool isTerminator() const override;
	
	/// Constructs a new orphaned function 
	Function(OString name, std::vector<Parameter *> params);
	
	/// Constructs a new global function.
	Function(Module* module, OString name, std::vector<Parameter *> params);
	
	Function(const Function& other);
};
