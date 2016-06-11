cmake_minimum_required(VERSION 3.4)
project(orange)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/etc/CMake")

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
   message(FATAL_ERROR "In-source builds are not allowed.
This has created a CMakeFiles directory and a CMakeCache.txt file.
Please delete them before continuing.")
endif("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")

include(clang_complete)

add_subdirectory(lib/libast)

if (${BUILD_CLANG_COMPLETE})
	clang_complete(${CMAKE_SOURCE_DIR}/.clang_complete)
endif()
