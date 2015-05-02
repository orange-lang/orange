/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_ANY_TYPE_H__
#define __ORANGE_ANY_TYPE_H__

#include <map>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

#include "CodeElement.h"

using namespace llvm;

class Expression;

class AnyType : public CodeElement {
private:
	Type* m_type;
	std::string m_type_str;

	bool m_signed = false;
	int m_ptrs = 0;

	std::vector<int> m_arrays;
	std::vector<Expression *> m_arrays_expr;

	static std::map<std::string, AnyType*> m_defined_tyes;
public:
	std::string string() const;
	Type* getLLVMType() const { return m_type; }
	bool isSigned() const { return m_signed; }

	bool isIDTy() const;
	bool isVoidTy() const;
	bool isIntegerTy() const; 
	bool isFloatTy() const; 
	bool isDoubleTy() const;
	bool isFloatingPointTy() const;
	bool isPointerTy() const { return m_ptrs > 0; }
	bool isArrayTy() const { return (m_arrays.size() > 0) || (m_arrays_expr.size() > 0); }
	int getIntegerBitWidth() const;
	int getPointerLength() const { return m_ptrs; }
	int getArrayElements() const { return m_arrays[0]; }

	std::vector<int> getAllArrayElements() const { return m_arrays; }
	std::vector<Expression* > getAllVariadicArrayElements() const { return m_arrays_expr; }

	bool isConstantArray() const { return m_arrays.size() > 0 && m_arrays_expr.size() == 0; }
	bool isVariadicArray() const { return m_arrays_expr.size() > 0; }

	AnyType* getArray(int size);

	static AnyType* getIDTy();
	static AnyType* getVoidTy();
	static AnyType* getUIntNTy(int size);
	static AnyType* getIntNTy(int size);
	static AnyType* getFloatTy();
	static AnyType* getDoubleTy();
	static AnyType* getInt8PtrTy();

	/** 
	 * Gets a type that's a pointer to the current type.
	 */
	AnyType* getPointerTo();

	/** 
	 * Gets a type that's being stored by this array.
	 */
	AnyType* getElementType(); 

	/**
	 * Gets the type that a pointer is pointing to.
	 */ 
	AnyType* getPointerElementType(); 

	/** 
	 * Allocates a value of this type.
	 */
	Value* allocate();

	AnyType(Type* type, bool isSigned = false);
	AnyType(std::string type, std::vector<int> arrays = std::vector<int>(), int ptrs = 0);

	/**
	 * Creates an array AnyType with a size that is determined at 
	 * runtime.
	 */ 
	AnyType(std::string type, std::vector<Expression*> arrayExpr, int ptrs = 0);
}; 

#endif 