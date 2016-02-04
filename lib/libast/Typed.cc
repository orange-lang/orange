/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <libast/Typed.h>

#include <libast/types/Type.h>
#include <libast/types/FutureType.h>

#include <util/assertions.h>

const Orange::Type* Typed::getType() const
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
	
	return Orange::Type::compare(source_ty, target_ty);
}

bool Typed::matchesType(const Orange::Type* ty) const
{
	return m_type->matches(ty);
}

void Typed::setType(const Orange::Type* type)
{
	if (m_type)
	{
		if (m_type->getComparisonTy()->is<WatchableType *>())
		{
    		m_type->getComparisonTy()->as<WatchableType *>()->removeWatcher(this);
		}
		else if (m_type->getComparisonTy()->isAggTy())
		{
			for (auto type : m_type->getComparisonTy()->getMemberTys())
			{
				if (type->is<WatchableType *>())
				{
					type->as<WatchableType *>()->removeWatcher(this);
				}
			}
		}
	}
	
	m_type = type;
	
	if (m_type)
	{
		if (m_type->getComparisonTy()->is<WatchableType *>())
		{
			m_type->getComparisonTy()->as<WatchableType *>()->addWatcher(this);
		}
		else if (m_type->getComparisonTy()->isAggTy())
		{
			for (auto type : m_type->getComparisonTy()->getMemberTys())
			{
				if (type->is<WatchableType *>())
				{
					type->as<WatchableType *>()->addWatcher(this);
				}
			}
		}
	}
}