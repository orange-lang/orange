find_package(LLVM REQUIRED HINTS ${CMAKE_BINARY_DIR}/etc/llvm/cmake/modules/CMakeFiles)

add_definitions(${LLVM_DEFINITIONS})

llvm_map_components_to_libnames(llvm_libs X86 ipo MCJIT)

set(FLEX_FlexOutput_OUTPUTS "")
set(BISON_BisonOutput_OUTPUTS "")

find_package(BISON)
if (${BISON_FOUND})
    bison_target(BisonOutput ${CMAKE_SOURCE_DIR}/lib/libast/parser.y ${CMAKE_SOURCE_DIR}/lib/libast/parser.cc)
endif()

find_package(FLEX)
if (${FLEX_FOUND})
    flex_target(FlexOutput ${CMAKE_SOURCE_DIR}/lib/libast/lexer.l ${CMAKE_SOURCE_DIR}/lib/libast/lexer.cc)
endif()

include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/lib/libast)

AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/lib/libast LIBAST_SOURCES)
AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/lib/libast/types LIBAST_TYPES_SOURCES)
AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/lib/libast/exceptions LIBAST_EXCEPTIONS_SOURCES)
AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/lib/libast/transformations LIBAST_TRANSFORMATIONS_SOURCES)

file(GLOB SRC_INCLUDES )
file(GLOB INCLUDES "${CMAKE_SOURCE_DIR}/include/libast/*.h")
file(GLOB TYPE_INCLUDES "${CMAKE_SOURCE_DIR}/include/libast/types/*.h")
file(GLOB EXCEPTION_INCLUDES "${CMAKE_SOURCE_DIR}/include/libast/exceptions/*.h")
file(GLOB TRANSFORMATION_INCLUDES "${CMAKE_SOURCE_DIR}/include/libast/transformations/*.h")
file(GLOB_RECURSE TEST_FILES "${CMAKE_SOURCE_DIR}/test/*.or")

source_group(parser FILES
	${CMAKE_SOURCE_DIR}/lib/libast/parser.y
	${CMAKE_SOURCE_DIR}/lib/libast/lexer.l
)

source_group(parser\\generated FILES
    ${FLEX_FlexOutput_OUTPUTS} ${BISON_BisonOutput_OUTPUTS}
)

source_group(src FILES ${LIBAST_SOURCES})
source_group(src\\types FILES ${LIBAST_TYPES_SOURCES})
source_group(src\\exceptions FILES ${LIBAST_EXCEPTIONS_SOURCES})
source_group(src\\transformations FILES ${LIBAST_TRANSFORMATIONS_SOURCES})

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

add_library(ast ${LIBAST_SOURCES} ${LIBAST_TYPES_SOURCES} ${LIBAST_EXCEPTIONS_SOURCES}
    ${LIBAST_TRANSFORMATIONS_SOURCES}
	${INCLUDES} ${TYPE_INCLUDES} ${EXCEPTION_INCLUDES} ${TRANSFORMATION_INCLUDES}
	${FLEX_FlexOutput_OUTPUTS} ${BISON_BisonOutput_OUTPUTS}
	${CMAKE_SOURCE_DIR}/lib/libast/lexer.l
	${CMAKE_SOURCE_DIR}/lib/libast/parser.y
    ${TEST_FILES}
)

set_target_properties (ast PROPERTIES FOLDER lib)

# Test to see if util has been cotired.
get_target_property(UTIL_HAS_PFX util COTIRE_ENABLE_PRECOMPILED_HEADER)
if (${UTIL_HAS_PFX})
  get_target_property(utilPfx util COTIRE_CXX_PREFIX_HEADER)
  set_property(TARGET ast APPEND_STRING PROPERTY COTIRE_CXX_PREFIX_HEADER_INIT "${utilPfx};")
endif()

# Test to see if cmd has been cotired.
get_target_property(CMD_HAS_PFX cmd COTIRE_ENABLE_PRECOMPILED_HEADER)
if (${CMD_HAS_PFX})
  get_target_property(cmdPfx cmd COTIRE_CXX_PREFIX_HEADER)
  set_property(TARGET ast APPEND_STRING PROPERTY COTIRE_CXX_PREFIX_HEADER_INIT "${cmdPfx};")
endif()

cotire(ast)

target_link_libraries(ast util cmd ${llvm_libs})

ADD_DEPENDENCIES(ast boot util)
