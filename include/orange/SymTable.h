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
	SymTable* m_parent = nullptr; 

	/** 
	 * Points to the table containing this one, if any.
	 * This is different than parent: parentage is set for 
	 * symbol tables that will inherit objects from their parents.
	 * 
	 * The container is just used to access the containing 
	 * symbol table for reasons other than inheritance. 
	 * In most castes, m_container == m_parent. 
	 */
	SymTable* m_container = nullptr; 

	/**
	 * Points to the structure of this symbol table.
	 * This can either be a function, if statement, for loop,
	 * or more. Traverse up the tree to find more.
	 */
	ASTNode *m_structure = nullptr;

	std::map<std::string, ASTNode *> m_objs;

	int m_ID = 0; 

	bool m_root = false;
public:
	/**
	 * Gets the parent symbol table of this one. 
	 * Returns nullptr if there is no parent.
	 *
	 * @return The parent symbol table, if it exists. 
	 */
	SymTable* parent() const;

	/**
	 * Gets the symbol table that this one is contained in.
	 * Returns nullptr if there is no containing table.
	 *
	 * @return The containing symbol table, if any. 
	 */
	SymTable* container() const; 

	/**
	 * Sets the parent symbol table of this one.
	 *
	 * @param parent The parent of this table.
	 */
	void setParent(SymTable* parent) { m_parent = parent; }

	/** 
	 * Sets the containing symbol table of this one.
	 *
	 * @param container The containing symbol table of this one. 
	 */
	void setContainer(SymTable* container) { m_container = container; }

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
	 * Finds an ASTNode in this tree by name, if it exists.
	 * Unlike find, findFromAny looks up the container tree.
	 *
	 * @param name The name of the ASTNode to find.
	 *
	 * @return The ASTNode in this symbol table.
	 */
	ASTNode* findFromAny(std::string name);

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

	/**
	 * Returns whether or not this symtab is meant to be the root.
	 */
	bool root() const;

	/**
	 * Constructs a new symbol table. If this table is meant to be used as the root 
	 * for all other tables, isRoot should be true. 
	 *
	 * @param isRoot Indicates whether or not this is the top-most symbol table. 
	 */
	SymTable(bool isRoot = false);

	/**
	 * Constructs a new symbol table, given a specific parent. Using this constructor 
	 * will set the containing symbol table to the parameter passed in here. 
	 *
	 * @param parent The parent symbol table. This value also sets container. 
	 */
	SymTable(SymTable *parent);

	/**
	 * Constructs a new symbol table, given a specific parent and container. 
	 * When using this constructor, both parent and container may be null. 
	 *
	 * @param parent The parent symbol table.
	 * @parem container The symbol table containing this newly constructed table. 
	 */
	SymTable(SymTable* parent, SymTable* container);
};

#endif 