##
## Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
## directory of this distribution.
##
## Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
## may not be copied, modified, or distributed except according to those terms.
##

find_package(LLVM REQUIRED HINTS ${CMAKE_BINARY_DIR}/etc/llvm/cmake/modules/CMakeFiles)

add_definitions(${LLVM_DEFINITIONS})

llvm_map_components_to_libnames(llvm_libs core)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(translate src/translate.cc ../../include/libtranslate/translate.h)

target_include_directories(translate PRIVATE include)
set_target_properties(translate PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(translate PRIVATE cxx_range_for)
target_link_libraries(translate ast analysis ${llvm_libs})

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(testtranslate test/test_translate.cc)
target_include_directories(testtranslate PRIVATE include)
target_link_libraries(testtranslate gtest gtest_main parse ast translate ${llvm_libs})
target_compile_features(testtranslate PRIVATE cxx_range_for)
add_test(testtranslate testtranslate)

install(TARGETS translate ARCHIVE DESTINATION lib)
