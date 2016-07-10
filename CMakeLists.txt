##
## Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
## directory of this distribution.
##
## Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
## may not be copied, modified, or distributed except according to those terms.
##

cmake_minimum_required(VERSION 3.4)
project(orange)
enable_testing()

set(CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}/orange")
set(LLVM_INCLUDE_TESTS OFF CACHE BOOL "Generate build targets for the LLVM unit tests." FORCE)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/etc/CMake")
set(OR_INCLUDES "${CMAKE_SOURCE_DIR}/include")
set(USE_SYSTEM_LLVM OFF CACHE BOOL "Use a pre-installed LLVM instead of building it from source.")
set(LLVM_ENABLE_RTTI ON CACHE BOOL "Build LLVM with run-time type information.")
set(BUILD_ORANGE_TESTS ON CACHE BOOL "Build the Orange tests")

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
   message(FATAL_ERROR "In-source builds are not allowed.
This has created a CMakeFiles directory and a CMakeCache.txt file.
Please delete them before continuing.")
endif("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")

include(clang_complete)

include_directories(${OR_INCLUDES})

# Build LLVM from source
if (NOT ${USE_SYSTEM_LLVM})
    add_subdirectory(etc/llvm)
endif()

add_subdirectory(etc/gtest)
add_subdirectory(lib/libast)
add_subdirectory(lib/libparse)
add_subdirectory(lib/libanalysis)
add_subdirectory(lib/libtranslate)

if (${BUILD_CLANG_COMPLETE})
	clang_complete(${CMAKE_SOURCE_DIR}/.clang_complete)
endif()

if (${BUILD_ORANGE_TESTS})
    add_subdirectory(test)
endif()

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION include)
