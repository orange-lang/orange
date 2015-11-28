/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include <llvm/IR/Value.h>
#include <llvm/IR/Type.h>

enum TypeComparison {
	VAL,
	PTR
};

template <TypeComparison SRC = VAL, TypeComparison DEST = VAL>
void assertEqual(llvm::Type* a, llvm::Type* b, std::string err)
{
	if (a == nullptr || b == nullptr)
	{
		throw std::invalid_argument(err);
	}
	
	if (SRC == PTR)
	{
		a = a->getPointerElementType();
	}
	
	if (DEST == PTR)
	{
		b = b->getPointerElementType();
	}
	
	if (a == nullptr || b == nullptr || a != b)
	{
		throw std::invalid_argument(err);
	}
}

template <TypeComparison SRC = VAL, TypeComparison DEST = VAL>
void assertEqual(llvm::Value* a, llvm::Value* b, std::string err)
{
	if (a == nullptr || b == nullptr)
	{
		throw std::invalid_argument(err);
	}
	
	assertEqual<SRC, DEST>(a->getType(), b->getType(), err);
}