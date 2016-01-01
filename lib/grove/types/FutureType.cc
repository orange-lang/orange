/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/types/FutureType.h>
#include <grove/types/ReferenceType.h>

#include <grove/Typed.h>

#include <util/assertions.h>

Module* FutureType::getModule() const
{
	return Type::getModule();
}

std::string FutureType::getString() const
{
	return "future";
}

std::string FutureType::getSignature() const
{
	std::stringstream ss;
	ss << "Z" << this;
	return ss.str();
}

void FutureType::findDependencies()
{
	for (auto watcher : m_watchers)
	{
		addDependency(watcher->as<ASTNode *>());
	}
}

const Orange::Type* FutureType::copyType() const
{
	return FutureType::copy()->as<Type *>();
}


ASTNode* FutureType::copy() const
{
	throw fatal_error("FutureType should never be copied");
}

std::vector<ObjectBase **> FutureType::getMemberNodes()
{
	return defMemberNodes();
}

std::vector<std::vector<ObjectBase *>*> FutureType::getMemberLists()
{
	auto list = defMemberLists();
	list.insert(list.end(), {
		(std::vector<ObjectBase *>*)&m_watchers
	});
	return list;
}

bool FutureType::isFutureTy() const
{
	return true;
}

void FutureType::replace(const Orange::Type* with)
{
	auto watchers_copy = m_watchers;
	
	for (auto watcher : watchers_copy)
	{
		auto ty = watcher->getType();
		
		if (ty->isAggTy())
		{
			watcher->setType(ty->replaceMember(this, with));
		}
		else if (ty == this)
		{
			watcher->setType(with);
		}
		else if (ty->is<ReferenceType*>())
		{
			auto ref_ty = ty->as<ReferenceType *>();
			auto comp_ty = ty->getComparisonTy();
			
			if (comp_ty->isAggTy())
			{
				ref_ty->setType(comp_ty->replaceMember(this, with));
			}
			else if (comp_ty == this)
			{
				ref_ty->setType(with);
			}
		}
		else
		{
			throw fatal_error("Watcher not affiliated with FutureType");
		}
	}
	
	m_watchers.clear();
}

void FutureType::addWatcher(Typed* watcher)
{
	auto it = std::find(m_watchers.begin(), m_watchers.end(), watcher);
	if (it == m_watchers.end())
	{
		m_watchers.push_back(watcher);
	}
}

void FutureType::removeWatcher(Typed* watcher)
{
	auto it = std::find(m_watchers.begin(), m_watchers.end(), watcher);
	if (it != m_watchers.end())
	{
		m_watchers.erase(it);
	}
}

FutureType::FutureType(Module* mod)
: NodeType(false)
{
	assertExists(mod, "FutureType needs module");
	
	Type::m_module = mod;
}