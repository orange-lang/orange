/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/types/ArrayType.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>

ArrayType::ArrayType(Type* contained, unsigned int size)
{
	if (contained == nullptr)
	{
		throw std::invalid_argument("contained must not be null.");
	}

	m_contained = contained;
	m_size = size;

	m_type = llvm::ArrayType::get(m_contained->getLLVMType(), m_size);
}

std::string ArrayType::getSignature() const
{
	std::stringstream ss;
	ss << m_size << m_contained->getSignature();
	return ss.str();
}

bool ArrayType::isSigned() const
{
	return m_contained->isSigned();
}

bool ArrayType::isArrayTy() const
{
	return true;
}

Type* ArrayType::getBaseTy()
{
	return m_contained;
}

Type* ArrayType::getRootTy()
{
	return m_contained->getRootTy();
}

ArrayType* ArrayType::get(Type *contained, unsigned int size)
{
	if (contained == nullptr)
	{
		throw std::invalid_argument("contained must not be nullptr");
	}

	std::stringstream ss;
	ss << size << contained->getSignature();

	auto defined = getDefined(ss.str());
	if (defined != nullptr)
	{
		return defined->as<ArrayType *>();
	}

	ArrayType* ty = new ArrayType(contained, size);
	define(ss.str(), ty);

	return ty;
}
