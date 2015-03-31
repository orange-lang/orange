/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_FILE_H__ 
#define __ORANGE_FILE_H__

#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/regex.hpp>

#include "config.h"

using namespace boost::filesystem;
using namespace boost;

/**
 * Finds the project directory by looking for a project settings file in the current 
 * and parent directories. If it's not found, a runtime_error is thrown.
 *
 * @return The path of the project directory.
 */
boost::filesystem::path findProjectDirectory();

#endif 