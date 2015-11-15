/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include <vector>
#include "Statement.h"

class Named;
class Type;

/**
 * Block is the base class for any element that holds a list of statements.
 */
class Block : public Statement {
private:
	std::vector<ASTNode *> m_statements;
protected:
	void buildStatements();
public:
	std::vector<ASTNode *> getStatements() const;
	
	void addStatement(ASTNode* statement);
	
	/// Gets a Named node in the immediate list of children.
	/// (i.e., does not search the whole tree.)
	/// @param name The name of the node to look for.
	/// @param limit The child to stop searching at.
	Named* getNamed(std::string name, const ASTNode* limit) const;
	
	/// Gets a Named node in the immediate list of children.
	/// (i.e., does not search the whole tree.)
	/// @param name The name of the node to look for.
	/// @param candidates A list of candidates to help find the proper Node.
	/// @param limit The child to stop searching at.
	Named* getNamed(std::string name, std::vector<Type *> candidates,
					const ASTNode* limit) const;
	
	Block();
	Block(Module* module);
};
