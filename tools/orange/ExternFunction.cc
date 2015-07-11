/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/ExternFunction.h>
#include <orange/generator.h>

std::string ExternFunction::string() {
	std::stringstream ss; 
	ss << "extern " << m_type->string() << " " << m_name << "(";
	for (unsigned int i = 0; i < m_parameters.size(); i++) {
		VarExpr* param = m_parameters[i];

		if (param->getType()->isVoidTy() == false) {
			ss << param->getType()->string() << " "; 
		}

		ss << param->name();

		if (i + 1 < m_parameters.size()) {
			ss << ", "; 
		}
	}  

	if (m_parameters.varArg()) {
		ss << ", ...";
	}

	ss << ")";
	return ss.str();
}

ExternFunction::ExternFunction(OrangeTy* returnType, std::string name, ParamList parameters) : m_name(name), m_parameters(parameters) {
	m_type = returnType; 

	if (returnType == nullptr) {
		throw std::runtime_error("return type for an external function can not be null!");
	}

	for (auto param : m_parameters) {
		addChild(param);
	}
}

Value* ExternFunction::Codegen() {
	std::vector<Type*> Args;

	for (auto param : m_parameters) {
		Args.push_back(param->getLLVMType());
	}

	FunctionType *FT = FunctionType::get(getLLVMType(), Args, m_parameters.varArg());
	Function *TheFunction = Function::Create(FT, Function::ExternalLinkage, m_name, GE::module());

	m_value = TheFunction;

	return m_value; 
}

void ExternFunction::initialize() {
	// don't do anything
}

void ExternFunction::resolve() {
	if (m_resolved) return; 
	m_resolved = true;

	bool added = GE::runner()->symtab()->create(m_name, this);
	if (added == false) {
		std::string s = "A function called " + m_name + " already exists!";
		throw std::runtime_error(s);
	}
}
