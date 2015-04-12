/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __COND_BLOCK_H__
#define __COND_BLOCK_H__

#include "Block.h"

class CondBlock : public Block {
private:
	Expression* m_condition; 
	bool m_inverted = false;
public:
	virtual std::string getClass() { return "CondBlock"; }

	Expression* condition() const { return m_condition; }

	bool inverted() const { return m_inverted; }

	/** 
	 * Codegen the condition assigned to this block, but NOT any of the statements. 
	 *
	 * @return Returns the LLVM value for this generated condition.
	 */
	virtual Value* CodegenCondition();

	virtual ASTNode* clone();

	virtual void resolve();

	CondBlock(Expression* condition, SymTable* tab, bool inverted = false);
};

#endif 