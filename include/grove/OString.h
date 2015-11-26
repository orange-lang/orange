/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "CodeBase.h"

class OString : public CodeBase
{
private:
	std::string m_str;
public:
	operator std::string() const;
	
	// Comparisons
	bool operator!=(const OString& other) const;
	bool operator!=(const std::string& other) const;
	bool operator!=(const char* other) const;
	
	bool operator==(const OString& other) const;
	bool operator==(const std::string& other) const;
	bool operator==(const char* other) const;
	
	// Methods
	std::string str() const;
	const char* c_str() const; 
	
	// Constructors
	OString();
	OString(OString const& str);
	OString(std::string str);
	OString(const char* str);
};