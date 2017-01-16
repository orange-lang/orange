/*
** Copyright 2014-2017 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include <string>
#include <vector>

/**
 * Namespace defines namespace for functions and classes.
 */
class Namespace {
private:
	std::string m_name;
	std::vector<Namespace *> m_children;
public:
	/// Gets the name for this namespace.
	std::string getName() const;
	
	/// Gets the children of this namespace. 
	std::vector<Namespace *> getChildren() const;
	
	// Gets the namespace from a path starting from this namespace.
	Namespace* getPath(std::string path);
	
	/// Constructs a new namespace.
	Namespace(std::string name);
};
