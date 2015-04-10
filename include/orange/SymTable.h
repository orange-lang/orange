/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_SYMTAB_H__
#define __ORANGE_SYMTAB_H__

#include "AST.h"

class SymTable {
private:
	SymTable *m_parent = nullptr; 

	/**
	 * Points to the structure of this symbol table.
	 * This can either be a function, if statement, for loop,
	 * or more. Traverse up the tree to find more.
	 */
	ASTNode *m_structure = nullptr;

	std::map<std::string, ASTNode *> m_objs;

	int m_ID = 0; 
public:
	/**
	 * Gets the parent symbol table of this one. 
	 * Returns nullptr if there is no parent.
	 *
	 * @return The parent symbol table, if it exists. 
	 */
	SymTable* parent() const;

	/**
	 * Sets the parent symbol table of this one.
	 *
	 * @param parent The parent of this table.
	 */
	void setParent(SymTable* parent) { m_parent = parent; }

	/**
	 * Registers an ASTNode in this table by name, if an 
	 * ASTNode by that name doesn't already exist.
	 *
	 * @param name The name to assign to the node. 
	 * @param node The node to register.
	 *
	 * @return true if it was created, false if one by that name exists.
	 */
	bool create(std::string name, ASTNode* node);

	/**
	 * Find a ASTNode in this tree by name, if it exists.
	 *
	 * @param name The name of the ASTNode to find.
	 *
	 * @return The ASTNode in this symbol table.
	 */
	ASTNode* find(std::string name);

	/**
	 * Finds the closest ASTNode of a certain class.
	 *
	 * @return The ASTNode, if it exists. nullptr otherwise. 
	 */ 
	ASTNode* findStructure(std::string className);

	/**
	 * Sets the structure for this SymTable.
	 *
	 * @param structure The structure to set.
	 */
	void setStructure(ASTNode* structure);

	/**
	 * Creates a clone of this symbol table. 
	 *
	 * @return A clone of this symbol table.
	 */
	SymTable* clone();

	/**
	 * Gets the ID of this symbol table.
	 *
	 * @return The ID of this symbol table.
	 */
	int ID() const; 

	SymTable();
	SymTable(SymTable *parent);
};

#endif 