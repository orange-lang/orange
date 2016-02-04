/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <libast/types/VariadicArrayType.h>
#include <libast/types/PointerType.h>

#include <libast/Valued.h>
#include <libast/Expression.h>

#include <util/assertions.h>

#include <llvm/IR/Type.h>
#include <llvm/IR/IRBuilder.h>

static llvm::Value* PointerCast(void* irBuilder, Valued* val,
								const Orange::Type* from,
								const Orange::Type* to)
{
	assertExists(irBuilder, "irbuilder must exist");
	assertExists(val, "val must exist");
	assertExists(from, "from must exist");
	assertExists(to, "to must exist");
	
	auto llvm_val = val->getPointer();
	assertExists(llvm_val, "valued didn't have pointer");
	
	LLVMBuilder* IRB = (LLVMBuilder *)irBuilder;
	
	return IRB->CreateBitCast(llvm_val, to->getLLVMType());
}

Orange::VariadicArrayType::VariadicArrayType(const Type* contained, Expression* size,
									 bool isConst)
: Type(isConst)
{
	assertExists(contained, "contained must not be null.");
	assertExists(size, "size must not be null.");
	
	m_contained = contained;
	m_size = size;
	
	
	auto non_array = m_contained;
	while (non_array->isArrayTy())
	{
		non_array = non_array->getBaseTy();
	}
	
	m_type = (llvm::Type *)non_array->getLLVMType();
	
	defineCast(typeid(PointerType), llvm::Instruction::CastOps::BitCast,
			   PointerCast);
}

const Orange::Type* Orange::VariadicArrayType::copyType() const
{
	return VariadicArrayType::get(getModule(), m_contained->copyType(),
								  m_size->copy()->as<Expression *>(),
								  isConst());
}

std::string Orange::VariadicArrayType::getString() const
{
	std::stringstream ss;
	
	if (isConst())
	{
		ss << "const ";
	}
	
	ss << m_contained->getString() << "[]";
	return ss.str();
}

std::string Orange::VariadicArrayType::getSignature(const Type *conatined,
											Expression *size, bool isConst)
{
	std::stringstream ss;
	
	if (isConst)
	{
		ss << getConstIdentifier();
	}
	
	ss << "S" << conatined->getSignature() << (uint64_t)size;
	
	return ss.str();
}

std::string Orange::VariadicArrayType::getSignature() const
{
	return getSignature(m_contained, m_size, isConst());
}

Expression* Orange::VariadicArrayType::getSize() const
{
	return m_size;
}

bool Orange::VariadicArrayType::isSigned() const
{
	return m_contained->isSigned();
}

bool Orange::VariadicArrayType::isArrayTy() const
{
	return true;
}


const Orange::Type* Orange::VariadicArrayType::getBaseTy() const
{
	return m_contained;
}

const Orange::Type* Orange::VariadicArrayType::getRootTy() const
{
	return m_contained->getRootTy();
}

const Orange::Type* Orange::VariadicArrayType::getConst() const
{
	return get(getModule(), m_contained, m_size, true);
}

bool Orange::VariadicArrayType::isVariadiclySized() const
{
	return true;
}

std::vector<Expression *> Orange::VariadicArrayType::getVariadicSizes() const
{
	std::vector<Expression *> sizes;
	
	const Orange::Type* ptr = this;
	while (ptr->isVariadiclySized())
	{
		auto va = dynamic_cast<const VariadicArrayType *>(ptr);
		sizes.push_back(va->getSize());
		
		ptr = ptr->getBaseTy();
	}
	
	return sizes;
}

Orange::VariadicArrayType* Orange::VariadicArrayType::get(Module* mod,
														  const Type *contained,
														  Expression *expr,
														  bool isConst)
{
	assertExists(contained, "contained cannot be null");
	assertExists(expr, "expr cannot be null");
	
	auto sig = getSignature(contained, expr, isConst);
	
	auto defined = getDefined(mod, sig);
	if (defined != nullptr)
	{
		return defined->as<VariadicArrayType *>();
	}
	
	VariadicArrayType* ty = new VariadicArrayType(contained, expr, isConst);
	define(mod, sig, ty);
	
	return ty;
}