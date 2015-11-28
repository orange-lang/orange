/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include <iostream>
#include <vector>

/**
 * Finds the project directory by looking for a project settings file in the current
 * and parent directories. If it's not found, a runtime_error is thrown.
 *
 * @param target The name of the file to find that indicates the project root.
 * @return The path of the project directory.
 */
std::string findProjectDirectory(std::string target);

/// Gets the current working directory.
std::string getWorkingDirectory();

/// Combines two paths into one.
std::string combinePaths(std::string a, std::string b);

/// Creates a temporary file with a prefix and suffix. 
std::string getTempFile(std::string prefix, std::string suffix);

/// Recursively get all files in path and return it in a vector
std::vector<std::string> getFilesRecursive(std::string path,
										   std::string ext = "");

