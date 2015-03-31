cmake_minimum_required (VERSION 2.8.8)
project (oc)
set(oc_SOURCE_DIR ${CMAKE_SOURCE_DIR}/tools/oc)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -fexceptions -O3")

if(${UNIX}) 
	list(APPEND CMAKE_CXX_FLAGS "-Wno-unused -Wno-deprecated-register")
endif(${UNIX})

if(${WIN32})
	message(STATUS "Detected WIN32...")

	list(APPEND CXX_DEFINES "${CMAKE_CXX_DEFINES} -DYY_NO_UNISTD_H")
	list(APPEND CXX_DEFINES "${CMAKE_C_DEFINES} -DYY_NO_UNISTD_H")
endif(${WIN32})

# LLVM stuff
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

llvm_map_components_to_libnames(llvm_libs native core)

FIND_PACKAGE(BISON REQUIRED)
bison_target(BisonOutput ${oc_SOURCE_DIR}/parser.y ${oc_SOURCE_DIR}/parser.cc COMPILE_FLAGS "-d")

FIND_PACKAGE(FLEX REQUIRED)
flex_target(FlexOutput ${oc_SOURCE_DIR}/lexer.l ${oc_SOURCE_DIR}/lexer.cc)

include_directories(include/oc)

AUX_SOURCE_DIRECTORY(${oc_SOURCE_DIR} OC_SOURCES) 

add_executable(oc 
	${OC_SOURCES}
	${FLEX_FlexOutput_OUTPUTS} ${BISON_BisonOutput_OUTPUTS}
)

target_link_libraries(oc ${llvm_libs})
