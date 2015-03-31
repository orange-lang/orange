#include "gen/DerefId.h"
#include "gen/VarExpr.h"
#include "gen/generator.h"

std::string DerefId::string() {
	std::stringstream ss; 
	for (int i = 0; i < pointers; i++) {
		ss << "*"; 
	}

	ss << id->string(); 
	return ss.str();
}

Type* DerefId::getType() {
	DEBUG_MSG("((DerefId)) GETTING TYPE OF " << id->string() << " using " << pointers << " pointers!");

	AnyType *at = AnyType::Create(id->getType());

	int newPtrs = at->numPointers - pointers; 

	if (newPtrs < 0) {
		std::stringstream myStr; 
		for (int i = 0; i < pointers; i++) myStr << "*";
		myStr << at->type; 

		std::stringstream theirStr;
		for (int i = 0; i < at->numPointers; i++) theirStr << "*";		 
		theirStr << at->type;

		std::cerr << "fatal: trying to dereference a pointer of " << theirStr.str() << " to invalid type " 
			<< myStr.str() << " (pointer mismatch!)" << std::endl;

		exit(1);
	}

	std::string *name = new std::string(at->type);
	AnyType *ret = new AnyType(name, newPtrs);
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