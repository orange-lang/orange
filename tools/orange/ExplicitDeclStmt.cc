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

Value* ExplicitDeclStmt::CodegenPair(VarExpr* var, Expression* expr) {
	// If we have an expression, cast it to the type of our variable and assign it.
	if (var->getType()->isVarTy()) {
		throw CompilerMessage(*var, "var type never given a value");
	}

	if (expr) {
		Value* value = expr->Codegen();

		// If the expr returns a pointer, don't load if LHS is a pointer and RHS is an array 
		bool doLoad = expr->returnsPtr();
		if (doLoad && var->getType()->isPointerTy() && expr->getType()->isArrayTy()) {
			doLoad = false;
		}

		if (doLoad) {
			value = GE::builder()->CreateLoad(value);
		}
		
		bool arrayToArray = expr->getType()->isArrayTy() && var->getType()->isArrayTy(); 

		if (arrayToArray == false) {
			bool casted = CastingEngine::CastValueToType(&value, var->getType(), var->isSigned(), true);
			if (casted == false) {
				throw CompilerMessage(*expr, "Could not cast expression to variable type!");
			}
		}

		var->allocate();

		GE::builder()->CreateStore(value, var->getValue());
	} else {
		// Otherwise, just allocate the variable.
		var->allocate();
	}

	m_value = var->Codegen();
	return m_value;
}

Value* ExplicitDeclStmt::Codegen() {
	auto retVal = CodegenPair(m_var, m_expr);

	// Codegen our extra pairs.
	for (auto pair : m_extras) {
		CodegenPair(pair.var, pair.val);
	}

	// Only return the first variable.
	return retVal;
}

ASTNode* ExplicitDeclStmt::clone() {
	std::vector<DeclPair> extraClones;

	for (auto pair : m_extras) {
		extraClones.push_back(DeclPair(pair.var->name(), (Expression *)pair.val->clone()));
	}

	if (m_expr) {
		return new ExplicitDeclStmt((VarExpr*)m_var->clone(), (Expression*)m_expr->clone(), extraClones);
	} else {
		return new ExplicitDeclStmt((VarExpr*)m_var->clone(), extraClones);
	}
}

OrangeTy* ExplicitDeclStmt::getType() { 
	return m_var->getType(); 
}

bool ExplicitDeclStmt::isSigned() {
	return m_var->isSigned();
}

void ExplicitDeclStmt::resolve() {
	ASTNode::resolve();
	m_var->create();

	if (m_var->getType()->isVoidTy()) {
		throw CompilerMessage(*m_var, "keyword void cannot be used to create a variable");
	}
	
	if (m_var->getType()->isVarTy() && m_expr) {
		m_var->setType(m_expr->getType());
		m_var->resolve(); 
	} 

	if (m_var->getType()->isVariadicArray() && m_expr) {
		throw CompilerMessage(*m_var, "Variable-sized arrays may not be initialized");
	}

	for (auto pair : m_extras) {
		pair.var->create();
		
		if (pair.var->getType()->isVoidTy()) {
			throw CompilerMessage(*m_var, "keyword void cannot be used to create a variable");
		}

		if (pair.var->getType()->isVarTy() && pair.val) {
			pair.var->setType(pair.val->getType()); 
			pair.var->resolve(); // type has changed; re-resolve the variable 
		}

		if (pair.var->getType()->isVariadicArray() && pair.val) {
			throw CompilerMessage(*pair.var, "Variable-sized arrays may not be initialized");
		}
	}
}

std::string ExplicitDeclStmt::string() {
	std::stringstream ss; 

	if (m_expr) {
		ss << m_var->string() << " = " << m_expr->string();
	} else {
		ss << m_var->string();
	}

	for (auto pair : m_extras) {
		ss << "\n";

		if (pair.val) {
			ss << pair.var->string() << " = " << pair.val->string(); 
		} else {
			ss << pair.var->string();
		}
	}
	
	return ss.str();
}

ExplicitDeclStmt::ExplicitDeclStmt(VarExpr* var) {
	if (var == nullptr) {
		throw std::runtime_error("ExplicitDeclStmt ctor: var can not be null!");
	}

	m_var = var;
}

ExplicitDeclStmt::ExplicitDeclStmt(VarExpr* var, std::vector<DeclPair> extras) {
	if (var == nullptr) {
		throw std::runtime_error("ExplicitDeclStmt ctor: var can not be null!");
	}

	m_var = var;

	auto typeForExtras = m_var->getType();

	for (auto pair : extras) {
		m_extras.push_back(DeclPairInternal(new VarExpr(pair.name, typeForExtras), pair.expression));
	}	
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

ExplicitDeclStmt::ExplicitDeclStmt(VarExpr* var, Expression* value, std::vector<DeclPair> extras) {
	if (var == nullptr) {
		throw std::runtime_error("ExplicitDeclStmt ctor: var can not be null!");
	}

	if (value == nullptr) {
		throw std::runtime_error("ExplicitDeclStmt ctor: value can not be null!");
	}

	m_var = var;
	m_expr = value; 

	addChild("m_var", m_var);
	addChild("m_expr", m_expr);

	auto typeForExtras = m_var->getType();


	for (unsigned int i = 0; i < extras.size(); i++) {
		auto pair = extras[i];

		auto newVar = new VarExpr(pair.name, typeForExtras); 

		{
			std::stringstream ss; 
			ss << "var" << i;
			addChild(ss.str(), newVar);
		}

		{
			std::stringstream ss;
			ss << "expr" << i;
			addChild(ss.str(), pair.expression);
		}

		m_extras.push_back(DeclPairInternal(newVar, pair.expression));
	}
}
