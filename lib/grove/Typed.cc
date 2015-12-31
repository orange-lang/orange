/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/Typed.h>

#include <grove/types/Type.h>
#include <grove/types/FutureType.h>

#include <util/assertions.h>

const Type* Typed::getType() const
{
	return m_type;
}

llvm::Type* Typed::getLLVMType() const
{
	if (m_type == nullptr)
	{
		return nullptr;
	}
	
	return getType()->getLLVMType();
}

Comparison Typed::compare(const Typed *source, const Typed *target)
{
	assertExists(source, "source type must exist.");
	assertExists(target, "target type must exist.");
	
	auto source_ty = source->getType();
	auto target_ty = target->getType();
	
	assertExists(source_ty, "source didn't have a type");
	assertExists(target_ty, "target didn't have a type");
	
	return Type::compare(source_ty, target_ty);
}

bool Typed::matchesType(const Type *ty) const
{
	return m_type->matches(ty);
}

void Typed::setType(const Type* type)
{
	if (m_type)
	{
		if (m_type->getComparisonTy()->isFutureTy())
		{
    		m_type->getComparisonTy()->as<FutureType *>()->removeWatcher(this);
		}
		else if (m_type->getComparisonTy()->isAggTy())
		{
			for (auto type : m_type->getComparisonTy()->getMemberTys())
			{
				if (type->isFutureTy())
				{
					type->as<FutureType *>()->removeWatcher(this);
				}
			}
		}
	}
	
	m_type = type;
	
	if (m_type)
	{
		if (m_type->getComparisonTy()->isFutureTy())
		{
			m_type->getComparisonTy()->as<FutureType *>()->addWatcher(this);
		}
		else if (m_type->getComparisonTy()->isAggTy())
		{
			for (auto type : m_type->getComparisonTy()->getMemberTys())
			{
				if (type->isFutureTy())
				{
					type->as<FutureType *>()->addWatcher(this);
				}
			}
		}
	}
}