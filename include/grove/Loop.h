/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "Block.h"

namespace llvm { class BasicBlock; }

class Expression;

class Loop : public Block
{
private:
	/// The initializer is a line of code executed before the loop begins.
	std::vector<ASTNode*> m_initializers;
	
	/// The condition detects whether or not to break out of our loop.
	Expression* m_condition = nullptr;
	
	/// The afterthought occurs after the loop body executes.
	ASTNode* m_afterthought = nullptr;
	
	llvm::BasicBlock* m_condition_block = nullptr;
	llvm::BasicBlock* m_body_block = nullptr;
	llvm::BasicBlock* m_afterthought_block = nullptr;
	llvm::BasicBlock* m_continue_block = nullptr;
	
	bool m_post_check = false;
	
	ASTNode* copyIfNonNull(ASTNode* node) const;
public:
	virtual ASTNode* copy() const override;
	
	virtual std::vector<ObjectBase**> getMemberNodes() override;
	
	virtual std::vector<std::vector<ObjectBase *>*> getMemberLists() override;
	
	std::vector<ASTNode*> getInitializers() const;
	Expression* getCondition() const;
	ASTNode* getAfterthought() const;
	
	void setInitializers(std::vector<ASTNode *> initializers);
	void setCondition(Expression* condition);
	void setAfterthought(ASTNode* afterthought);
	
	llvm::BasicBlock* getConditionBlock() const;
	llvm::BasicBlock* getBodyBlock() const;
	llvm::BasicBlock* getAfterthoughtBlock() const;
	llvm::BasicBlock* getContinueBlock() const;
	
	bool isPostCheck() const;
	
	virtual bool isTerminator() const override;
	
	/// Checks to make sure that condition is a boolean.
	virtual void resolve() override;
	virtual void build() override;
	
	Loop(std::vector<ASTNode*> initializer, Expression* condition,
		 ASTNode* afterthought, bool postCheck);
	Loop(const Loop& other);
};