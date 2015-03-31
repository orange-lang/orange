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

add_definitions( -DINSTALL_LOCATION="${CMAKE_INSTALL_PREFIX}" )

# unix specific flags 
if(${APPLE})
	message(STATUS "Detected OS X...")
	list(APPEND CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -g -Wall -fexceptions -O3 -Wno-unused -Wno-deprecated-register")
elseif(${UNIX}) 
	list(APPEND CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -g -Wall -fexceptions -O3 -Wno-unused")
endif()

# windows only... 
if(${WIN32})
	message(STATUS "Detected WIN32...")

	list(APPEND CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -Z7 -w -Ox")
	list(APPEND CXX_DEFINES "${CMAKE_CXX_DEFINES} -DYY_NO_UNISTD_H")
	list(APPEND C_DEFINES "${CMAKE_C_DEFINES} -DYY_NO_UNISTD_H")
endif(${WIN32})

include_directories(etc/cereal/include)

add_subdirectory(lib/libor)
add_subdirectory(lib/helper)
add_subdirectory(lib/gen)
add_subdirectory(tools/oc)
add_subdirectory(test)
