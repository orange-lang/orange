/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/ExplicitDeclStmt.h>
#include <orange/VarExpr.h>
#include <orange/generator.h>

Value* ExplicitDeclStmt::Codegen() {
	// If we have an expression, cast it to the type of our variable and assign it.
	if (m_expr) {
		Value* value = m_expr->Codegen();

		// If the expr returns a pointer, don't load if LHS is a pointer and RHS is an array 
		bool doLoad = m_expr->returnsPtr();
		if (doLoad && m_var->getType()->isPointerTy() && m_expr->getType()->isArrayTy()) {
			doLoad = false;
		}

		if (doLoad) {
			value = GE::builder()->CreateLoad(value);
		}
		
		bool arrayToArray = m_expr->getType()->isArrayTy() && m_var->getType()->isArrayTy(); 

		if (arrayToArray == false) {
			bool casted = CastingEngine::CastValueToType(&value, m_var->getType(), m_var->isSigned(), true);
			if (casted == false) {
				throw CompilerMessage(*m_expr, "Could not cast expression to variable type!");
			}
		}


		m_var->allocate();
		GE::builder()->CreateStore(value, m_var->getValue());
	} else {
		// Otherwise, just allocate the variable.
		m_var->allocate();
	}

	// Do any initializations that we may need.
	m_var->initialize();
	return m_var->Codegen();
}

ASTNode* ExplicitDeclStmt::clone() {
	if (m_expr) {
		return new ExplicitDeclStmt((VarExpr*)m_var->clone(), (Expression*)m_expr->clone());
	} else {
		return new ExplicitDeclStmt((VarExpr*)m_var->clone());
	}
}

AnyType* ExplicitDeclStmt::getType() { 
	return m_var->getType(); 
}

bool ExplicitDeclStmt::isSigned() {
	return m_var->isSigned();
}

void ExplicitDeclStmt::resolve() {
	if (m_resolved) return;
	m_resolved = true; 

	m_var->resolve();
	m_var->create();

	if (m_var->getType()->isVariadicArray() && m_expr) {
		throw CompilerMessage(*m_var, "Variable-sized arrays may not be initialized");
	}

	if (m_expr) m_expr->resolve();
}

std::string ExplicitDeclStmt::string() {
	if (m_expr) {
		return m_var->string() + " = " + m_expr->string();
	} else {
		return m_var->string();
	}
}

ExplicitDeclStmt::ExplicitDeclStmt(VarExpr* var) {
	if (var == nullptr) {
		throw std::runtime_error("ExplicitDeclStmt ctor: var can not be null!");
	}

	m_var = var;
}

ExplicitDeclStmt::ExplicitDeclStmt(VarExpr* var, Expression* value) {
	if (var == nullptr) {
		throw std::runtime_error("ExplicitDeclStmt ctor: var can not be null!");
	}

	if (value == nullptr) {
		throw std::runtime_error("ExplicitDeclStmt ctor: value can not be null!");
	}

	m_var = var;
	m_expr = value; 
}