/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/Block.h>
#include <grove/Named.h>
#include <grove/Genericable.h>
#include <grove/Module.h>

std::vector<ASTNode *> Block::getStatements() const
{
	return m_statements;
}

Named* Block::getNamed(std::string name, const ASTNode *limit) const
{
	return getNamed(name, nullptr, limit, false, true);
}

Named* Block::namedOrGenericInstance(Named* n, Type* t) const
{
	if (n->is<Genericable *>() &&
		n->as<Genericable *>()->isGeneric())
	{
		auto generic = n->as<Genericable *>();
		if (generic->hasInstance(t))
		{
			return generic->findInstance(t)->as<Named *>();
		}
		else
		{
			auto inst = generic->createInstance(t)->as<Named *>();
			getModule()->resolve(inst->as<ASTNode *>());
			return inst;
		}
	}
	
	return n;
}

Named* Block::getNamed(std::string name, Type* type,
					   const ASTNode *limit, bool forceTypeMatch,
					   bool createGeneric) const
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
			if (forceTypeMatch && type && named->is<Typed *>())
			{
				if (named->as<Typed *>()->matchesType(type) == false)
				{
					continue;
				}
			}
			
			matches.push_back(named);
		}
	}
	
	// If we only had one match, we can return it.
	if (matches.size() == 1)
	{
		if (createGeneric)
		{
    		return namedOrGenericInstance(matches.at(0), type);
		}
		else
		{
			return matches.at(0);
		}
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
			if (createGeneric)
			{
    			return namedOrGenericInstance(match, type);
			}
			else
			{
				return matches.at(0);
			}
		}
	}
	
	return nullptr;
}

void Block::addStatement(ASTNode *statement)
{
	if (statement == nullptr)
	{
		throw std::invalid_argument("statement cannot be null.");
	}
	
	m_statements.push_back(statement);
	addChild(statement, true);
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
		stmt->build();
		
		if (stmt->is<Statement *>() && stmt->as<Statement *>()->isTerminator())
		{
			break;
		}
	}
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