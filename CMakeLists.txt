cmake_minimum_required (VERSION 2.8.8)
project(orange)

enable_testing()

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
   message(SEND_ERROR "In-source builds are not allowed.")
endif("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")

set(oc_SOURCE_DIR ${CMAKE_SOURCE_DIR}/tools/oc)
set(gen_SOURCE_DIR ${CMAKE_SOURCE_DIR}/lib/gen)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/bin)

SET(CMAKE_BUILD_TYPE Release
		CACHE STRING CMAKE_BUILD_TYPE)

add_definitions( -DINSTALL_LOCATION="${CMAKE_INSTALL_PREFIX}" )

# unix specific flags 
if(${APPLE})
	message(STATUS "Detected OS X...")
	list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -Wall -fexceptions -O3 -Wno-unused -Wno-deprecated-register -fdata-sections -ffunction-sections ")
	SET(CMAKE_EXE_LINKER_FLAGS "-Wl,-dead_strip -Wl,-dead_strip_dylibs")
elseif(${UNIX}) 
	list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -Wall -fexceptions -O3 -Wno-unused -fdata-sections -ffunction-sections")
	SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--gc-sections")
endif()

# windows only... 
if(${WIN32})
	message(STATUS "Detected WIN32...")

	list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -Z7 -w -Ox")
	list(APPEND CXX_DEFINES "-DYY_NO_UNISTD_H")
	list(APPEND C_DEFINES "-DYY_NO_UNISTD_H")
endif(${WIN32})

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
	message(STATUS "Setting DEBUG mode...")
  ADD_DEFINITIONS(-DDEBUG)
endif()

find_package(LLVM QUIET)
if(NOT LLVM_FOUND)
	message(STATUS "Need to build LLVM...")
	add_subdirectory(etc/llvm)

	MESSAGE(WARNING "LLVM has been configured, and needs to be built before Orange. Make and install the generated project and then run CMake again.")
else()
	include_directories(etc/cereal/include)

	add_subdirectory(lib/libor)
	add_subdirectory(lib/helper)
	add_subdirectory(tools/orange)
endif()

