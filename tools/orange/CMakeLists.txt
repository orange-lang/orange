find_package(LLVM REQUIRED HINTS ${CMAKE_BINARY_DIR}/etc/llvm/cmake/modules/CMakeFiles)

add_definitions(${LLVM_DEFINITIONS})

# llvm_map_components_to_libnames(llvm_libs native core ipo ExecutionEngine Interpreter MCJIT)

llvm_map_components_to_libnames(llvm_libs X86 ipo MCJIT)

set(FLEX_FlexOutput_OUTPUTS "")
set(BISON_BisonOutput_OUTPUTS "")

find_package(BISON)
if (${BISON_FOUND})
    bison_target(BisonOutput ${CMAKE_SOURCE_DIR}/tools/orange/parser.y ${CMAKE_SOURCE_DIR}/tools/orange/parser.cc)
endif()

find_package(FLEX)
if (${FLEX_FOUND})
    flex_target(FlexOutput ${CMAKE_SOURCE_DIR}/tools/orange/lexer.l ${CMAKE_SOURCE_DIR}/tools/orange/lexer.cc)
endif()

include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/tools/orange)

AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/tools/orange ORANGE_SOURCES)
AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/tools/orange/types ORANGE_SOURCES)
AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/tools/orange/commands ORANGE_SOURCES)

file(GLOB_RECURSE INCLUDES "${CMAKE_SOURCE_DIR}/*.h")

add_executable(orange
    ${ORANGE_SOURCES} ${FLEX_FlexOutput_OUTPUTS} ${BISON_BisonOutput_OUTPUTS} ${INCLUDES}
)

target_link_libraries(orange util cmd ${llvm_libs})

ADD_DEPENDENCIES(orange boot)

install(TARGETS orange DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
