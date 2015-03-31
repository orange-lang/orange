#ifndef __ORANGE_FILE_H__ 
#define __ORANGE_FILE_H__

#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/regex.hpp>

#include "config.h"

/**
 * Finds the project directory by looking for a project settings file in the current 
 * and parent directories. If it's not found, a runtime_error is thrown.
 *
 * @return The path of the project directory.
 */
boost::filesystem::path findProjectDirectory();

#endif 