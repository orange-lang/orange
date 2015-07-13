/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/FuncCall.h>
#include <orange/generator.h>
#include <orange/ExternFunction.h>

Value* FuncCall::Codegen() {
	SymTable *curTab = GE::runner()->symtab();
	
	auto function = curTab->findFromAny(m_name, this); 

	if (function == nullptr) {
		throw CompilerMessage(*this, "No function " + m_name + " found!");
	}

	if (function->getClass() != "FunctionStmt" && function->getClass() != "ExternFunction") {
		throw CompilerMessage(*this, m_name + " is not a function!");
	}

	Function* llvmFunction = (Function*) function->getValue();

	if (llvmFunction == nullptr) {
		throw CompilerMessage(*this, "No function " + m_name + " generated!");
	}

	if (llvmFunction->isVarArg() == false && llvmFunction->arg_size() != m_arguments.size()) {
		throw CompilerMessage(*this, "Invalid number of arguments");
	} else if (llvmFunction->isVarArg() && m_arguments.size() == 0) {
		throw CompilerMessage(*this, "Must have at least one argument in a variable argument call!");		
	}

	ParamList parameters; 

	if (function->getClass() == "FunctionStmt") {
		parameters = ((FunctionStmt*)function)->parameters();
	} else {
		parameters = ((ExternFunction*)function)->parameters();
	}

	if (m_arguments.size()) {
		std::vector<Value*> Args;

		for (unsigned int i = 0; i < parameters.size(); i++) {
			Value* vArg = m_arguments[i]->Codegen();

			if (vArg == nullptr) {
				throw CompilerMessage(*m_arguments[i], "codegen returned nothing!");
			}

			if (m_arguments[i]->returnsPtr() && m_arguments[i]->getType()->isArrayTy() == false) {
				vArg = GE::builder()->CreateLoad(vArg);
			}

			m_arguments[i]->cast(&vArg, parameters[i]->getType(), true);
			Args.push_back(vArg);
		}

		// If we're calling a variable argument function, add our other arguments.
		if (llvmFunction->isVarArg()) {
			for (unsigned int i = llvmFunction->arg_size(); i < m_arguments.size(); i++) {
				Value *vArg = m_arguments[i]->Codegen();
				
				if (vArg == nullptr) {
					throw std::runtime_error("FuncCall::Codegen(): m_arguments[i] did not generate a value!");
				}

				if (m_arguments[i]->returnsPtr()) {
					vArg = GE::builder()->CreateLoad(vArg);
				}

				Args.push_back(vArg);			
			}
		}

		m_value = GE::builder()->CreateCall(llvmFunction, Args);
	} else {
		m_value = GE::builder()->CreateCall(llvmFunction);
	}

	return m_value;
}

ASTNode* FuncCall::clone() {
	FuncCall* cloned = new FuncCall(m_name);

	for (auto arg : m_arguments) {
		cloned->m_arguments.push_back((Expression*)arg->clone());
	}

	cloned->copyProperties(this);
	return cloned; 
}

std::string FuncCall::string() {
	std::stringstream ss;
	ss << m_name << "(";

	for (unsigned int i = 0; i < m_arguments.size(); i++) {
		ss << " " << m_arguments[i]->string() << " ";
		if (i+1 < m_arguments.size()) {
			ss << ",";
		}
	}

	ss << ")";
	return ss.str();
}

void FuncCall::mapDependencies() {
	ASTNode::mapDependencies();

	SymTable *curTab = GE::runner()->symtab();
	ASTNode* function = curTab->findFromAny(m_name, this); 

	if (function == nullptr) {
		throw CompilerMessage(*this, "No function " + m_name + " found!");
	}

	if ((function->getClass() != "FunctionStmt" &&
		function->getClass() != "ExternFunction")) {
		throw CompilerMessage(*this, m_name + " is not a function!");
	}

	// The dependency here may be a generic function. 
	// In which case, we will not be able to know which clone 
	// we are depending on. This is not an issue, however, since 
	// by the time dependencies are being resolved for this function 
	// call, the function will have already been marked as resolved. 
	m_dependency = function; 
}

void FuncCall::resolve() {
	if (m_resolved) return; 
	m_resolved = true;

	if (m_dependency) m_dependency->resolve();

	// Look for the function in the symbol table.
	SymTable *curTab = GE::runner()->symtab();
	ASTNode* function = curTab->findFromAny(m_name, this); 

	if (function == nullptr) {
		throw CompilerMessage(*this, "No function " + m_name + " found!");
	}

	if ((function->getClass() != "FunctionStmt" &&
		function->getClass() != "ExternFunction")) {
		throw CompilerMessage(*this, m_name + " is not a function!");
	}

	for (auto arg : m_arguments) arg->resolve();

	// Call resolve on the clone, since we're the one that creates it. 
	if (function->getClass() == "FunctionStmt") {
		FunctionStmt* fstmt = (FunctionStmt*)function;
		if (fstmt->isGeneric()) {
			bool shouldResolve = fstmt->getGenericClone(m_arguments) == nullptr;

			FunctionStmt* clone = fstmt->createGenericClone(m_arguments);
			m_name = clone->name();
			function = clone;

			if (shouldResolve) clone->resolve();
		}
	}

	m_type = function->getType();

	if (m_type == nullptr) {
		throw CompilerMessage(*this, "Ambiguous return type");
	}
}

bool FuncCall::isSigned() {
	// This will need to be dynamic at some point.
	return false; 
}

FuncCall::FuncCall(std::string name) : m_name(name) {

}

FuncCall::FuncCall(std::string name, ArgList arguments) : m_name(name), m_arguments(arguments) {
	for (auto arg : m_arguments) {
		addChild(arg);
	}
}
