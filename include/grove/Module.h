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

class Builder;
class Namespace;
class Block;
class Function;

/**
 * Module hosts methods for compiling a specific object file. It accepts 
 * a single file.
 */
class Module {
private:
	Builder* m_builder = nullptr;
	
	// The global function
	Function* m_main;
	
	// The local namespace for this module.
	Namespace* m_namespace = nullptr;
	
	std::string m_file;
	
	// Stack of active blocks during parsing
	std::stack<Block *> m_ctx;
	
	void parse();
public:
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
	
	/// Constructs a new module with a specified builder and filepath.
	Module(Builder* builder, std::string filePath);
};
