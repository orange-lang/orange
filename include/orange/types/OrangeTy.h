/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_ORANGE_TY_H__
#define __ORANGE_ORANGE_TY_H__

#include <map>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

#include "../CodeElement.h"

using namespace llvm;

class Expression;

/** 
 * OrangeTy represents various types in Orange.
 */
class OrangeTy : public CodeElement {
protected:
	Type* m_llvm_ty = nullptr;

	static std::map<std::string, OrangeTy*> m_defined_types;

	/** 
	 * Gets a defined type if it exists.
	 * @param name The name of the type to get.
	 * @return The defined type if it exists. nullptr otherwise.
	 */
	static OrangeTy* getDefined(std::string name);

	static OrangeTy* define(std::string name, OrangeTy* type);

	OrangeTy() { }
	virtual ~OrangeTy() { }
public:
	virtual std::string string() const { return ""; }
	virtual std::string typeSuffix() const { return ""; } 

	virtual Type* getLLVMType() const { return m_llvm_ty; }

	virtual bool isSigned() const { return false; }

	static OrangeTy* get(std::string str);

	////
	// Type comparison section 
	////

	/** 
	 * If a type is ID, it doesn't exist right now 
	 * but it will in the future.
	 */
	virtual bool isIDTy() const { return false; }

	/** 
	 * If a type is void, then it does not exist.
	 */
	virtual bool isVoidTy() const { return false; }

	virtual bool isIntegerTy() const { return false; }

	virtual bool isFloatTy() const { return false; }

	virtual bool isDoubleTy() const { return false; }

	virtual bool isFloatingPointTy() const { return false; }

	virtual bool isPointerTy() const { return false; }

	virtual bool isArrayTy() const { return false; }

	virtual bool isConstantArray() const { return false; }

	virtual bool isVariadicArray() const { return false; }

	virtual int getIntegerBitWidth() const { return 0; }

	virtual int getPointerLength() const { return 0; }

	////
	// Pointer operation section
	////
	virtual OrangeTy* getPointerTo();
	virtual OrangeTy* getPointerElementType() { return nullptr; }
	virtual OrangeTy* getBaseType() { return this; }

	////
	// Array operation section 
	////
	virtual OrangeTy* getArrayElementType() { return nullptr; }
	virtual unsigned int getArrayElements() { return 0; }
	virtual Expression* getVariadicArrayElement() { return nullptr; }

	////
	// LLVM operation section 
	////
	virtual Value* allocate(); 
	static OrangeTy* getFromLLVM(Type* ty, bool isSigned);
	static bool isExpressionValidForConstArray(Expression* e);
	static unsigned int valueFromExpression(Expression* e);
}; 

#endif 