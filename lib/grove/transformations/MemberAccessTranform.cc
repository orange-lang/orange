/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/transformations/TransformRegistry.h>
#include <grove/transformations/TransformBase.h>

#include <grove/ASTNode.h>
#include <grove/IDReference.h>
#include <grove/ClassMethod.h>
#include <grove/MemberVarDecl.h>
#include <grove/AccessExpr.h>
#include <grove/Module.h>

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
			if (ref->is<MemberVarDecl*>() == false) continue;
			
			// We found an IDReference in a method referencing
			// a MemberVarDecl; replace it with a MemberAccess and process it.
			auto this_ref = new IDReference("this");
			auto access = new AccessExpr(this_ref, child->getName());
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