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
#AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/lib/grove/types GROVE_SOURCES)
#AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/lib/grove/commands GROVE_SOURCES)

file(GLOB_RECURSE INCLUDES "${CMAKE_SOURCE_DIR}/include/grove/*.h")

add_library(grove ${GROVE_SOURCES}
	${FLEX_FlexOutput_OUTPUTS} ${BISON_BisonOutput_OUTPUTS} ${INCLUDES}
)

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
