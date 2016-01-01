/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include <vector>
#include "Statement.h"

class Named;
namespace Orange { class Type; }

/**
 * Block is the base class for any element that holds a list of statements.
 */
class Block : public Statement {
private:
	std::vector<ASTNode *> m_statements;
	
	/// Returns the named node or a generic instance
	/// of the named node.
	Named* namedOrGenericInstance(Named* n, const Orange::Type* t,
								  const ASTNode* from) const;
	bool usable(Named* n, const ASTNode* from) const;
	Named* verify(Named* n, const ASTNode* from) const;
protected:
	void buildStatements();
	
	void copyStatements(const Block *orig);
public:
	std::vector<ASTNode *> getStatements() const;
	
	void addStatement(ASTNode* statement);
	void addStatement(ASTNode* statement, const ASTNode* ref, int delta);
	
	/// Determines whether or not this block has a named node by
	/// a given name.
	bool hasNamed(OString name, const ASTNode* limit,
				  SearchSettings settings) const;
	
	/// Returns a named node, if it exists, from this block with a specific
	/// name.
	/// @param name The name of the node to get.
	/// @param type Optional. The type of the node to get.
	/// @param from The node who is searching. Must be an immediate child.
	/// @param settings The settings to use.
	Named* getNamed(OString name, const Orange::Type* type, const ASTNode* from,
					SearchSettings settings) const;
	
	std::vector<Named *> getAllNamed(OString name, const ASTNode* from)
    	const;
	
	virtual ASTNode* copy() const override;
	
	virtual std::vector<ObjectBase**> getMemberNodes() override;
	
	virtual std::vector<std::vector<ObjectBase *>*> getMemberLists() override;
	
	virtual void build() override;
	
	/// Returns whether or not this block is a terminator.
	/// This block is a terminator when one of its immediate children is a
	/// terminator.
	virtual bool isTerminator() const override;
	
	Block();
	Block(Module* module);
	Block(const Block& other);
};
