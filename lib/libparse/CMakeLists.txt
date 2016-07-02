##
## Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
## directory of this distribution.
##
## Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
## may not be copied, modified, or distributed except according to those terms.
##

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(parse include/lex.h
        src/lex.cc
        include/stream_helpers.h
        src/char_types.cc
        include/char_types.h
        include/lex_helpers.h
        src/lex_helpers.cc ../../include/libparse/parser.h include/lex_stream.h src/lex_stream.cc src/parser.cc)

target_include_directories(parse PRIVATE include)

set_target_properties(parse PROPERTIES LINKER_LANGUAGE CXX)

target_compile_features(parse PRIVATE cxx_range_for)

target_link_libraries(parse ast)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(testparse test/helpers.cc test/test_lexer.cc
        test/helpers.h test/test_lex_helpers.cc test/test_lex_stream.cc)
target_include_directories(testparse PRIVATE include)
target_link_libraries(testparse gtest gtest_main parse ast)
target_compile_features(testparse PRIVATE cxx_range_for)
add_test(testparse testparse)
