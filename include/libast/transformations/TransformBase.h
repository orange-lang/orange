/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

class ASTNode;

enum TransformPhase
{
	PRE_INITIALIZE,
	PRE_FIND_DEPENDENCIES,
	PRE_RESOLVE,
	PRE_BUILD
};

class TransformBase
{
public:
	/// Transforms the AST.
	virtual void transform(TransformPhase phase, ASTNode* root) const = 0;
};

extern void InitMemberAccessTransform();
extern void InitMethodAccessTransform();

void InitAllTransforms()
{
	InitMemberAccessTransform();
	InitMethodAccessTransform();
}