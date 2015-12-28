/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "Block.h"

class Expression;

/**
 * CondBlocks are regular blocks with expressions to define a condition.
 * They are meant to be used by structures who contain blocks that need 
 * a condition, such as if statements.
 */
class CondBlock : public Block
{
private:
	Expression* m_expr = nullptr;
	bool m_invert = false;
public:
	virtual void resolve() override;
	
	Expression* getExpression() const;
	
	virtual ASTNode* copy() const override;
	
	virtual std::vector<ObjectBase**> getMemberNodes() override;
	
	virtual std::vector<std::vector<ObjectBase *>*> getMemberLists() override;
	
	bool invertCondition() const; 
	
	CondBlock(Expression* expr, bool invert = false);
	CondBlock(const CondBlock& other);
};
