/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/ExternFunction.h>
#include <orange/generator.h>

ExternFunction::ExternFunction(AnyType* returnType, std::string name, ParamList parameters) : m_type(returnType), m_name(name), m_parameters(parameters) {
	if (returnType == nullptr) {
		throw std::runtime_error("return type for an external function can not be null!");
	}
}

Value* ExternFunction::Codegen() {
	std::vector<Type*> Args;

	for (auto param : m_parameters) {
		Args.push_back(param->getLLVMType());
	}

	FunctionType *FT = FunctionType::get(getLLVMType(), Args, false); // TODO: check for vararg!
	Function *TheFunction = Function::Create(FT, Function::ExternalLinkage, m_name, GE::module());

	m_value = TheFunction;

	return m_value; 
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
