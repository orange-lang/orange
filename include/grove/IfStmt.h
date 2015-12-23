/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "Statement.h"

#include <vector>

class Block;
class CondBlock;

namespace llvm { class BasicBlock; }
namespace llvm { class Value; }

/**
 * IfStmt represents all if, else if, and else statements with their blocks.
 *
 */
class IfStmt : public Statement
{
private:
	std::vector<Block *> m_if_blocks;
	std::vector<llvm::BasicBlock *> m_blocks;
	
	llvm::BasicBlock* m_continue_block = nullptr;
protected:
	llvm::Value* getCond(CondBlock* block);
	bool isElse(Block* block);
public:
	/// Gets all if statements.
	std::vector<Block *> getBlocks() const;
	
	/// Gets all LLVM blocks.
	std::vector<llvm::BasicBlock *> getLLVMBlocks() const;
	
	/// Gets the continue block.
	llvm::BasicBlock* continueBlock() const;
	
	/// Adds a block to the list of conditional blocks.
	void addBlock(Block* block);
	
	/// Determines whether or not there is an else statement.
	bool hasElse() const;
	
	/// Returns whether or not this if statement is a terminator.
	/// It will only be a terminator if every one of the blocks is a
	/// terminator.
	virtual bool isTerminator() const override;
	
	virtual ASTNode* copy() const override;
	
	virtual void resolve() override;
	virtual void build() override;
	
	IfStmt();
	IfStmt(const IfStmt& other);
};