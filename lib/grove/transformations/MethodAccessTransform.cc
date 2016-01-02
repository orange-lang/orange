/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/transformations/TransformRegistry.h>
#include <grove/transformations/TransformBase.h>

#include <grove/ASTNode.h>
#include <grove/FunctionCall.h>
#include <grove/ClassMethod.h>
#include <grove/ClassDecl.h>
#include <grove/Module.h>
#include <grove/IDReference.h>
#include <grove/AccessExpr.h>

#include <grove/types/ReferenceType.h>

#include <util/copy.h>

class MethodAccessTransform : public TransformBase
{
public:
	MethodAccessTransform()
	{
		TransformRegistry::get()->registerTransform(this);
	}
	
	void transform(TransformPhase phase, ASTNode* root) const
	{
		if (phase != TransformPhase::PRE_RESOLVE)
		{
			return;
		}
		
		// Go through all IDReference where it has a parent that is
		// a ClassMethod
		auto children = root->findChildren<FunctionCall*>();
		for (auto child : children)
		{
			if (child->findParent<ClassMethod*>() == nullptr) continue;
			auto the_class = child->findParent<ClassDecl *>();
			
			// TODO: see if the functions match, outside of name
			if (the_class->hasMethod(child->getName()) == false)
			{
				continue;
			}
			
			// Resolve all the arguments so we can see what we're referring to
			for (auto arg : child->getArgs())
			{
				arg->getModule()->resolve(arg);
			}
			
			child->expectedFunctionTy();
			
			// TODO: support multiple names here
			ClassMethod* method = nullptr;
			for (auto class_method : the_class->getMethods())
			{
				if (class_method->getName() == child->getName())
				{
					method = class_method;
					break;
				}
			}
			
			ASTNode* accessLHS = nullptr;
			
			// We need to create an access expr to replace the IDReference,
			// but if it's a static member, the LHS is the class name,
			// otherwise it's a reference to "this"
			if (method->getStatic())
			{
				accessLHS = new ReferenceType(the_class);
			}
			else
			{
				accessLHS = new IDReference("this");
			}
			
			auto access = new AccessExpr(accessLHS, child->getName());
			accessLHS->setLocation(child->getLocation());
			access->setLocation(child->getLocation());
			
			child->getModule()->beginCopy();
			
			auto call = new ExpressionCall(access,
										   copyVector(child->getArgs()),
										   true);
			
			child->getModule()->endCopy();
			
			child->replace(call);
			access->getModule()->findDependencies(call);
		
		}
	}
};

void InitMethodAccessTransform()
{
	for (auto transform : TransformRegistry::get()->getTransforms())
	{
		if (dynamic_cast<const MethodAccessTransform *>(transform) != nullptr)
		{
			return;
		}
	}
	
	new MethodAccessTransform();
}
