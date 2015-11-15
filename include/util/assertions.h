/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include <string>

/// Throws an exception if ptr == nullptr.
/// @param err The message of the exception.
void assertExists(void* ptr, std::string err);

/// Throws an exception if a != b.
/// @param err The message of the exception.
void assertEqual(void* a, void* b, std::string err);


