/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/Builder.h>
#include <grove/BuildSettings.h>
#include <grove/Library.h>

Library* Builder::getLibrary() const
{
	return m_library;
}

BuildSettings* Builder::getSettings() const
{
	return m_settings;
}

void Builder::initialize()
{
	m_library = new Library();
}

Builder::Builder()
{
	m_settings = new BuildSettings();
}

Builder::Builder(BuildSettings* settings)
{
	m_settings = settings;
}

Builder::~Builder()
{
	delete m_library;
	delete m_settings;
}