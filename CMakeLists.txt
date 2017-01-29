##
## Copyright 2014-2017 Robert Fratto. See the LICENSE.txt file at the top-level
## directory of this distribution.
##
## Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
## may not be copied, modified, or distributed except according to those terms.
##

cmake_minimum_required(VERSION 3.4)
project(orange)
enable_testing()

set(CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}/orange")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/etc/CMake")
set(INCLUDES "${CMAKE_SOURCE_DIR}/include")

set(gtest_force_shared_crt ON CACHE BOOL "Use shared (DLL) run-time lib even when Google Test is built as static lib.")
set(BUILD_ORANGE_TESTS ON CACHE BOOL "Build the Orange tests")

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
   message(FATAL_ERROR "In-source builds are not allowed.
This has created a CMakeFiles directory and a CMakeCache.txt file.
Please delete them before continuing.")
endif("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")

include_directories("${CMAKE_SOURCE_DIR}/include")

add_subdirectory(etc/gtest)

add_subdirectory(lib/analysis)
add_subdirectory(lib/ast)
add_subdirectory(lib/generate)
add_subdirectory(lib/parse)
add_subdirectory(lib/translate)
add_subdirectory(tools/oc)

if (${BUILD_ORANGE_TESTS})
    add_subdirectory(test)
endif()

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include DESTINATION include)
