/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include <vector>

#include "NodeType.h"

class Typed;

/**
 * Represents a type that is meant to be replaced. Only to be used during 
 * resolving generic instances. Shouldn't exist in the AST after resolve. 
 */
class FutureType : public NodeType
{
protected:
	std::vector<Typed *> m_watchers;
public:
	virtual Module* getModule() const override;
	
	virtual std::string getString() const override;
	virtual std::string getSignature() const override;
	
	virtual void findDependencies() override;
	
	virtual ASTNode* copy() const override;
	
	virtual std::vector<std::vector<ObjectBase *>*> getMemberLists() override;
	
	virtual bool isFutureTy() const override;
	
	/// Gets the type from each watcher and replaces it with another type.
	/// If the watcher's type is an aggregate, looks for the FutureType
	/// and replaces that instead. Removes all watchers. 
	void replace(Type* with);
	
	void addWatcher(Typed* watcher);
	
	void removeWatcher(Typed* watcher);
	
	FutureType(Module* mod);
};
