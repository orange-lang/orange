/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_ANY_TYPE_H__
#define __ORANGE_ANY_TYPE_H__

#include "AST.h"

class AnyType : public CodeElement {
private:
	Type* m_type;
	std::string m_type_str;

	bool m_signed = false;
public:
	std::string string() const { return m_type_str; }
	Type* getType() const { return m_type; }
	bool isSigned() const { return m_signed; }

	AnyType(Type* type, bool isSigned = false);
	AnyType(std::string type);
}; 

#endif 