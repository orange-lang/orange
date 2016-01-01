/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include <iostream>
#include "config.h"

/**
 * Finds the project directory by looking for a project settings file in the current
 * and parent directories. If it's not found, a runtime_error is thrown.
 *
 * @return The path of the project directory.
 */
std::string findProjectDirectory();
