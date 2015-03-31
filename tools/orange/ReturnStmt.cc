/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/ReturnStmt.h>
#include <orange/generator.h>
#include <orange/SymTable.h>

Value* ReturnStmt::Codegen() {
	SymTable *curTab = GE::runner()->topBlock()->symtab();
	FunctionStmt *containingFunc = (FunctionStmt *)curTab->findStructure("FunctionStmt");

	Value* retVal = containingFunc->getRetVal();

	if (retVal == nullptr && containingFunc->getType()->isVoidTy() == false) {
		throw std::runtime_error("Internal compiler error: ret val is nullptr when it should not be!");
	}

	Value* retExpr = nullptr;

	// Cast our return value to the return type of the function, if needed.
	if (m_expr) {
		retExpr = m_expr->Codegen();

		if (m_expr->returnsPtr()) retExpr = GE::builder()->CreateLoad(retExpr);

		CastingEngine::CastValueToType(&retExpr, containingFunc->getType(), m_expr->isSigned(), true);

		// Store it and jump to the end block.
		GE::builder()->CreateStore(retExpr, retVal);
	}

	GE::builder()->CreateBr(containingFunc->getBlockEnd());

	return retExpr; 
}

AnyType* ReturnStmt::getType() {
	if (m_expr) return m_expr->getType();
	return AnyType::getVoidTy();
}

void ReturnStmt::resolve() {
	if (m_resolved) return;
	m_resolved = true; 

	if (m_expr) m_expr->resolve();
	
	// Find our parent function...
	SymTable *curTab = GE::runner()->topBlock()->symtab();
	FunctionStmt *containingFunc = (FunctionStmt *)curTab->findStructure("FunctionStmt");

	if (m_expr && containingFunc->getType()->isVoidTy()) {
		throw CompilerMessage(*m_expr, "Returning value in a void function.");
	} else if (containingFunc->getType()->isVoidTy() == false && m_expr == nullptr) {
		throw std::runtime_error("Returning void in a function that expects a value.");
	}

	if (m_expr) {
		if (m_expr->getType() == nullptr) {
			throw CompilerMessage(*m_expr, "Compiler error: expression has no type.");
		}

		if (CastingEngine::AreTypesCompatible(m_expr->getType(), containingFunc->getType()) == false) {
			std::cout << m_expr->getType()->string() << std::endl;
			std::cout << containingFunc->getType()->string() << std::endl;

			throw CompilerMessage(*m_expr, "Cannot convert return value to function return type.");
		}
	}
}