/*
 ** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
 ** directory of this distribution.
 **
 ** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
 ** may not be copied, modified, or distributed except according to those terms.
 */

#pragma once

#include "ObjectBase.h"

#include <vector>

class Type;

/**
 * Named is an interface to define any node with a name.
 */
class Named : public ObjectBase {
protected:
	std::string m_name;
public:
	/// Gets the name of this node.
	std::string getName() const;

	/// Determines whether or not a name matches this node.
	/// @param name The name to compare against.
	virtual bool matches(std::string name) const;

	/// Determines whether or not a name matches this node.
	/// @param name The name to compare against.
	/// @param candidates A list of candidates to help narrow down if the name
	/// exactly matches the node if the node has extra properties and multiple
	/// nodes with the same name exist.
	virtual bool matches(std::string name, std::vector<Type *> candidates) const;
};
