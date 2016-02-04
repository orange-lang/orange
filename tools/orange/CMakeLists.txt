find_package(LLVM REQUIRED HINTS ${CMAKE_BINARY_DIR}/etc/llvm/cmake/modules/CMakeFiles)
add_definitions(${LLVM_DEFINITIONS})

include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/tools/orange)

AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/tools/orange ORANGE_SOURCES)

file(GLOB_RECURSE INCLUDES "${CMAKE_SOURCE_DIR}/include/orange/*.h")

add_executable(orange-bin ${ORANGE_SOURCES} ${INCLUDES})
set_target_properties(orange-bin PROPERTIES OUTPUT_NAME orange)
set_target_properties(orange-bin PROPERTIES FOLDER tools)

# Test to see if util has been cotired.
get_target_property(UTIL_HAS_PFX util COTIRE_ENABLE_PRECOMPILED_HEADER)
if (${UTIL_HAS_PFX})
  get_target_property(utilPfx util COTIRE_CXX_PREFIX_HEADER)
  set_property(TARGET orange-bin APPEND_STRING PROPERTY COTIRE_CXX_PREFIX_HEADER_INIT "${utilPfx};")
endif()

# Test to see if cmd has been cotired.
get_target_property(CMD_HAS_PFX cmd COTIRE_ENABLE_PRECOMPILED_HEADER)
if (${CMD_HAS_PFX})
  get_target_property(cmdPfx cmd COTIRE_CXX_PREFIX_HEADER)
  set_property(TARGET orange-bin APPEND_STRING PROPERTY COTIRE_CXX_PREFIX_HEADER_INIT "${cmdPfx};")
endif()

# Test to see if grove has been cotired.
get_target_property(GROVE_HAS_PFX ast COTIRE_ENABLE_PRECOMPILED_HEADER)
if (${GROVE_HAS_PFX})
  get_target_property(astPfc ast COTIRE_CXX_PREFIX_HEADER)
  set_property(TARGET orange-bin APPEND_STRING PROPERTY COTIRE_CXX_PREFIX_HEADER_INIT "${astPfx};")
endif()

cotire(orange-bin)

target_link_libraries(orange-bin ast util cmd orange)

ADD_DEPENDENCIES(orange-bin boot util cmd ast orange)

install(TARGETS orange-bin DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
