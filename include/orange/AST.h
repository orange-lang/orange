/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __AST_H__
#define __AST_H__

#include <iostream>
#include <vector>
#include <sstream>
#include <stack>
#include <map>

#include <llvm/IR/DataLayout.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/CodeGen.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/PassManager.h>

// Include the casting engine so any class inheriting from AST has access to it.
#include "CastingEngine.h"
#include "CodeElement.h"
#include "OrangeTypes.h"

using namespace llvm;

class FunctionStmt;
class Block;
 
/**
 * ASTNode is the base class for all structures in the AST. It provides some methods for pseudo-reflection and 
 * general features used throughout the project.
 */
class ASTNode : public CodeElement {
protected:
	/**
	 * The internal value returned by Codegen() and getValue().
	 */
	Value *m_value = nullptr; 

	/** 
	 * Determines the type of the node. Used for caching. 
	 */
	OrangeTy* m_type = nullptr;

	/**
	 * The parent node that this node is stored inside, if any 
	 */
	ASTNode* m_parent = nullptr; 

	/**
	 * The dependency of this node.
	 */
	ASTNode* m_dependency = nullptr;

	/** 
	 * The children for this node, if any.
	 */
	std::vector<ASTNode *> m_children;

	std::string m_tag = ""; 

	/**
	 * Flag indicating whether or not this node is resolved.
	 */
	bool m_resolved = false;

	/**
	 * A unique identifier for this node. Resolved generic functions 
	 * have the same ID as their parent. 
	 */
	unsigned long m_ID = 0;

	/** 
	 * Adds a child to the list of children.
	 */
	void addChild(ASTNode* child);

	void addChild(std::string tag, ASTNode* child);
public:
	/**
	 * Gets the name of the class. Children classes will override this method to return the 
	 * names of their respective classes.
	 *
	 * @return The name of this class. Each instance of this class will return the same value.
	 */ 
	virtual std::string getClass() { return "ASTNode"; }

	unsigned long ID() const;

	std::string tag() const;

	void setTag(std::string tag);

	std::vector<ASTNode*> children() const; 

	std::vector<ASTNode*> siblings() const;

	bool contains(ASTNode* node);

	void copyProperties(ASTNode* from);

	ASTNode* dependency() const;

	bool resolved() const;

	/**
	 * Generates code in the current LLVM module for use with compilation. May not return anything.
	 *
	 * @return Returns a Value if the class is a child of Expression, nullptr otherwise.
	 */
	virtual Value* Codegen();

	/**
	 * Gets the value attributed to this object. This will usually be the value created 
	 * by Codegen().
	 *
	 * @return The Value attributed to this object.
	 */ 
	virtual Value* getValue();

	/**
	 * Sets the value attributed to this object. 
	 * @param value The new value for this object.
	 */
	virtual void setValue(Value* value);

	/**
	 * Creates a allocated clone of this object. The result of this function call must be cleaned up
	 * manually to avoid memory links. Cloned objects are not yet resolved.
	 *
	 * @return A clone of this object.
	 */
	virtual ASTNode* clone(); 

	/**
	 * Returns the string represenation of this object in code. This string is a full representation
	 * of the code with simplified syntax.
	 *
	 * @return The string representation of this object in code.
	 */  
	virtual std::string string(); 

	/**
	 * Indicates whether or not this object is to return a pointer to be loaded in by Codegen. Always returns false 
	 * for classes that inherit from Statement.
	 *
	 * @return Indicates whether or not the Codegen return value should be loaded in.
	 */
	virtual bool returnsPtr();

	/** 
	 * Indicates whether or not this statement is a Block. 
	 * Returns false except for any class inheriting from Block.
	 *
	 * @return True if this statement is a Block, false otherwise.
	 */
	virtual bool isBlock();

	/**
	 * Gets the type of this object. For most classes inheriting from Statement, the type will be 
	 * void. 
	 *
	 * @return The type of this object.
	 */
	virtual OrangeTy* getType() const;

	/**
	 * Gets the LLVM type of this object.
	 *
	 * @return The LLVM type of this object in code.
	 */
	Type* getLLVMType() const;

	/**
	 * @return The function this node is contained in.
	 */
	FunctionStmt* getContainingFunction();

	/**
	 * @return The parent Block 
	 */
	Block* parentBlock() const;

	/** 
	 * @return The parent of this node, if any.
	 */ 
	ASTNode* parent() const;

	/** 
	 * Set the parent for this node.
	 * @param parent The new parent.
	 */
	void setParent(ASTNode* parent);

	ASTNode* root() const; 

	virtual std::string dump();

	/**
	 * Populates the symbol table as appropriate for 
	 * this node and all of its children.
	 */
	virtual void initialize();

	/**
	 * Determines what node this node depends on being resolved.
	 */ 
	virtual void mapDependencies();

	/**
	 * Resolves this object, intended for use during the analysis pass. This function's body 
	 * will only ever excecute once, to avoid unnecessary duplication of code.
	 */
	virtual void resolve();

	/**
	 * Request a new ID.
	 */
	void newID();

	ASTNode();
	
	virtual ~ASTNode();
};

/**
 * Statement is a class used to represent structures in code that do not have values; 
 * if statements, for loops, functions, etc.
 */
class Statement : public ASTNode {
public:
	virtual std::string getClass() { return "Statement"; }
};

/**
 * Expression is a class used to represent code that do have values; assignments,
 * math, variable declarations, etc.
 */
class Expression : public ASTNode { 
public:
	virtual std::string getClass() { return "Expression"; }

	/**
	 * Indicates whether or not the result of the Codegen returns a signed expression.
	 *
	 * @return True if Codegen would return a signed expression, false otherwise.
	 */ 
	virtual bool isSigned() { return false; }

	/**
	 * Indicates whether or not the result of this expression is constant and is not 
	 * affected by other code. (e.g., does not load in any variables).
	 *
	 * @return True if Codegen would return a constant, false otherwise.
	 */
	virtual bool isConstant() { return false; } 
};

typedef std::vector<Expression *> ArgList; 

#endif
