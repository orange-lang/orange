/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/FuncCall.h>
#include <orange/generator.h>

Value* FuncCall::Codegen() {
	SymTable *curTab = GE::runner()->symtab();
	FunctionStmt* function = (FunctionStmt*)curTab->find(m_name); 

	return GE::builder()->CreateCall(function->getValue());
}

ASTNode* FuncCall::clone() {
	FuncCall* cloned = new FuncCall(m_name);
	return cloned; 
}

std::string FuncCall::string() {
	return m_name + "()";
}

AnyType* FuncCall::getType() {
	SymTable *curTab = GE::runner()->symtab();
	FunctionStmt* function = (FunctionStmt*)curTab->find(m_name); 
	return function->getType();
}

void FuncCall::resolve() {
	if (m_resolved) return;
	m_resolved = true;

	// Look for the function in the symbol table.
	SymTable *curTab = GE::runner()->symtab();
	ASTNode* function = curTab->find(m_name); 

	if (function == nullptr || (function->getClass() != "FunctionStmt" &&
		function->getClass() != "ExternFunctionStmt")) {
		throw CompilerMessage(*this, m_name + " is not a function!");
	}

	// TODO: create clone of function if needed (for generics).
}

bool FuncCall::isSigned() {
	// This will need to be dynamic at some point.
	return false; 
}

FuncCall::FuncCall(std::string name) : m_name(name) {}