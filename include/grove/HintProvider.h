/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "CodeBase.h"

/**
 * Can be prompted to provide a hint for certain operations like searching 
 * the AST tree for a node. 
 */
class HintProvider : public CodeBase
{
public:
	virtual bool providesHint() const;
	virtual CodeBase* getHint() const;
};