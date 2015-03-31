/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_BIN_OP_EXPR_H__
#define __ORANGE_BIN_OP_EXPR_H__

#include "AST.h"
#include "Values.h"

class BinOpExpr : public Expression {
private:
	Expression* m_LHS;
	Expression* m_RHS;  

	StrElement m_op;
protected:
	/**
	 * Returns true if and only if the left-hand side of 
	 * our expression should not be null as a requirement.
	 * If this returns false, LHS can either be null or not.
	 *
	 * @return Indicates whether or not LHS needs to have a value.
	 */
	bool LHSShouldNotBeNull(); 

	/**
	 * Returns true if and only if the right-hand side of 
	 * our expression should not be null as a requirement.
	 * If this returns false, RHS can either be null or not.
	 *
	 * @return Indicates whether or not RHS needs to have a value.
	 */	
	bool RHSShouldNotBeNull();

 	/**
 	 * Returns true if and only if the expression
 	 * is valid. This could return false for cases like "3 = 5". This 
 	 * method will throw an exception for the runner to catch.
 	 *
 	 * @return Indicates whether or not the expression is valid; i.e., without errors.
 	 */
	bool Validate(Value* LHS, Value* RHS); 
public:
	/**
	 * Returns true if op will assign a value to the LHS.
	 *
	 * @return True if op is an assign operator, false otherwise.
	 */
	static bool IsAssignOp(std::string op); 

	/** 
	 * Returns true if op is a comparison operator, comparing
	 * the LHS and RHS in some manner.
	 *
	 * @return True if op is a comparison operator, false otherwise.
	 */
	static bool IsCompareOp(std::string op);

	/**
	 * Gets the LLVM binary ops function from two values.
	 *
	 * @param value1 The first value to use.
	 * @param op The operator to use.
	 * @param value2 The second value to use.
	 * 
	 * @return The LLVM binary ops function.
	 */
	static Instruction::BinaryOps GetBinOpFunction(Value* value1, bool signed1, StrElement op, Value* value2, bool signed2);
	static CmpInst::Predicate GetBinOpPredComp(Value* value1, bool signed1, StrElement op, Value* value2, bool signed2);

	virtual std::string getClass() { return "BinOpExpr"; }

	virtual Value* Codegen();

	virtual ASTNode* clone() {
		return new BinOpExpr((Expression*)m_LHS->clone(), m_op, (Expression*)m_RHS->clone());
	}

	virtual std::string string();

	virtual Type* getType();

	virtual void resolve();

	virtual bool isSigned();
	virtual bool isConstant();

	/**
	 * Constructs a new Binary Operator Expression.
	 *
	 * @param LHS The left hand side of the expression.
	 * @param op The operator string (e.g., +, -, etc).
	 * @param RHS The right hand side of the expression.
	 */
	BinOpExpr(Expression* LHS, StrElement op, Expression* RHS);
};

#endif 