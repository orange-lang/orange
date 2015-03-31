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

class AnyType : public CodeElement {
private:
	Type* m_type;
	std::string m_type_str;

	bool m_signed = false;
	int m_ptrs = 0;

	static std::map<std::string, AnyType*> m_defined_tyes;
public:
	std::string string() const;
	Type* getLLVMType() const { return m_type; }
	bool isSigned() const { return m_signed; }

	bool isVoidTy() const;
	bool isIntegerTy() const; 
	bool isFloatTy() const; 
	bool isDoubleTy() const;
	bool isFloatingPointTy() const;
	bool isPointerTy() const { return m_ptrs > 0; }
	int getIntegerBitWidth() const;
	int getPointerLength() const { return m_ptrs; }

	static AnyType* getVoidTy();
	static AnyType* getUIntNTy(int size);
	static AnyType* getIntNTy(int size);
	static AnyType* getFloatTy();
	static AnyType* getDoubleTy();
	static AnyType* getInt8PtrTy();

	AnyType(Type* type, bool isSigned = false);
	AnyType(std::string type, int ptrs = 0);
}; 

#endif 