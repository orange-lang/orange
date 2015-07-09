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
	
	FunctionStmt* function = (FunctionStmt*)curTab->findFromAny(m_name); 

	if (function == nullptr) {
		throw CompilerMessage(*this, "No function " + m_name + " found!");
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

	if (m_arguments.size()) {
		std::vector<Value*> Args;

		auto arg_it = llvmFunction->arg_begin();
		for (unsigned int i = 0; i < llvmFunction->arg_size(); i++, arg_it++) {
			Value *vArg = m_arguments[i]->Codegen();

			if (vArg == nullptr) {
				throw CompilerMessage(*m_arguments[i], "codegen returned nothing!");
			}

			if (m_arguments[i]->returnsPtr() && m_arguments[i]->getType()->isArrayTy() == false) {
				vArg = GE::builder()->CreateLoad(vArg);
			}

			OrangeTy* ty = OrangeTy::getFromLLVM(arg_it->getType(), m_arguments[i]->isSigned());

			CastingEngine::CastValueToType(&vArg, ty, m_arguments[i]->isSigned(), true);
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

OrangeTy* FuncCall::getType() {
	SymTable* curTab = GE::runner()->symtab();
  ASTNode* node = curTab->findFromAny(m_name);
  
  if (node == nullptr) {
      throw CompilerMessage(*this, m_name + " does not exist!");
  }
  
  if ((node->getClass() != "FunctionStmt" &&
       node->getClass() != "ExternFunction")) {
      throw CompilerMessage(*this, m_name + " is not a function!");
  }
    
	if (node->getClass() == "FunctionStmt" && ((FunctionStmt*)node)->isGeneric()) {
		// Try resolving...
		throw CompilerMessage(*this, "Can't get the type of an unresolved generic function.");
	}

	return node->getType();
}

void FuncCall::resolve() {
	// Look for the function in the symbol table.
	SymTable *curTab = GE::runner()->symtab();
	ASTNode* function = curTab->findFromAny(m_name); 

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
			FunctionStmt* clone = fstmt->createGenericClone(m_arguments);
			m_name = clone->name();
		}
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
