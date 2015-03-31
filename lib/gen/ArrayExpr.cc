#include "gen/ArrayExpr.h"
#include "gen/generator.h"
#include "gen/CastingEngine.h"

void ArrayExpr::resolve() {
	if (resolved)
		return;
	resolved = true;

	for (Expression *e : *elements) {
		e->resolve();
	}
}

Type* ArrayExpr::getType() {
	// -- Determine type of array: 
	// 1. Create an array of each Expression type 
	// 2. Greatest = type of arr[0].
	// 3. Iterate over the array, i++
	// 		a. if (type of arr[i]) > Greatest, Greatest = arr[i]  
	// 4. Continue until all elements have been searched.  
	// 5. Return ArrayType::get of greatest, elements->size() 

	// -- Determine greatest between two types. 
	// 1. GetFittingType(a, b). 
	// 		a. If it returns a, a is greater.
	//		b. If it returns b, b is greater. 
	std::vector<Type *> types; 
	for (Expression *e : *elements) {
		types.push_back(e->getType());
	}

	Type *Greatest = types[0];
	for (Type *t : types) {
		if (GetFittingType(t, Greatest) == t)
			Greatest = t; 
	} 

	return ArrayType::get(Greatest, elements->size());
}

std::string ArrayExpr::string() {
	std::stringstream ss;
	ss << "[";
	for (int i = 0; i < elements->size(); i++) {
		ss << elements->at(i)->string(); 
		if (i + 1 < elements->size()) 
			ss << ", ";
	}
	ss << "]";
	return ss.str();
}

bool ArrayExpr::isConstant() {
	for (Expression *e : *elements) {
		if (e->returnsPtr()) {
			return false;
		}

		if (e->isConstant() == false) {
			return false; 
		}

	}

	return true; 
}

Value* ArrayExpr::Codegen() {
	// you got this!!!!
	ArrayType *ourType = (ArrayType *)getType();

	Value *ret = CG::Builder.CreateAlloca(ourType);

	if (isConstant()) {
		// Constant array:
		// 1. If all expressions in elements are constant, create an 
		//		vector<Constant *> and push back the code gens for each expression.
		// 2. Create a ConstantArray::get() with getType() and the array as parameters.
		// 3. Return that vector.
		std::vector<Constant *> arr;
		for (Expression *e : *elements) {
			Value *v = e->Codegen();
			CastValueToType(&v, ourType->getElementType(), e->isSigned());

			arr.push_back((Constant *)v);
		}

		Value *sta = ConstantArray::get(ourType, arr);

		CG::Builder.CreateStore(sta, ret);
		
		return ret;
	}

	// Non-constant array:
	// 1. Do a CreateAlloca of getType.
	// 2. For each Expression in elements, 
	//		a. GEP (getelementptr) to its element
	//		b. do a store to the result of a. 
	// 3. Return the variable from alloca.

	for (int i = 0; i < elements->size(); i++) {
		Expression *expr = elements->at(i);

		Value *gep = CG::Builder.CreateConstInBoundsGEP2_64(ret, 0, i);
		Value *sta = expr->Codegen();

		if (expr->returnsPtr()) {
			sta = CG::Builder.CreateLoad(sta);
		}

		CG::Builder.CreateStore(sta, gep);
	}

	return ret;
}
