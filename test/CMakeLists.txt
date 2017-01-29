##
## Copyright 2014-2017 Robert Fratto. See the LICENSE.txt file at the top-level
## directory of this distribution.
##
## Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
## may not be copied, modified, or distributed except according to those terms.
##

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(unittests libparse/test_lexer.cc)

target_include_directories(unittests
        PRIVATE ../lib/parse/include
)

target_link_libraries(unittests gtest gtest_main parse)
target_compile_features(unittests PRIVATE cxx_range_for)
add_test(unittests unittests)
