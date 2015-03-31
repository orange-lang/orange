#include "gen/AnyType.h"
#include "gen/Values.h"

int AnyType::arrays_size() const { 
	return arrays.size(); 
}

std::string AnyType::getTypeStr() const { 
	return type; 
}

bool AnyType::isSigned() {
	/* 
		Return true if and only if the first character of our type is i. This makes sense considering:
			1. int8, int16, int32, and int64 are the only signed integers.
			2. floats and doubles are always signed, and don't apply here.
			3. bools are unsigned types (uint1). 
	*/
	return (type[0] == 'i');
}

int AnyType::getNumPointers() const { 
	return numPointers; 
}

int AnyType::absoluteNumPtrs() {
	// The absolute number of pointers is numPointers + the size of the arrays vector
	int ret = numPointers + arrays.size();
	return ret;
}

std::string AnyType::string(bool no_brackets) {
	std::stringstream ss;
	ss << type;

	// Add an asterisk for each pointer 
	for (int i = 0; i < numPointers; i++) ss << "*";

	// We don't need to check if arrays.size() > 0 since the body of this 
	// will only run when arrays has elements	
	for (auto sz : arrays) {
		// If the user didn't specify no_brackets, encase the size of this dimension in brackets. 
		// Otherwise, use a single underscore.
		if (no_brackets == false) {
			ss << "[" << sz << "]"; 
		} else {
			ss << "_" << sz; 
		}
	}

	return ss.str();
}

Type *AnyType::getType() {
	// We have to use ::getType here since we're referring to the getType function defined in AST.h. 
	Type *initial = ::getType(type);

	// For each pointer, get a pointer to our current LLVM type.
	for (int i = 0; i < numPointers; i++) {
		initial = initial->getPointerTo(0);
	}

	// Finally, for each array dimension, get an array type of our current LLVM type.
	for (int i = arrays.size() - 1; i >= 0; i--) {
		initial = ArrayType::get(initial, arrays[i]);
	}
	
	return initial;
}

AnyType* AnyType::clone() {
	AnyType* ret = new AnyType;
	for (auto n : arrays) ret->arrays.push_back(n);
	ret->type = type;
	ret->numPointers = numPointers;
	return ret;
}

AnyType *AnyType::Create(Type *t) {
	AnyType *ret = new AnyType;
	ret->numPointers = 0;

	// As long as t is a pointer, add a pointer to our AnyType, and 
	// make t be the type that the pointer is pointing to. This will run 
	// until we have identified the pointer depth.
	while (t->isPointerTy()) {
		ret->numPointers++;
		t = t->getPointerElementType();
	}

	// As long as t is an array, push back the number of elements, and 
	// make t be the type that the array is pointing to. This will run 
	// until we have identified all of the number of elements in the n-dimension array.
	while (t->isArrayTy()) {
		ArrayType *at = (ArrayType *)t;
		ret->arrays.push_back((int)at->getNumElements());
		t = t->getArrayElementType();		
	}

	// Now that we've ensured we are not a pointer or an array, get the type for this.
	if (t->isFloatTy()) {
		ret->type = "float"; 
	} else if (t->isDoubleTy()) {
		ret->type = "double";
	} else if (t->isIntegerTy(8)) {
		ret->type = "int8";
	} else if (t->isIntegerTy(16)) {
		ret->type = "int16"; 
	} else if (t->isIntegerTy(32)) {
		ret->type = "int32";
	} else if (t->isIntegerTy(64)) {
		ret->type = "int64";
	} else if (t->isVoidTy()) {
		ret->type = "void";
	} else {
		std::cerr << "warning: unrecognized type.\n";
	}

	return ret;
}

AnyType::AnyType(std::string *type, int numPointers, std::vector<BaseVal *> *arrays) {
	this->type = *type;
	this->numPointers = numPointers; 

	if (arrays == nullptr) return; 
	
	for (BaseVal *bv : *arrays) {
		if (bv == nullptr) {
			this->numPointers++;
			continue;
		}

		// We require the user to use hard integer values for the size of the array (no such thing as a 1.5 size array!).
		if (bv->getClass() != "UIntVal" && bv->getClass() != "IntVal") {
			std::cerr << "fatal: cannot construct array with element size " << bv->string() << std::endl;
			exit(1);
		}

		if (bv->getClass() == "UIntVal") {
			UIntVal *uiv = (UIntVal *)bv; 
			this->arrays.push_back(uiv->value); 
		} else if (bv->getClass() == "IntVal") {
			IntVal *iv = (IntVal *)bv; 
			this->arrays.push_back((uint64_t)iv->value);
		}
	}
}

