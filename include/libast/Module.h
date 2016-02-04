/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include <string>
#include <stack>
#include <vector>
#include <map>

#include "SearchSettings.h"
#include "OString.h"

class Builder;
class Namespace;
class Block;
class Function;
class ASTNode;
class Named;
namespace Orange { class Type; }

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

typedef std::map<const ASTNode *, const ASTNode *> CopyMap;

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
	
	std::vector<ASTNode *> m_initialized;
	std::vector<ASTNode *> m_resolved;
	std::vector<ASTNode *> m_searched;
	std::vector<ASTNode *> m_prebuilt;
	std::vector<ASTNode *> m_built;
	
	// Children of the module are nodes that are used in the AST
	// but have no parents, and are destroyed here.
	std::vector<ASTNode *> m_children;
	
	// A stack of copy states. Nodes that initiate copy on nodes request
	// for a new copy stack, which nodes will register their created copies
	// to the stack. Then, nodes that were referencing the original node
	// can look at the copy stack and get their newly created copy.
	CopyMap m_copy_states;
	int m_copy_levels = 0;
	
	/// Indicates whether or not we are currently parsing.
	bool m_parsing = false;
	
	void parse();
	
	/**
	 * Iterates through blocks. Uses SearchSettings to determine which 
	 * blocks will be next. If m_module is in parsing mode, module's 
	 * m_ctx will be used. Otherwise, AST parentage will be used.
	 */
	class BlockIterator
	{
	private:
		const Module* m_module;
		const ASTNode* m_ptr;
		const SearchSettings& m_settings;
		std::stack<Block *> m_ctx_stack;
		unsigned int m_step;
		
		bool useContextStack() const;
	public:
	 	bool hasNext() const;
	 	const Block* getNext();
		const ASTNode* getLimit() const;
	 
		BlockIterator(const Module* mod, const ASTNode* from,
					  const SearchSettings& settings);
	};
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
	
	/// Returns whether or not this module is currently parsing.
	bool getParsing() const;
	
	void addChild(ASTNode *child);
	
	/// Push a block to the stack.
	void pushBlock(Block *);
	
	/// Pops a block from the stack.
	Block* popBlock();
	
	/// Find all dependencies for a node and its children, if it hasn't been
	/// searched.
	void findDependencies(ASTNode* node);
	
	// Finds dependencies for all unsearched nodes.
	void findDependencies();
	
	/// Initializes a node and its children, if it hasn't already been
	/// initialized.
	void initialize(ASTNode* node);
	
	/// Initialize uninitialized nodes.
	void initialize();
	
	/// Resolve the dependencies of a node and then the node, but
	/// not its children. If the nodes have already been resolved, does nothing.
	void resolveDependencies(ASTNode* node);
	
	/// Resolve a node and its children, if it's unresolved.
	void resolve(ASTNode* node);
	
	/// Resolve unresolved nodes.
	void resolve();
	
	/// Does any pre-building tasks
	void prebuild(ASTNode* node);
	
	/// Does any pre-building tasks on all nodes.
	void prebuild();
	
	/// Completely processes a node.
	void process(ASTNode* node);
	
	/// Generates code for a node, ensuring it hasn't already
	/// been built.
	void build(ASTNode* node);

	/// Generate code.
	void build();
	
	/// Gets the latest node in the tree. If the current
	/// block has children, returns the last child of that block.
	/// Otherwise, returns the block.
	ASTNode* getLatestNode() const;
	
	/// Returns whether or not a named node with a given name,
	/// up to from, exists in the AST.
	bool hasNamed(OString name, const ASTNode* from,
				  SearchSettings settings) const;
	
	/// Returns a named node with a given name, optional type settings
	/// and search settings from the AST, up to but not including from.
	Named* findNamed(OString name, const Orange::Type* type,
					 const ASTNode* from,
					 SearchSettings settings = SearchSettings()) const;
	
	/// Returns all named nodes with a given name in the AST, up to but not
	/// including from.
	std::vector<Named *> findAllNamed(OString name,
									  const ASTNode* from) const;
	
	/// Returns whether or not a name is a defined type name.
	/// Uses the block stack to search up the AST.
	bool isDefinedTypeName(OString name) const;
	
	/// Informs the module that we are about to copy some nodes.
	/// Adds a new CopyMap onto a stack.
	void beginCopy();
	
	/// Defines a copy mapping. Throws an error if one already
	/// exists for the original.
	void defineCopy(const ASTNode* original, const ASTNode* copy);
	
	bool hasCopy(const ASTNode* original);
	
	/// Gets a copy from the copy map.
	ASTNode* getCopy(const ASTNode* original);
	
	/// Gets a copy from the copy map, if it exists.
	/// Returns original otherwise. 
	ASTNode* tryGetCopy(const ASTNode* original);
	
	/// Informs the module that we are finished copying.
	/// Removes the top CopyMap from the stack.
	void endCopy();
	
	/// Output built code into an object file.
	/// Returns the path of the object file.
	std::string compile();
	
	/// Constructs a new module with a specified builder and filepath.
	Module(Builder* builder, std::string filePath);
	
	/// Constructs a new empty module.
	Module();
	
	~Module();
};
