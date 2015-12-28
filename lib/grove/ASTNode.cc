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

void ASTNode::defineCopy(const ASTNode *copy) const
{
	getModule()->defineCopy(this, copy);
}

Module* ASTNode::getModule() const
{
	if (m_module == nullptr && getParent() != nullptr)
	{
		return getParent()->getModule();
	}
	
	return m_module;
}

void ASTNode::setModule(Module *module)
{
	m_module = module;
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

bool ASTNode::isChild(const ASTNode *child) const
{
	auto it = std::find(m_children.begin(), m_children.end(), child);
	return it != m_children.end();
}

void ASTNode::addDependency(ASTNode *dependency)
{
	if (dependency != nullptr)
	{
    	m_dependencies.push_back(dependency);
	}
}

void ASTNode::addChild(ASTNode *child, int idx, bool mustExist)
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
	
	if (child->m_parent != nullptr)
	{
		throw fatal_error("Child already has a parent");
	}
	
	m_children.insert(m_children.begin()+idx, child);
	
	child->m_parent = this;
	child->m_module = getModule();
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
	
	if (child->m_parent != nullptr)
	{
		throw fatal_error("Child already has a parent");
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
	
	if (child->m_parent != nullptr)
	{
		throw fatal_error("Child already has a parent");
	}
	
	m_children.insert(pos + delta, child);
	
	child->m_parent = this;
	child->m_module = getModule();
}

void ASTNode::removeChild(ASTNode *child)
{
	assertExists(child, "Child must not be null!");
	
	auto it = std::find(m_children.begin(), m_children.end(), child);
	if (it == m_children.end())
	{
		throw fatal_error("element was not found in list of children");
	}
	
	m_children.erase(it);
	child->m_parent = nullptr;
	child->m_module = nullptr;
}

bool ASTNode::isRootNode() const
{
	return getParent() == nullptr;
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
	return getModule()->hasNamed(name, this, settings);
}

Named* ASTNode::findNamed(OString name, const Type* type,
						  SearchSettings settings)
const
{
	return getModule()->findNamed(name, type, this, settings);
}

std::vector<Named*> ASTNode::findAllNamed(OString name) const
{
	return getModule()->findAllNamed(name, this);
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