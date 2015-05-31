/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/TernaryExpr.h>
#include <orange/generator.h>

std::string TernaryExpr::string() {
	std::stringstream ss; 

	ss << m_condition->string() << " ? ";
	ss << m_true_expr->string() << " : "; 
	ss << m_false_expr->string();

	return ss.str();
}

Value* TernaryExpr::Codegen() { 
	Value* condition = m_condition->Codegen();

	if (condition == nullptr) {
		throw std::runtime_error("TernaryExpr::Codegen(): m_condition generated no value!");
	}

	if (CastingEngine::CastValueToType(&condition, IntTy::getUnsigned(1), m_condition->isSigned(), true) == false) {
		throw CompilerMessage(*m_condition, "could not cast to a boolean!");
	}

	// First, create a value to store the result. 
	Value* result = getType()->allocate();

	// Next, create two basic blocks and a continue block.
	auto trueBB = getContainingFunction()->createBasicBlock("ternaryTrue");
	auto falseBB = getContainingFunction()->createBasicBlock("ternaryFalse");
	auto continueBB = getContainingFunction()->createBasicBlock("ternaryContinue");

	// Now, create a BR. 
	GE::builder()->CreateCondBr(condition, trueBB, falseBB);

	// Finally, generate our expressions for true and false.

	// Generate our true block
	GE::builder()->SetInsertPoint(trueBB);

	Value* trueValue = m_true_expr->Codegen();

	if (m_true_expr->returnsPtr()) {
		trueValue = GE::builder()->CreateLoad(trueValue);
	}

	CastingEngine::CastValueToType(&trueValue, getType(), m_true_expr->isSigned(), true); 
	
	GE::builder()->CreateStore(trueValue, result);
	
	GE::builder()->CreateBr(continueBB);

	// Now, generate our false block
	GE::builder()->SetInsertPoint(falseBB);

	Value* falseValue = m_false_expr->Codegen();

	if (m_false_expr->returnsPtr()) {
		falseValue = GE::builder()->CreateLoad(falseValue);
	}

	CastingEngine::CastValueToType(&falseValue, getType(), m_false_expr->isSigned(), true); 
	
	GE::builder()->CreateStore(falseValue, result);
	
	GE::builder()->CreateBr(continueBB);

	// Now, set the current insert point to continue, load up our result variable and return that.
	GE::builder()->SetInsertPoint(continueBB);
	return GE::builder()->CreateLoad(result);
}

ASTNode* TernaryExpr::clone() { 
	return new TernaryExpr((Expression *)m_condition->clone(), (Expression *)m_true_expr->clone(), 
		(Expression *)m_false_expr->clone());
}

OrangeTy* TernaryExpr::getType() {
	return CastingEngine::GetFittingType(m_true_expr->getType(), m_false_expr->getType());
}

void TernaryExpr::resolve() { 
	if (m_resolved) return;
	m_resolved = true; 

	m_condition->resolve();
	m_true_expr->resolve();
	m_false_expr->resolve();

	// If the true and false expr types aren't compatible with one another, throw an error
	if (CastingEngine::AreTypesCompatible(m_true_expr->getType(), m_false_expr->getType()) == false) {
		std::string errorStr = "Types "; 
		errorStr += m_true_expr->getType()->string() + " and " + m_false_expr->getType()->string();
		errorStr += " can not be casted to fit!";
		throw CompilerMessage(*this, errorStr);
	}
}

bool TernaryExpr::isSigned() {
	return m_true_expr->isSigned() || m_false_expr->isSigned();
}

Expression* TernaryExpr::condition() {
	return m_condition;
}

Expression* TernaryExpr::trueExpression() {
	return m_true_expr;
}

Expression* TernaryExpr::falseExpression() {
	return m_false_expr; 
}

TernaryExpr::TernaryExpr(Expression* condition, Expression* trueExpr, Expression* falseExpr) {
	m_condition = condition;
	m_true_expr = trueExpr; 
	m_false_expr = falseExpr;

	m_condition->setParent(this);
	m_true_expr->setParent(this);
	m_false_expr->setParent(this);
}
