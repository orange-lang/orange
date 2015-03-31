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

#include <llvm/Analysis/Passes.h>
#include <llvm/IR/DataLayout.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/PassManager.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/CodeGen.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/Transforms/Scalar.h>

using namespace llvm;

class CodeLocation {
public:
	int row_begin = 0, row_end = 0;
	int col_begin = 0, col_end = 0;
};

/**
 * ASTNode is the base class for all structures in the AST. It provides some methods for pseudo-reflection and 
 * general features used throughout the project.
 */
class ASTNode {
protected:
	/** 
	 * Indicates whether or not this object has been resolved in the analysis pass.
	 */
	bool m_resolved = false;

	/**
	 * The internal value returned by Codegen() and getValue().
	 */
	Value *m_value = nullptr; 

	/**
	 * Indicates where the code is located in a file.
	 */
	CodeLocation m_location;
public:
	/**
	 * Gets the name of the class. Children classes will override this method to return the 
	 * names of their respective classes.
	 *
	 * @return The name of this class. Each instance of this class will return the same value.
	 */ 
	virtual std::string getClass() { return "ASTNode"; }

	/**
	 * Generates code in the current LLVM module for use with compilation. May not return anything.
	 *
	 * @return Returns a Value if the class is a child of Expression, nullptr otherwise.
	 */
	virtual Value* Codegen() { return nullptr; }	

	/**
	 * Gets the value attributed to this object. This will usually be the value created 
	 * by Codegen().
	 *
	 * @return The Value attributed to this object.
	 */ 
	virtual Value* getValue() { return m_value; }

	/**
	 * Creates a allocated clone of this object. The result of this function call must be cleaned up
	 * manually to avoid memory links. Cloned objects are not yet resolved.
	 *
	 * @return A clone of this object.
	 */
	virtual ASTNode* clone() { return new ASTNode(); }

	/**
	 * Returns the string represenation of this object in code. This string is a full representation
	 * of the code with simplified syntax.
	 *
	 * @return The string representation of this object in code.
	 */  
	virtual std::string string() { return ""; }

	/**
	 * Indicates whether or not this object is to return a pointer to be loaded in by Codegen. Always returns false 
	 * for classes that inherit from Statement.
	 *
	 * @return Indicates whether or not the Codegen return value should be loaded in.
	 */
	virtual bool returnsPtr() { return false; }

	/**
	 * Gets the LLVM type of this object. For classes inheriting from Statement, the type will 
	 * be void, as getType() only returns a value if it is to be used as part of an expression.
	 *
	 * @return The LLVM type of this object in code.
	 */
	virtual Type *getType() { return Type::getVoidTy(getGlobalContext()); }

	/**
	 * Gets the current code location
	 *
	 * @return The location where this fragment of code resides.
	 */
	CodeLocation location() const { return m_location; }

	/**
	 * Sets the code location
	 *
	 * @param location The new location to use.
	 */
	void setLocation(CodeLocation location) { m_location = location; }  
	
	/**
	 * Resolves this object, intended for use during the analysis pass. This function's body 
	 * will only ever excecute once, to avoid unnecessary duplication of code.
	 */
	virtual void resolve() { 
		if (m_resolved)
			return; 
		m_resolved = true; 
	};

	virtual ~ASTNode() { };
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
	 * affected by other code. (e.g., does not load in any varaibles).
	 *
	 * @return True if Codegen would return a constant, false otherwise.
	 */
	virtual bool isConstant() { return false; } 
};


#endif
