/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include "gen/DerefId.h"
#include "gen/VarExpr.h"
#include "gen/generator.h"

std::string DerefId::string() {
	std::stringstream ss; 
	for (int i = 0; i < pointers; i++) {
		ss << "*"; 
	}

	ss << "(" << id->string() << ")"; 
	return ss.str();
}

Type* DerefId::getType() {
	AnyType *at = AnyType::Create(id->getType());
	int newPtrs = at->absoluteNumPtrs() - pointers; 

	if (newPtrs < 0) {
		std::stringstream myStr; 
		for (int i = 0; i < pointers; i++) myStr << "*";
		myStr << at->getTypeStr(); 

		std::stringstream theirStr;
		for (int i = 0; i < at->getNumPointers(); i++) theirStr << "*";		 
		theirStr << at->getTypeStr();

		std::cerr << "fatal: trying to dereference a pointer of " << theirStr.str() << " to invalid type " 
			<< myStr.str() << " (pointer mismatch!)" << std::endl;

		exit(1);
	}

	std::string *name = new std::string(at->getTypeStr());
	AnyType *ret = new AnyType(name, newPtrs, nullptr);

	delete name; 
	return ret->getType();
}


Value* DerefId::Codegen() {
	Value *ret = id->Codegen(); 
	for (int i = 0; i < pointers; i++) {
		ret = CG::Builder.CreateLoad(ret);
	}
	return ret; 
}

DerefId::~DerefId() {
	delete id;
}