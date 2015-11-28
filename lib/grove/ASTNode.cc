/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <stdexcept>

#include <grove/ASTNode.h>
#include <grove/Module.h>
#include <grove/Block.h>
#include <grove/ClassTopLevel.h>
#include <grove/ClassDecl.h>

#include <grove/exceptions/fatal_error.h>

#include <util/assertions.h>

void ASTNode::addAllChildrenAsDependencies()
{
	for (auto child : getChildren())
	{
		addDependency(child);
	}
}

Module* ASTNode::getModule() const
{
	if (m_module == nullptr && getParent() != nullptr)
	{
		return getParent()->getModule();
	}
	
	return m_module;
}

ASTNode* ASTNode::getParent() const
{
	return m_parent;
}

IRBuilder* ASTNode::IRBuilder() const
{
	if (getModule() == nullptr)
	{
		return nullptr;
	}
	
	return getModule()->getIRBuilder();
}

std::vector<ASTNode *> ASTNode::getChildren() const
{
	return m_children;
}

std::vector<ASTNode *> ASTNode::getDependencies() const
{
	return m_dependencies;
}

bool ASTNode::dependsOn(ASTNode *node) const
{
	for (auto dependency : getDependencies())
	{
		if (dependency == node)
		{
			return true;
		}
		
		if (dependency->dependsOn(node))
		{
			return true;
		}
	}
	
	return false;
}

void ASTNode::addDependency(ASTNode *dependency)
{
	m_dependencies.push_back(dependency);
}

void ASTNode::addChild(ASTNode *child, bool mustExist)
{
	if (child == nullptr)
	{
		if (mustExist == true)
		{
			throw fatal_error("child cannot be nullptr");
		}
		else
		{
			return;
		}
	}
	
	if (this->is<ClassDecl *>() == false && child->is<ClassTopLevel*>())
	{
		throw fatal_error("Adding a ClassTopLevel in a non-class context");
	}
	
	m_children.push_back(child);
	
	child->m_parent = this;
	child->m_module = getModule();
}

void ASTNode::addChild(ASTNode *child, const ASTNode *ref, int delta)
{
	assertExists(child, "Child must exist");
	assertExists(ref, "Ref must exist");
	
	if (this->is<ClassDecl *>() == false && child->is<ClassTopLevel*>())
	{
		throw fatal_error("Adding a ClassTopLevel in a non-class context");
	}
	
	
	auto pos = std::find(m_children.begin(), m_children.end(), ref);
	if (pos == m_children.end())
	{
		throw fatal_error("reference was not found in list of children");
	}
	
	m_children.insert(pos + delta, child);
	
	child->m_parent = this;
	child->m_module = getModule();
}

bool ASTNode::isRootNode() const
{
	return getParent() == nullptr;
}

ASTNode* ASTNode::copy() const
{
	throw fatal_error("ASTNode::copy() not overriden");
}

void ASTNode::findDependencies()
{
	// By default, add all children as dependencies.
	addAllChildrenAsDependencies();
}

void ASTNode::resolve()
{
	// Do nothing
}

void ASTNode::build()
{
	// Do nothing 
}

bool ASTNode::hasNamed(OString name, SearchSettings settings) const
{
	auto ptr = this;
	
	while (ptr != nullptr)
	{
		// Find the nearest block from this pointer.
		auto block = ptr->findParent<Block *>();
		
		if (block == nullptr)
		{
			break;
		}
		
		// Find closest node whose parent is that block.
		auto limit = ptr;
		while (limit != nullptr)
		{
			if (limit->getParent() == block)
			{
				break;
			}
			
			limit = limit->getParent();
		}
		
		if (block->hasNamed(name, limit, settings))
		{
			return true;
		}
		
		if (settings.searchWholeTree == false)
		{
			break;
		}
		else
		{
			// If we didn't find one, start looking from the block.
			ptr = block;
		}
	}
	
	return false;
}

Named* ASTNode::findNamed(OString name, Type* type,
						  SearchSettings settings)
const
{
	auto ptr = this;
	
	while (ptr != nullptr)
	{
		// Find the nearest block from this pointer.
		auto block = ptr->findParent<Block *>();
		
		if (block == nullptr)
		{
			break;
		}
		
		const ASTNode* limit = nullptr;
		
		if (settings.includeLimit)
		{
    		// Find closest node whose parent is that block.
    		limit = ptr;
    		while (limit != nullptr)
    		{
    			if (limit->getParent() == block)
    			{
    				break;
    			}
    			
    			limit = limit->getParent();
    		}	
		}
		
	
		auto named = block->getNamed(name, type, limit, settings);
		if (named != nullptr)
		{
			return named;
		}		

		if (settings.searchWholeTree == false)
		{
			break;
		}
		else
		{
    		// If we didn't find it, start looking from the block.
    		ptr = block;
		}
	}
	
	return nullptr;
}

std::vector<Named*> ASTNode::findAllNamed(OString name) const
{
	std::vector<Named *> matches;
	
	auto ptr = this;
	while (ptr != nullptr)
	{
		// Find the nearest block from this pointer.
		auto block = ptr->findParent<Block *>();
		
		if (block == nullptr)
		{
			break;
		}
		
		// Find closest node whose parent is that block.
		auto limit = ptr;
		while (limit != nullptr)
		{
			if (limit->getParent() == block)
			{
				break;
			}
			
			limit = limit->getParent();
		}
		
		auto found = block->getAllNamed(name, limit);
		matches.insert(matches.end(), found.begin(), found.end());
		
		ptr = block;
	}
	
	return matches;
}

ASTNode::ASTNode(Module* module)
{
	if (module == nullptr)
	{
		throw fatal_error("module was null");
	}
	
	m_module = module;
}

ASTNode::ASTNode(ASTNode* parent)
{
	if (parent == nullptr)
	{
		throw fatal_error("parent was null");
	}
	
	m_parent = parent;
	m_module = getParent()->getModule();
	
	getParent()->addChild(this);
}

ASTNode::ASTNode()
{
	// Do nothing.
}

ASTNode::~ASTNode()
{
	for (auto child : m_children)
	{
		delete child;
	}
}