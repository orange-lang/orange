find_package(LLVM REQUIRED HINTS ${CMAKE_BINARY_DIR}/etc/llvm/cmake/modules/CMakeFiles)

add_definitions(${LLVM_DEFINITIONS})

llvm_map_components_to_libnames(llvm_libs X86 ipo MCJIT)

set(FLEX_FlexOutput_OUTPUTS "")
set(BISON_BisonOutput_OUTPUTS "")

find_package(BISON)
if (${BISON_FOUND})
    bison_target(BisonOutput ${CMAKE_SOURCE_DIR}/lib/grove/parser.y ${CMAKE_SOURCE_DIR}/lib/grove/parser.cc)
endif()

find_package(FLEX)
if (${FLEX_FOUND})
    flex_target(FlexOutput ${CMAKE_SOURCE_DIR}/lib/grove/lexer.l ${CMAKE_SOURCE_DIR}/lib/grove/lexer.cc)
endif()

include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/lib/grove)

AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/lib/grove GROVE_SOURCES)
AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/lib/grove/types GROVE_TYPES_SOURCES)
AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/lib/grove/exceptions GROVE_EXCEPTIONS_SOURCES)
AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/lib/grove/transformations GROVE_TRANSFORMATIONS_SOURCES)

file(GLOB SRC_INCLUDES )
file(GLOB INCLUDES "${CMAKE_SOURCE_DIR}/include/grove/*.h")
file(GLOB TYPE_INCLUDES "${CMAKE_SOURCE_DIR}/include/grove/types/*.h")
file(GLOB EXCEPTION_INCLUDES "${CMAKE_SOURCE_DIR}/include/grove/exceptions/*.h")
file(GLOB TRANSFORMATION_INCLUDES "${CMAKE_SOURCE_DIR}/include/grove/transformations/*.h")
file(GLOB_RECURSE TEST_FILES "${CMAKE_SOURCE_DIR}/test/*.or")

source_group(parser FILES
	${CMAKE_SOURCE_DIR}/lib/grove/parser.y
	${CMAKE_SOURCE_DIR}/lib/grove/lexer.l
)

source_group(parser\\generated FILES
    ${FLEX_FlexOutput_OUTPUTS} ${BISON_BisonOutput_OUTPUTS}
)

source_group(src FILES ${GROVE_SOURCES})
source_group(src\\types FILES ${GROVE_TYPES_SOURCES})
source_group(src\\exceptions FILES ${GROVE_EXCEPTIONS_SOURCES})
source_group(src\\transformations FILES ${GROVE_TRANSFORMATIONS_SOURCES})

source_group(headers FILES ${INCLUDES})
source_group(headers\\types FILES ${TYPE_INCLUDES})
source_group(headers\\exceptions FILES ${EXCEPTION_INCLUDES})
source_group(headers\\transformations FILES ${TRANSFORMATION_INCLUDES})

# Add test files to their relative path in the source_group
foreach(test_file ${TEST_FILES})
    file(RELATIVE_PATH relative_file ${CMAKE_SOURCE_DIR} ${test_file})
    get_filename_component(relative_path ${relative_file} DIRECTORY)
    string(REPLACE "/" "\\" relative_path ${relative_path})
    source_group(${relative_path} FILES ${test_file})
endforeach()

add_library(grove ${GROVE_SOURCES} ${GROVE_TYPES_SOURCES} ${GROVE_EXCEPTIONS_SOURCES}
    ${GROVE_TRANSFORMATIONS_SOURCES}
	${INCLUDES} ${TYPE_INCLUDES} ${EXCEPTION_INCLUDES} ${TRANSFORMATION_INCLUDES}
	${FLEX_FlexOutput_OUTPUTS} ${BISON_BisonOutput_OUTPUTS}
	${CMAKE_SOURCE_DIR}/lib/grove/lexer.l
	${CMAKE_SOURCE_DIR}/lib/grove/parser.y
    ${TEST_FILES}
)

set_target_properties (grove PROPERTIES FOLDER lib)

# Test to see if util has been cotired.
get_target_property(UTIL_HAS_PFX util COTIRE_ENABLE_PRECOMPILED_HEADER)
if (${UTIL_HAS_PFX})
  get_target_property(utilPfx util COTIRE_CXX_PREFIX_HEADER)
  set_property(TARGET grove APPEND_STRING PROPERTY COTIRE_CXX_PREFIX_HEADER_INIT "${utilPfx};")
endif()

# Test to see if cmd has been cotired.
get_target_property(CMD_HAS_PFX cmd COTIRE_ENABLE_PRECOMPILED_HEADER)
if (${CMD_HAS_PFX})
  get_target_property(cmdPfx cmd COTIRE_CXX_PREFIX_HEADER)
  set_property(TARGET grove APPEND_STRING PROPERTY COTIRE_CXX_PREFIX_HEADER_INIT "${cmdPfx};")
endif()

cotire(grove)

target_link_libraries(grove util cmd ${llvm_libs})

ADD_DEPENDENCIES(grove boot util)
