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
#include <libast/FunctionCall.h>
#include <libast/ClassMethod.h>
#include <libast/ClassDecl.h>
#include <libast/Module.h>
#include <libast/IDReference.h>
#include <libast/AccessExpr.h>

#include <libast/types/ReferenceType.h>
#include <libast/types/VarType.h>
#include <libast/types/FunctionType.h>

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
		
		auto module = root->getModule();
		
		// Go through all IDReference where it has a parent that is
		// a ClassMethod
		auto children = root->findChildren<FunctionCall*>();
		for (auto child : children)
		{
			if (child->findParent<ClassMethod*>() == nullptr) continue;
			auto the_class = child->findParent<ClassDecl *>();
			
			// Abort out early if the class doesn't have a method
			// with this name.
			if (the_class->hasMethod(child->getName()) == false)
			{
				continue;
			}
			
			// Resolve all the arguments so we can see what we're referring to
			for (auto arg : child->getArgs())
			{
				module->resolve(arg);
			}
			
			auto expected = child->expectedFunctionTy();
			
			// Copy expected, adding a var for this, though.
			std::vector<const Orange::Type*> types;
			types.push_back(Orange::VarType::get(module));
			for (auto type : expected->getArgs())
			{
				types.push_back(type);
			}
			
			expected = Orange::FunctionType::get(module,
												 expected->getReturnTy(),
												 types);
			SearchSettings settings;
			settings.createGeneric = false;
			settings.forceTypeMatch = true;
			settings.includeLimit = false;
			settings.searchWholeTree = false;
			settings.filter = [](Named* named) -> bool
			{
				return named->is<ClassMethod *>();
			};
			
			auto named = the_class->getNamed(child->getName(), expected,
											 nullptr,
											 settings);
			if (named == nullptr)
			{
				continue;
			}
			
			auto method = named->as<ClassMethod*>();
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
			
			module->beginCopy();
			
			auto call = new ExpressionCall(access,
										   copyVector(child->getArgs()),
										   true);
			
			module->endCopy();
			
			child->replace(call);
			module->findDependencies(call);
		
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
