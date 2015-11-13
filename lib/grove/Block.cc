/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/Block.h>

std::vector<ASTNode *> Block::getStatements() const
{
	return m_statements;
}

void Block::addStatement(ASTNode *statement)
{
	if (statement == nullptr)
	{
		throw std::invalid_argument("statement cannot be null.");
	}
	
	m_statements.push_back(statement);
}

Block::Block()
: Statement()
{
	// Do nothing
}

Block::Block(Module* module)
: Statement(module)
{
	// Do nothing 
}