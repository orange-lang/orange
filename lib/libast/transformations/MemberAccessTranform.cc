/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <libast/transformations/TransformRegistry.h>
#include <libast/transformations/TransformBase.h>

#include <libast/ASTNode.h>
#include <libast/IDReference.h>
#include <libast/ClassMethod.h>
#include <libast/ClassDecl.h>
#include <libast/MemberVarDecl.h>
#include <libast/AccessExpr.h>
#include <libast/Module.h>

#include <libast/types/ReferenceType.h>

class MemberAccessTransform : public TransformBase
{
public:
	MemberAccessTransform()
	{
		TransformRegistry::get()->registerTransform(this);
	}
	
	void transform(TransformPhase phase, ASTNode* root) const
	{
		// Only resolve when we're on PRE_FIND_DEPENDENCIES
		if (phase != TransformPhase::PRE_FIND_DEPENDENCIES)
		{
			return;
		}
		
		// Go through all IDReference where it has a parent that is
		// a ClassMethod
		auto children = root->findChildren<IDReference*>();
		for (auto child : children)
		{
			if (child->findParent<ClassMethod*>() == nullptr) continue;
			auto ref = child->findNamed(child->getName(), nullptr);
			
			// If it is not referencing a MemberVarDecl, continue onwards.
			if (ref == nullptr || ref->is<MemberVarDecl*>() == false)
			{
				continue;
			}
			
			auto member = ref->as<MemberVarDecl *>();
			
			ASTNode* accessLHS = nullptr;
			
			// We need to create an access expr to replace the IDReference,
			// but if it's a static member, the LHS is the class name,
			// otherwise it's a reference to "this"
			if (member->getStatic())
			{
				auto parent_class = member->findParent<ClassDecl *>();
				accessLHS = new ReferenceType(parent_class);
			}
			else
			{
				accessLHS = new IDReference("this");
			}
			
			auto access = new AccessExpr(accessLHS, child->getName());
			accessLHS->setLocation(child->getLocation());
			access->setLocation(child->getLocation());
			child->replace(access);		
		}
	}
};

void InitMemberAccessTransform()
{
	for (auto transform : TransformRegistry::get()->getTransforms())
	{
		if (dynamic_cast<const MemberAccessTransform *>(transform) != nullptr)
		{
			return;
		}
	}
	
	new MemberAccessTransform();
}