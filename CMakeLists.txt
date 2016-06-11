##
## Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
## directory of this distribution.
##
## Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
## may not be copied, modified, or distributed except according to those terms.
##

cmake_minimum_required(VERSION 3.4)
project(orange)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/etc/CMake")
set(OR_INCLUDES "${CMAKE_SOURCE_DIR}/include")

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
   message(FATAL_ERROR "In-source builds are not allowed.
This has created a CMakeFiles directory and a CMakeCache.txt file.
Please delete them before continuing.")
endif("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")

include(clang_complete)

include_directories(${OR_INCLUDES})

add_subdirectory(lib/libast)
add_subdirectory(lib/libparse)

if (${BUILD_CLANG_COMPLETE})
	clang_complete(${CMAKE_SOURCE_DIR}/.clang_complete)
endif()
