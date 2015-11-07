/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

class Library;
class BuildSettings;

/**
 * Builder provides methods for building and running an orange project 
 * or single orange file.
 */
class Builder {
private:
	Library* m_library = nullptr;
	BuildSettings* m_settings = nullptr;
	
	void initialize();
public:
	/// Returns the library.
	Library* getLibrary() const;
	
	/// Returns the current build settings.
	BuildSettings* getSettings() const;
	
	/// Constructs a builder with the default settings.
	Builder();
	
	/// Constructs a builder with custom settings.
	Builder(BuildSettings* settings);
	
	~Builder();
};