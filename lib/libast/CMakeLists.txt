include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(ast
        include/libast/ast.h
        include/libast/type.h
        include/libast/visitor.h
        include/libast/walker.h
        src/walker.cc)

set_target_properties(ast PROPERTIES LINKER_LANGUAGE CXX)

target_compile_features(ast PRIVATE cxx_range_for)
