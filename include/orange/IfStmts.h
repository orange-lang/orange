/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __IF_STMTS_H__
#define __IF_STMTS_H__

#include "AST.h"
#include "Block.h"

class IfStmts : public Statement {
private:
	/** 
	 * The list of blocks in this if statement.
	 */
	std::vector<Block *> m_blocks;

	/** 
	 * Indicates whether or not we can continue 
	 * adding blocks to this.
	 *
	 * This will be set to true when resolving, Codegenning, and 
	 * after a regular Block (not CondBlock) is added.
	 */
	bool m_locked;
public:
	virtual std::string getClass() { return "IfStmts"; }

	virtual Value* Codegen();

	virtual ASTNode* clone();

	virtual void resolve();

	/** 
	 * The blocks assigned to this if statement (ifs, else ifs, else).
	 * Only else statements return a Block. All other statements (ifs, else ifs) return 
	 * CondBlocks.
	 *
	 * @return The blocks assigned to this if statement.
	 */
	std::vector<Block *> blocks() const { return m_blocks; }

	/** 
	 * Add a block to this if statement. The block must either be a regular Block 
	 * or a CondBlock. If anything else is added, an exception will be thrown. 
	 * If a Block is added, it acts as the else statement and no other blocks can be 
	 * added. If addBlock is called again after adding a regular Block, an exception 
	 * will be thrown.
	 *
	 * @param block The block to add.
	 */ 
	void addBlock(Block *block);
};

#endif 