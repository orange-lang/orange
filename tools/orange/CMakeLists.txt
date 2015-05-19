set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)

find_package(LLVM REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem system regex)

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

llvm_map_components_to_libnames(llvm_libs native core ipo ExecutionEngine Interpreter MCJIT)

find_package(BISON REQUIRED)
bison_target(BisonOutput ${CMAKE_SOURCE_DIR}/tools/orange/parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cc COMPILE_FLAGS "-d")

find_package(FLEX REQUIRED)
flex_target(FlexOutput ${CMAKE_SOURCE_DIR}/tools/orange/lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cc)

include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/tools/orange)

AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/tools/orange ORANGE_SOURCES) 
AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/tools/orange/types ORANGE_SOURCES) 

file(GLOB_RECURSE INCLUDES "${CMAKE_SOURCE_DIR}/*.h")

add_executable(orange 
    ${ORANGE_SOURCES} ${FLEX_FlexOutput_OUTPUTS} ${BISON_BisonOutput_OUTPUTS} ${INCLUDES}
)

target_link_libraries(orange helper ${Boost_LIBRARIES} ${llvm_libs})

ADD_DEPENDENCIES(orange boot)

install(TARGETS orange DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)