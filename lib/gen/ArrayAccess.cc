#include "gen/ArrayAccess.h"
#include "gen/generator.h"
#include "gen/Values.h"

std::string ArrayAccess::string() {
	std::stringstream ss; 
	ss << array->string(); 
	ss << "[" << idx->string() << "]";
	return ss.str();
}

Type* ArrayAccess::getType() {
	// get the type of the elements stored in array 
	Type *v = array->getType();
	return v->getArrayElementType();
}

void ArrayAccess::resolve() {
	if (resolved == true)
		return;
	resolved = true;

	array->resolve();
	idx->resolve();

	Type *arrayTy = array->getType(); 

	// error checking 
	bool isArray = arrayTy->isPointerTy() || arrayTy->isArrayTy();
	if (isArray == false) {
		std::cerr << "fatal: cannot access element of a non-array\n";
		exit(1);
	}
}

Value* ArrayAccess::Codegen() {
	Type *arrayTy = array->getType();

	Value *arrV = array->Codegen();

	// If we're not an array, we're a pointer, 	
	// so we need to load it 
	if (arrayTy->isArrayTy() == false) {
		arrV = CG::Builder.CreateLoad(arrV);
	}

	Value *idxV = idx->Codegen();

	// If we're not a constant value, we need to 
	// be loaded in
	if (idx->returnsPtr()) {
		idxV = CG::Builder.CreateLoad(idxV);
	}

	std::vector<Value *> indicies; 

	// Adding back the subindex of 0 only is applicable 
	// for arrays, not pointers.
	if (arrayTy->isArrayTy()) {
		IntVal subIdx(0, 64);
		indicies.push_back(subIdx.Codegen());
	}

	indicies.push_back(idxV);

	Value *ret = CG::Builder.CreateInBoundsGEP(arrV, indicies);

	return ret;  
}

ArrayAccess::ArrayAccess(Expression *array, Expression *idx) {
	this->array = array; 
	this->idx = idx;
}
