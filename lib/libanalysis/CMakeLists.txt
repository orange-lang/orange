##
## Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
## directory of this distribution.
##
## Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
## may not be copied, modified, or distributed except according to those terms.
##

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(analysis src/analyze.cc ../../include/libanalysis/analyze.h)

target_include_directories(analysis PRIVATE include)

set_target_properties(analysis PROPERTIES LINKER_LANGUAGE CXX)

target_compile_features(analysis PRIVATE cxx_range_for)

target_link_libraries(analysis ast)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(testanalysis test/test_analysis.cc)
target_include_directories(testanalysis PRIVATE include)
target_link_libraries(testanalysis gtest gtest_main parse ast)
target_compile_features(testanalysis PRIVATE cxx_range_for)
add_test(testanalysis testanalysis)
