/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
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
 * Represents a type that can be watched for changes.
 */
class WatchableType : public NodeType
{
protected:
	std::vector<Typed *> m_watchers;
	
	WatchableType();
public:
	virtual std::vector<ObjectBase **> getMemberNodes() override;
	virtual std::vector<std::vector<ObjectBase *>*> getMemberLists() override;
	
	/// Gets the type from each watcher and replaces it with another type.
	/// If the watcher's type is an aggregate, looks for the FutureType
	/// and replaces that instead. Removes all watchers.
	void replace(const Type* with);
	
	void addWatcher(Typed* watcher);
	
	void removeWatcher(Typed* watcher);
};
