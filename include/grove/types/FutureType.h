/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include <vector>

#include "WatchableType.h"

class Typed;

/**
 * Represents a type that is meant to be replaced. Only to be used during 
 * resolving generic instances. Shouldn't exist in the AST after resolve. 
 */
class FutureType : public WatchableType
{
public:
	virtual Module* getModule() const override;
	
	virtual std::string getString() const override;
	virtual std::string getSignature() const override;
	
	virtual void findDependencies() override;
	
	virtual const Type* copyType() const override;
	
	virtual ASTNode* copy() const override;
	
	virtual bool isFutureTy() const override;
	
	FutureType(Module* mod);
};
