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

/*
	We want to be able to have debug mesages print out if the compiler is compiled with DEBUG set.
	If it's set, std::cout the string with DEBUG: prepended to it. Otherwise, don't do anything.
*/ 
#ifdef DEBUG
#define DEBUG_MSG(str) std::cout << "DEBUG: " << str << std::endl;
#else 
#define DEBUG_MSG(str) ;
#endif 

using namespace llvm;

// Forward declaration of a few classes that are used throughout AST.h
class Expression;
class ArgExpr;

/**
 * Gets the LLVM type from a string. The signed-ness of the string does not effect the outcome.
 *
 * @param typeStr The string to convert to an LLVM type.
 * @return An LLVM type generated from an Orange type in string format (e.g., "uint16", "float")
 */ 
Type *getType(std::string typeStr);

// std::vector<Expression *> is used throughout the AST, so create a shorter name for it here.
typedef std::vector<Expression *> ExprList;

/**
 * ASTNode is the base class for all structures in the AST. It provides some methods for pseudo-reflection and 
 * general features used throughout the project.
 */
class ASTNode {
protected:
	/** 
	 * Indicates whether or not this object has been resolved in the analysis pass.
	 */
	bool resolved = false;
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
	 * Indicates whether or not this object is to return a pointer to be loaded in. Always returns false 
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
	 * Resolves this object, intended for use during the analysis pass. This function's body 
	 * will only ever excecute once, to avoid unnecessary duplication of code.
	 */
	virtual void resolve() { 
		if (resolved)
			return; 
		resolved = true; 
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
	virtual bool isConstant() { return true; } 
};

/**
 * A list of ArgExpr that includes whether or not it's a variable argument list.
 */
class ArgList : public std::vector<ArgExpr *>  {
public:
	/**
	 * Determines whether or not this ArgList is a variable argument list (used in functions).
	 */ 
	bool isVarArg = false;

	/**
	 * Creates a allocated clone of this list. The result of this function call must be cleaned up
	 * manually to avoid memory links.
	 *
	 * @return A clone of this list.
	 */
	ArgList *clone();
};

#endif
