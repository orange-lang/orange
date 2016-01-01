/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/CodeBase.h>

CodeLocation CodeBase::getLocation() const
{
	return m_location;
}

void CodeBase::setLocation(CodeLocation loc)
{
	m_location = loc;
}

CodeBase::CodeBase(const CodeBase& other)
: m_location(other.m_location)
{
}

CodeBase::CodeBase(CodeBase&& other) noexcept
: m_location(other.m_location)
{
	other.m_location = CodeLocation("", 0, 0, 0, 0);
}

CodeBase& CodeBase::operator=(const CodeBase& other)
{
	CodeBase tmp(other);
	*this = std::move(tmp);
	return *this;
}

CodeBase& CodeBase::operator=(CodeBase&& other) noexcept
{
	m_location = other.m_location;
	other.m_location = CodeLocation("", 0, 0, 0, 0);
	
	return *this;
}

CodeBase::CodeBase()
: m_location("", 0, 0, 0, 0)
{
	// Do nothing.
}