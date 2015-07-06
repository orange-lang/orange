/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/IncrementExpr.h>
#include <orange/generator.h>

std::string IncrementExpr::string() {
	std::stringstream ss; 

	if (m_preincrement == true) ss << m_op; 
	ss << m_expr->string(); 
	if (m_preincrement == false) ss << m_op;
	return ss.str();
}

Value* IncrementExpr::Codegen() {
	Value* origValue = m_expr->Codegen();
	
	if (origValue == nullptr) {
		throw std::runtime_error("IncrementExpr::Codegen(): m_expr did not generate a value!");
	}
	
	Value* loadedVal = GE::builder()->CreateLoad(origValue);

	Value* newValue = nullptr;

	bool isFP = loadedVal->getType()->isFloatingPointTy();

	uint64_t delta = (m_op == "++") ? 1 : -1;  

	if (isFP) {
		newValue = GE::builder()->CreateFAdd(loadedVal, ConstantFP::get(loadedVal->getType(), delta));
	} else {
		newValue = GE::builder()->CreateAdd(loadedVal, ConstantInt::get(loadedVal->getType(), delta, true));	
	}

	GE::builder()->CreateStore(newValue, origValue);

	if (m_preincrement) {
		m_value = GE::builder()->CreateLoad(origValue);
	} else {
		m_value = loadedVal;
	}

	return m_value;
}

ASTNode* IncrementExpr::clone() {
	return new IncrementExpr((Expression *)m_expr->clone(), m_op, m_preincrement);
}

OrangeTy* IncrementExpr::getType() {
	return m_expr->getType();
}

void IncrementExpr::resolve() {
	ASTNode::resolve();

	if (m_expr->returnsPtr() == false) {
		throw CompilerMessage(*m_expr, "expression must be a variable or a memory location!");
	}
}


bool IncrementExpr::isSigned() {
	return m_expr->isSigned();
}

IncrementExpr::IncrementExpr(Expression* expression, StrElement op, bool preincrement) : m_op(op) {
	if (expression == nullptr) {
		throw std::runtime_error("IncrementExpr requires expression to not be null!");
	}

	m_expr = expression; 
	m_preincrement = preincrement; 

	addChild("m_expr", m_expr);
}
