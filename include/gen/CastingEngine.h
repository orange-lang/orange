#ifndef __CASTING_ENGINE_H__
#define __CASTING_ENGINE_H__

#include "AST.h"

// Casts Value *v to type t, if compatible. 
// v will change if a cast occured.
// This function returns true if casting occured, 
// false otherwise. 
bool CastValueToType(Value **v, Type *t, bool isSigned, bool force = false);

// Casts Values *v1 and *v2 to be compatible.
// Types of casting that will occur:
// 	- if v1 and v2 are both integers:
//		casts either v1 or v2 to the larger integer bit-width  
// 	- if v1 and v2 are both integers, and the signs are different:
//		casts unsigned to signed
//	- if either v1 or v2 is a float, and the other is an int:
//		casts the int to a float
//	- if either v1 or v2 is a double, and the other is an int:
//		casts the int to a double 
//	- if either v1 or v2 is a double, and the other is a float:
//		casts the float to a double.
// This function returns true if casting occured, 
// false otherwise. 
bool CastValuesToFit(Value **v1, Value **v2, bool isV1Signed, bool isV2Signed);

bool ShouldTypesMorph(Type *src, Type *dest);

bool CanTypeBeCasted(Type *src, Type *dest);

Type *GetFittingType(Type *v1, Type *v2);

#endif