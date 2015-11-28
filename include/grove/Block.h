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
	
	/// Returns the named node or a generic instance
	/// of the named node.
	Named* namedOrGenericInstance(Named* n, Type* t) const;
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
	
	/**
	 * Tries to find a Named node in the immediate list of chidlren. Does 
	 * not search the whole tree.
	 *
	 * Unlike getNamed(OString, const ASTNode*), this function allows
	 * for a type hint to be passed in. It is used to narrow down results 
	 * in the case of multiple nodes with the same name being found. The hint
	 * can be a compound type (e.g., FunctionType) or a regular type (e.g.,
	 * IntType). VarType can be used as a wildcard. If the hint provided 
	 * leaves 0 or more than 1 results, an error is thrown, but only if 
	 * hint was used.
	 *
	 * Hint is only used if multiple nodes are found by name. 
	 *
	 * @param name The name of the node to look for.
	 * @param hint The type hint to narrow down search results. 
	 * @param limit The child to stop searching at, if any. 
	 *
	 * @return The named node, if one was found. 
	 *
	 * @throws Throws an exception if multiple nodes with the same name 
	 * were found, and using hint does not narrow down results to exactly 
	 * ony node.
	 */
	Named* getNamed(OString name, Type* type, const ASTNode* limit,
					SearchSettings settings) const;
	
	/**
	 * Tries to find all named nodes with a given name from the immediate 
	 * list of children. Does not search the whole tree.
	 */
	std::vector<Named *> getAllNamed(OString name, const ASTNode* limit)
    	const;
	
	virtual ASTNode* copy() const override;
	
	virtual void build() override;
	
	/// Returns whether or not this block is a terminator.
	/// This block is a terminator when one of its immediate children is a
	/// terminator.
	virtual bool isTerminator() const override;
	
	Block();
	Block(Module* module);
};
