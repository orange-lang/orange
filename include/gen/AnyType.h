#ifndef __ANY_TYPE_H__
#define __ANY_TYPE_H__
#include "AST.h"
#include "Values.h"

/**
 * AnyType is a class to produce any LLVM type given the type string from orange (e.g., uint16),
 * a number of pointers, and a vector of BaseVal arrays. AnyType is used to keep track of whether  
 * or not a type is signed, since LLVM doesn't support signed/unsigned types (everything is unsigned).
 *
 * @see BaseVal
 */
class AnyType {
private:
	// We don't want users to dynamically change the type, so these variables must be private.
	std::vector<uint64_t> arrays;
	std::string type; 
	int numPointers = 0; 

	// The constructur with no arguments is used internally, but we don't want to provide 
	// it to the user so they have to create a type.
	AnyType() { }
public:
	/**
	 * Get the number of dimensions for this array, if any. If 
	 * this returns zero, then it is not an array. If this returns > 1, it 
	 * is a n-dimensional array.
	 * 
	 * @return The number of dimensions in this type.
	 */
	int arrays_size() const;

	/**
	 * Gets the type string representation of this AnyType. 
	 * If the type is a pointer to uint64, this function returns uint64, not 
	 * uint64*. If you wish to get the full string representation,
	 * use string() instead.
	 *
	 * @see string()
	 * 
	 * @return String representing the type of this AnyType.
	 */
	std::string getTypeStr() const;

	/**
	 * Gets whether or not this AnyType is an signed type. For example, 
	 * this method would return false for uint64 and true for int64. This 
	 * method will always return false for floating-point types.
	 *
	 * @return Boolean indiciating whether or not this AnyType is signed.
	 */
	bool isSigned();

	/**
	 * Gets the number of *direct* pointers of this type. If this type 
	 * is an array, that is not accounted for in this method. If you 
	 * wish to get the number of pointers including the dimensions of an
	 * array, use absoluteNumPtrs instead.
	 * 
	 * @see absoluteNumPtrs
	 *
	 * @return The direct number of pointers of this type.
	 */
	int getNumPointers() const;

	/**
	 * Gets the *absolute* number of pointers of this type. This 
	 * includes the dimensions of the array, if this type is an array. 
	 * For example, this method would return 1 for int[5] and 2 for 
	 * int*[5]. If you only wish to get the number of pointers (*), see
	 * getNumPointers.
	 *
	 * @see getNumPointers
	 *
	 * @return The absolute number of pointers of this type.
	 */
	int absoluteNumPtrs();

	/**
	 * Gets the full string represenation of this type. This will return 
	 * a string including the type, pointers, and arrays, if applicable. 
	 * If you only wish to get the type, use getTypeStr instead.
	 *
	 * @see getTypeStr
	 *
	 * @param no_brackets indicate whether or not to include array sizes enclosed in brackets. If true, uses an underscore instead.  
	 * @return The full string representation of this type.
	 */
	std::string string(bool no_brackets = false);

	/**
	 * Gets the LLVM type instance for this type. Whether or not the variable is 
	 * signed will not affect the return value of this method, since LLVM does not 
	 * establish a difference.
	 *
	 * @return The LLVM type instance for this type.
	 */
	Type *getType();

	/**
	 * Allocates and creates a clone of this type. The result of this function call 
	 * is allocated on the heap and must be deleted after use.
	 *
	 * @return An heap-allocated clone of this type.
	 */ 
	AnyType* clone();

	/**
	 * Creates an AnyType from an LLVM type. Note that this will always create an unsigned type.
	 *
	 * @param t The LLVM type to convert to an AnyType.
	 * @return The AnyType converted from an LLVM type.
	 */
	static AnyType *Create(Type *t);

	/**
	 * Creates an instance of AnyType, with a string representation, number of pointers, and list of arrays.
	 *
	 * @param type A pointer to a string holding the Orange type for this AnyType (e.g., float, double, int, int8)
	 * @param numPointers The number of pointers for this type. For example, uint16* would have one pointer.
	 * @param arrays A vector of array sizes. Each dimension should be a new element in the vector. int[3][2] would be two elements: 3 and 2. 
	 */ 
	AnyType(std::string *type, int numPointers, std::vector<BaseVal *> *arrays);
};

#endif