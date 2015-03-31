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
	Function* llvmFunction = (Function*) function->getValue();

	if (llvmFunction->arg_size() != m_arguments.size()) {
		throw CompilerMessage(*this, "Invalid number of arguments");
	}

	if (m_arguments.size()) {
		std::vector<Value*> Args;

		auto arg_it = llvmFunction->arg_begin();
		for (unsigned int i = 0; i < llvmFunction->arg_size(); i++, arg_it++) {
			Value *vArg = m_arguments[i]->Codegen();
			AnyType* anyType = new AnyType(arg_it->getType());
			CastingEngine::CastValueToType(&vArg, anyType, m_arguments[i]->isSigned(), true);
			delete anyType;
			Args.push_back(vArg);
		}


		return GE::builder()->CreateCall(llvmFunction, Args);
	} else {
		return GE::builder()->CreateCall(llvmFunction);
	}

}

ASTNode* FuncCall::clone() {
	FuncCall* cloned = new FuncCall(m_name);
	return cloned; 
}

std::string FuncCall::string() {
	std::stringstream ss;
	ss << m_name << "(";

	for (int i = 0; i < m_arguments.size(); i++) {
		ss << " " << m_arguments[i]->string() << " ";
		if (i+1 < m_arguments.size()) {
			ss << ",";
		}
	}

	ss << ")";
	return ss.str();
}

AnyType* FuncCall::getType() {
	SymTable *curTab = GE::runner()->symtab();
	FunctionStmt* function = (FunctionStmt*)curTab->find(m_name); 

	if (function == nullptr) {
		throw CompilerMessage(*this, "Function does not exist!");
	}

	return function->getType();
}

void FuncCall::resolve() {
	if (m_resolved) return;
	m_resolved = true;

	// Look for the function in the symbol table.
	SymTable *curTab = GE::runner()->symtab();
	ASTNode* function = curTab->find(m_name); 

	if (function == nullptr) {
		throw CompilerMessage(*this, "No function " + m_name + " found!");
	}

	if ((function->getClass() != "FunctionStmt" &&
		function->getClass() != "ExternFunction")) {
		throw CompilerMessage(*this, m_name + " is not a function!");
	}

	for (auto arg : m_arguments) arg->resolve();

	// TODO: create clone of function if needed (for generics).
}

bool FuncCall::isSigned() {
	// This will need to be dynamic at some point.
	return false; 
}

FuncCall::FuncCall(std::string name) : m_name(name) {}
FuncCall::FuncCall(std::string name, ArgList arguments) : m_name(name), m_arguments(arguments) {}
