/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "Expression.h"

#include <vector>

namespace llvm { class Function; }

class FunctionType;

/**
 * Calls an expression (if it is a function type)
 * as a function.
 */
class ExpressionCall : public Expression
{
private:
	/// The expression to call. Note here it's just
	/// an instance of Valued as we don't necessarily
	/// need an expression.
	ASTNode* m_expr = nullptr;
	
	FunctionType* m_function_ty = nullptr;
	
	void assertCallingFunction(llvm::Value* function);
protected:
	void setExpr(ASTNode* expr);
	
	std::vector<Expression *> m_args;
	
	const FunctionType* getFunctionTy() const;
	
	/// Construct a new ExpressionCall without an expression,
	/// which can be set by child classes during resolve.
	ExpressionCall(std::vector<Expression *> args);
public:
	/// Returns the function type this expression expects.
	FunctionType* expectedFunctionTy() const;
	
	/// Gets the expression we're calling as a valued node.
	const Valued* exprAsValued() const;
	
	/// Gets the expression we're calling as a typed node.
	const Typed* exprAsTyped() const;
	
	/// Gets the expression we're calling.
	const ASTNode* getExpr() const;
	
	/// Adds an argument to the list of arguments.
	/// @param arg The argument to add. This class will take ownership.
	/// @param idx The index to add. If -1, adds to the end.
	void addArgument(Expression* arg, int idx = -1);
	
	/// Gest the arguments in this expression call.
	std::vector<Expression *> getArgs() const;
	
	virtual void findDependencies() override;
	
	virtual void resolve() override;
	virtual void build() override;
	
	virtual ASTNode* copy() const override;
	
	virtual std::vector<ObjectBase**> getMemberNodes() override;
	
	virtual std::vector<std::vector<ObjectBase *>*> getMemberLists() override;
	
	/// Constructs a new expression call.
	/// @param expr A node. Expected implement Typed and Valued.
	/// @param args The argument list for this call.
	ExpressionCall(ASTNode* expr, std::vector<Expression *> args,
				   bool addAsChild = false);
	ExpressionCall(const ExpressionCall& other);
};