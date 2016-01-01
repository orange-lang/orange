/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include <vector>
#include <string>

std::vector<std::string> split(const std::string &s, char delim);

/**
 * Allocates a character array and copies the std::string to it.
 * @param str The string to copy.
 * @return Returns the allocated C string.
 */
const char* stringToCharArray(std::string str);

/**
 * Turns a string into a list of command line arguments.
 * Arguments are separated by space, but arguments enclosed in
 * quotations will have spaces ignored.
 * @param str The command line argument string.
 * @return Returns a list of allocated C strings as arguments.
 */
std::vector<const char*> strToArgs(std::string str);
