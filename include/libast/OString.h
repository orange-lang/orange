/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
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
	
	friend OString operator+(const char* LHS, const OString& RHS);
	friend OString operator+(const OString& LHS, const OString& RHS);
	
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
	
	OString(const OString& str);
	OString(OString&& str) noexcept;
	
	OString(const std::string& str);
	OString(std::string&& str) noexcept;
	
	OString(const char* str);
	
	OString& operator=(const OString& str);
	OString& operator=(OString&& str) noexcept;
	
	OString& operator=(const std::string& str);
	OString& operator=(const std::string&& str) noexcept;
};