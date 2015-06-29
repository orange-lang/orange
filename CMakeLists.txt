cmake_minimum_required (VERSION 2.8.8)
project(orange)

enable_testing()

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
   message(FATAL_ERROR "In-source builds are not allowed.")
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
	list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -Wall -fexceptions -O3 -Wno-unused -Wno-deprecated-register -fdata-sections -ffunction-sections -g ")
	LINK_DIRECTORIES(/usr/local/lib)
	SET(CMAKE_EXE_LINKER_FLAGS "-Wl,-dead_strip -Wl,-dead_strip_dylibs")
elseif(${UNIX}) 
	list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -Wall -fexceptions -O3 -Wno-unused -fdata-sections -ffunction-sections")
	SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--gc-sections")
endif()

# windows only... 
if(${WIN32})
	message(STATUS "Detected WIN32...")

	list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -Wall -fexceptions -O3 -Wno-unused -fdata-sections -ffunction-sections")
	list(APPEND CXX_DEFINES "-DYY_NO_UNISTD_H")
	list(APPEND C_DEFINES "-DYY_NO_UNISTD_H")
endif(${WIN32})

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
	message(STATUS "Setting DEBUG mode...")
  ADD_DEFINITIONS(-DDEBUG)
endif()

include_directories(etc/cereal/include)

# If we don't have LLVM installed, add the subdirectory to get it 
find_package(LLVM QUIET)
if (NOT ${LLVM_FOUND})
	find_path(LLVM_CMAKE README.txt PATHS ${CMAKE_SOURCE_DIR}/etc/llvm NO_DEFAULT_PATH)

	message(STATUS ${LLVM_CMAKE})

	if (${LLVM_CMAKE} STREQUAL "LLVM_CMAKE-NOTFOUND") 
		message(FATAL_ERROR "You don't have LLVM installed, but llvm was not checked out to etc/llvm. If you are using a cloned repo, init and update git submodules. Otherwise, you will need to download and install LLVM.")
	endif()

	add_subdirectory(etc/llvm)
	include_directories(${CMAKE_SOURCE_DIR}/etc/llvm/include)
	include_directories(${CMAKE_BINARY_DIR}/etc/llvm/include)
else()
	# This is a cheap hack: we'd like to know if the LLVM_INCLUDE_DIRS
	# has all the needed .h files, since it may point to the build folder here.
	# Look for any .h file not normally found in the build folder 
	find_path(DIE DIE.h PATHS ${LLVM_INCLUDE_DIRS} NO_DEFAULT_PATH)
	if (${DIE} STREQUAL "DIE-NOTFOUND") 
		include_directories(${CMAKE_SOURCE_DIR}/etc/llvm/include)
	endif()

	include_directories(${LLVM_INCLUDE_DIRS})
endif()

add_subdirectory(lib/libor)
add_subdirectory(lib/helper)
add_subdirectory(tools/orange)

