include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(ast
        ${OR_INCLUDES}/libast/ast.h
        ${OR_INCLUDES}/libast/type.h
        ${OR_INCLUDES}/libast/visitor.h
        ${OR_INCLUDES}/libast/walker.h
        walker.cc)

set_target_properties(ast PROPERTIES LINKER_LANGUAGE CXX)

target_compile_features(ast PRIVATE cxx_range_for)
