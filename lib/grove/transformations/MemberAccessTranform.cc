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

class MemberAccessTransform : public TransformBase
{
public:
	MemberAccessTransform()
	{
		TransformRegistry::get()->registerTransform(this);
	}
	
	void transform(TransformPhase phase, ASTNode* root) const
	{
		/// @todo: implement 
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