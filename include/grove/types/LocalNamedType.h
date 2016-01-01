/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include "NamedType.h"

class Module;

/**
 * LocalNamedType is a NamedType with a module.
 */
class LocalNamedType : public NamedType {
private:
	Module* m_module;
public:
	Module* getModule() const;
	
	LocalNamedType(Module* mod, std::string name, Orange::Type* type);
};
