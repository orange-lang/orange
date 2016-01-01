/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include <string>

namespace Orange { class Type; }

/**
 * NamedType is a container class to hold a type and a name. 
 * NamedTypes are used in the library.
 */
class NamedType {
private:
	Orange::Type* m_type;
	std::string m_name;
public:
	/// Gets the type of this NamedType.
	Orange::Type* getType() const;
	
	/// Gets the name of this type.
	std::string getName() const;
	
	/// Gets the mangled named of this type.
	std::string getMangledName() const;
	
	/// Constructs a new named type with name and type.
	NamedType(std::string name, Orange::Type* type);
};
