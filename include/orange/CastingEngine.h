/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_CASTING_ENGINE_H__
#define __ORANGE_CASTING_ENGINE_H__

#include "OrangeTypes.h"
#include "AST.h"

using namespace llvm;

class CastingEngine {
public:
	/**
	 * Determines whether or not two types can interact together. If the types cannot be 
	 * casted to fit each other, then this will return false. The parameters of this function 
	 * are order-independent. 
	 *
	 * @param a The first type to check for compatibility. 
	 * @param b The second type to check for compatibility.
	 *
	 * @return True if the types are compatible, false otherwise.
	 */
	static bool AreTypesCompatible(OrangeTy* a, OrangeTy* b);

	/**
	 * Determines whether or not a source type can be casted to a destination type. If the source 
	 * type cannot be casted to fit the destination type, then this will return false. The parameters 
	 * of this function may be order-dependant.
	 *
	 * @param src The source type to check for casting.
	 * @param dest The type to check for casting against.
	 *
	 * @return True if src can be casted to dest, false otherwise.
	 */
	static bool CanTypeBeCasted(OrangeTy* src, OrangeTy* dest); 

	/**
	 * Casts a value to a specified type. If the types are compatible, then the cast will 
	 * be successful regardless of whether or not force is set to true. If the types are compatible, 
	 * this method will only succeed if force is true. 
	 *
	 * This method may throw an exception if a force cast is not yet implemented
	 *
	 * @param v A pointer to the value to be casted.
	 * @param t The type to cast the value to.
	 * @param isSigned Indicates whether or not value v is a signed type.
	 * @param force Indicates whether or not this cast should be forced.
	 *
	 * @return Returns true if the cast was successful, false otherwise.
	 */ 
	static bool CastValueToType(Value** v, OrangeTy* t, bool isSigned, bool force = false);

	/**
	 * Casts two values to match types. The type that will be used is determined by type precedence: 
	 * 	- Floating-point numbers have higher precedences than integers. 
	 * 	- The higher the size of a number, the higher its precedence. e.g., uint64 > uint8 and double > float.
	 *	- Signed values take higher precedence than unsigned values.
	 *
	 * @param v1 A pointer to the first value to cast to match the other.
	 * @param v2 A pointer to the second value to cast to match the first.
	 * @param isV1Signed Indicates whether or not the first value is a signed type.
	 * @param isV2Signed Indicates whether or not the second value is a signed type.
	 *
	 * @return Returns true if the cast was successful, false otherwise.
	 */ 
	static bool CastValuesToFit(Value** v1, Value** v2, bool isV1Signed, bool isV2Signed);

	/**
	 * Determines whether or not a type should be morphed to a destination type. This method
	 * will return true if the destination type has a higher precedence than sort. See 
	 * CastValueToType to get information on type precedence.
	 * 
	 * @param src The source type to check for morphing necessity. 
	 * @param dest The destination type to checkf or morphing necessity against.
	 *
	 * @return Returns true if dest has a higher precedence than src, false otherwise.
	 * 
	 * @see CastvalueToType
	 */ 
	static bool ShouldTypeMorph(OrangeTy* src, OrangeTy* dest);

	/**
	 * Gets the higher precedence type between two types. See CastValueToType to get information on type 
	 * precedence.
	 *
	 * @param v1 The first type to check the precedence of.
	 * @param v2 The second type to check the precedence of.
	 *
	 * @return Returns v1 if v1 has a higher precedence than v2. Returns v2 if v2 has a higher precedence than v1. 
	 * Returns nullptr if v1 and v2 are incompatible.
	 *
	 * @see CastValueToType
	 */
	static OrangeTy* GetFittingType(OrangeTy* v1, OrangeTy* v2); 
};

#endif
