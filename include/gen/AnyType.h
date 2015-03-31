#ifndef __ANY_TYPE_H__
#define __ANY_TYPE_H__
#include "AST.h"

class AnyType {
private:
	std::vector<uint64_t> arrays;

	bool mArrayType = false;
	int mArraySize = 0;
	AnyType() { }
public:
	int arrays_size() const { return arrays.size(); }

	std::string type; 
	bool isSigned();
	int numPointers = 0; 
	bool arrayType() const { return mArrayType; }  
	int arraySize() const { return mArraySize; }
	int absoluteNumPtrs();

	std::string string(bool no_brackets = false);

	Type *getType();

	static AnyType *Create(Type *t);
	AnyType* clone();

	AnyType(std::string *type, int numPointers, std::vector<BaseVal *> *arrays);
};

#endif