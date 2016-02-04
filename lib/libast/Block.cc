/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <libast/Block.h>
#include <libast/Named.h>
#include <libast/Genericable.h>
#include <libast/Module.h>
#include <libast/Protectable.h>

#include <libast/exceptions/already_defined_error.h>
#include <libast/exceptions/fatal_error.h>
#include <libast/exceptions/access_denied_error.h>

#include <util/assertions.h>

#include <typeinfo>

std::vector<ASTNode *> Block::getStatements() const
{
	return m_statements;
}

bool Block::usable(Named *n, const ASTNode *from) const
{
	if (from == nullptr)
	{
		return true;
	}
	
	if (n->is<Protectable *>())
	{
		return n->as<Protectable *>()->usableFrom(from);
	}
	
	return true;
}

Named* Block::verify(Named *n, const ASTNode *from) const
{
	if (usable(n, from)) return n;
	
	throw access_denied_error(n->as<CodeBase*>(), from, n->getName().str());
}

Named* Block::namedOrGenericInstance(Named* n, const Orange::Type* t,
									 const ASTNode* from) const
{
	if (n->is<Genericable *>() &&
		n->as<Genericable *>()->isGeneric())
	{
		auto generic = n->as<Genericable *>();
		if (generic->hasInstance(t))
		{
			return verify(generic->findInstance(t)->as<Named *>(), from);
		}
		else
		{
			auto inst = generic->createInstance(t)->as<Named *>();
			getModule()->process(inst->as<ASTNode *>());
			return verify(inst, from);
		}
	}
	
	return n;
}

bool Block::hasNamed(OString name, const ASTNode *limit,
					 SearchSettings settings) const
{
	for (auto child : getChildren())
	{
		if (child == limit)
		{
			break;
		}
		
		if (child->is<Named *>() == false)
		{
			continue;
		}
		
		auto named = child->as<Named *>();
		if (named->matchesName(name) && settings.filter(named))
		{
			return true;
		}
	}
	
	return false;
}

Named* Block::getNamed(OString name, const Orange::Type* type,
					   const ASTNode *limit, SearchSettings settings) const
{
	// First thing to do is get the list of names that match.
	std::vector<Named *> matches;
	
	for (auto child : getChildren())
	{
		if (child == limit)
		{
			break;
		}
		
		if (child->is<Named *>() == false)
		{
			continue;
		}
		
		auto named = child->as<Named *>();
		if (named->matchesName(name))
		{
			if (settings.filter(named) == false)
			{
				continue;
			}
			
			if (settings.forceTypeMatch && type && named->is<Typed *>())
			{
				if (named->as<Typed *>()->matchesType(type) == false)
				{
					continue;
				}
			}
			
			matches.push_back(named);
		}
	}
	
	if (matches.size() == 0)
	{
		return nullptr;
	}
	
	// If we only had one match, we can return it.
	if (matches.size() == 1)
	{
		if (settings.createGeneric)
		{
    		return namedOrGenericInstance(matches.at(0), type, limit);
		}
		else
		{
			return verify(matches.at(0), limit);
		}
	}
	else if (type == nullptr)
	{
		// Check to see if all elements are the same type.
		auto original = (CodeBase *)matches.at(0);
		auto first = typeid(*original).hash_code();
		
		for (unsigned int i = 1; i < matches.size(); i++)
		{
			auto element = matches.at(i)->as<CodeBase *>();
			if (typeid(*element).hash_code() != first)
			{
				throw already_defined_error(element, original, name, false);
			}
		}
		
		return nullptr;
	}
	
	// If we had more than one match, we need to see if we can find
	// a match by type.
	for (auto match : matches)
	{
		if (match->is<Typed *>() == false)
		{
			continue;
		}
		
		auto typed = match->as<Typed *>();
		if (typed->matchesType(type))
		{
			if (settings.createGeneric)
			{
    			return namedOrGenericInstance(match, type, limit);
			}
			else
			{
				return verify(matches.at(0), limit);
			}
		}
	}
	
	return nullptr;
}

std::vector<Named*> Block::getAllNamed(OString name, const ASTNode *limit) const
{
	std::vector<Named *> matches;
	
	for (auto child : getChildren())
	{
		if (child == limit)
		{
			break;
		}
		
		if (child->is<Named *>() == false)
		{
			continue;
		}
		
		auto named = child->as<Named *>();
		if (named->matchesName(name))
		{
			matches.push_back(named);
		}
	}
	
	return matches;
}

void Block::addStatement(ASTNode *statement)
{
	if (statement == nullptr)
	{
		throw fatal_error("statement was null");
	}
	
	m_statements.push_back(statement);
	addChild(statement, true);
}

void Block::addStatement(ASTNode* statement, const ASTNode *ref, int delta)
{
	assertExists(statement, "statement was null");
	assertExists(ref, "ref was null");
	
	auto pos = std::find(m_statements.begin(), m_statements.end(), ref);
	if (pos == m_statements.end())
	{
		throw fatal_error("reference was not found in list of statements");
	}
	
	m_statements.insert(pos + delta, statement);
	addChild(statement, ref, delta);
}

bool Block::isTerminator() const
{
	for (auto stmt : getStatements())
	{
		if (stmt->is<Statement *>() && stmt->as<Statement *>()->isTerminator())
		{
			return true;
		}
	}
	
	return false;
}

void Block::buildStatements()
{
	for (auto stmt : getStatements())
	{
		getModule()->build(stmt);
		
		if (stmt->is<Statement *>() && stmt->as<Statement *>()->isTerminator())
		{
			break;
		}
	}
}

ASTNode* Block::copy() const
{
	return new Block(*this);
}

std::vector<ObjectBase**> Block::getMemberNodes()
{
	return defMemberNodes();
}

std::vector<std::vector<ObjectBase *>*> Block::getMemberLists()
{
	auto list = defMemberLists();
	list.insert(list.end(), {
		(std::vector<ObjectBase *>*)&m_statements
	});
	return list;
}

void Block::build()
{
	buildStatements();
}

void Block::copyStatements(const Block *orig)
{
	for (auto stmt : orig->getStatements())
	{
		addStatement(stmt->copy());
	}
}

Block::Block()
: Statement()
{
	// Do nothing
}

Block::Block(Module* module)
: Statement(module)
{
	// Do nothing 
}

Block::Block(const Block& other)
{
	copyStatements(&other);
	other.defineCopy(this);
}