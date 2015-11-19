/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include <string>
#include <stack>
#include <vector>

class Builder;
class Namespace;
class Block;
class Function;
class ASTNode;

namespace llvm { class Module; }
namespace llvm { class LLVMContext; }

namespace llvm {
	class ConstantFolder;
	
	template <bool preserveNames>
	class IRBuilderDefaultInserter;
	
	template <bool preserveNames, typename T, typename Inserter>
	class IRBuilder;
}

typedef llvm::IRBuilder<true, llvm::ConstantFolder,
llvm::IRBuilderDefaultInserter<true> > IRBuilder;

/**
 * Module hosts methods for compiling a specific object file. It accepts 
 * a single file.
 */
class Module {
private:
	llvm::Module* m_llvm_module = nullptr;
	IRBuilder* m_ir_builder = nullptr;
	
	Builder* m_builder = nullptr;
	
	// The global function
	Function* m_main;
	
	// The local namespace for this module.
	Namespace* m_namespace = nullptr;
	
	std::string m_file;
	
	// Stack of active blocks during parsing
	std::stack<Block *> m_ctx;
	
	std::vector<ASTNode *> m_resolved;
	
	void parse();
public:
	/// Gets the LLVM module.
	llvm::Module* getLLVMModule() const;
	
	/// Gets the IR builder.
	IRBuilder* getIRBuilder() const;
	
	llvm::LLVMContext& getLLVMContext() const;
	
	/// Get file that this module is building.
	std::string getFile() const;
	
	/// Returns the builder building this module.
	Builder* getBuilder() const;
	
	/// Gets the local namespace for this module.
	Namespace* getNamespace() const;
	
	/// Gets the currently active block.
	Block* getBlock() const;
	
	/// Gets the main function for this module.
	Function* getMain() const;
	
	/// Push a block to the stack.
	void pushBlock(Block *);
	
	/// Pops a block from the stack.
	Block* popBlock();
	
	/// Resolve a node and its children, if it's unresolved.
	void resolve(ASTNode *node);
	
	/// Resolve unresolved nodes.
	void resolve();
	
	/// Generate code.
	void build();
	
	/// Constructs a new module with a specified builder and filepath.
	Module(Builder* builder, std::string filePath);
};
