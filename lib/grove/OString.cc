/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
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

bool OString::operator==(OString& other)
{
	return m_str == other.m_str;
}

bool OString::operator==(std::string& other)
{
	return m_str == other;
}

bool OString::operator==(const char* other)
{
	return m_str == other;
}

std::string OString::str() const
{
	return m_str;
}

OString::OString(OString& str)
{
	m_str = str.str();
}

OString::OString(std::string& str)
{
	m_str = str;
}

OString::OString(const char* str)
{
	m_str = str;
}
