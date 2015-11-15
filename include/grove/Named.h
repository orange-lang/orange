/*
 ** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
 ** directory of this distribution.
 **
 ** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
 ** may not be copied, modified, or distributed except according to those terms.
 */

#pragma once

#include <vector>

class Type;

/**
 * Named is an interface to define any node with a name.
 */
class Named {
protected:
	std::string m_name;
public:
	std::string getName() const;
	
	virtual bool matches(std::string name) const;
	
	virtual bool matches(std::string name, std::vector<Type *> candidates) const;
};