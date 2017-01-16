/*
** Copyright 2014-2017 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/OString.h>

OString::operator std::string() const
{
	return m_str;
}

OString operator+(const char* LHS, const OString& RHS)
{
	std::string str = LHS + RHS.str();
	return OString(str);
}

OString operator+(const OString& LHS, const OString& RHS)
{
	std::string str = LHS.str() + RHS.str();
	return OString(str);
}

bool OString::operator!=(const OString& other) const
{
	return m_str != other.m_str;
}

bool OString::operator!=(const std::string& other) const
{
	return m_str != other;
}

bool OString::operator!=(const char* other) const
{
	return m_str != other;
}

bool OString::operator==(const OString& other) const
{
	return m_str == other.m_str;
}

bool OString::operator==(const std::string& other) const
{
	return m_str == other;
}

bool OString::operator==(const char* other) const
{
	return m_str == other;
}

std::string OString::str() const
{
	return m_str;
}

const char* OString::c_str() const
{
	return m_str.c_str();
}

OString::OString()
{
	m_str = "";
}

OString::OString(OString const& str)
{
	m_str = str.str();
	m_location = str.m_location;
}

OString::OString(std::string str)
{
	m_str = str;
}

OString::OString(const char* str)
{
	m_str = str;
}
