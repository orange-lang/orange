##
## Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
## directory of this distribution.
##
## Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
## may not be copied, modified, or distributed except according to those terms.
##

if (NOT ${USE_SYSTEM_LLVM})
    include_directories(${CMAKE_SOURCE_DIR}/etc/llvm/include)
    include_directories(${CMAKE_BINARY_DIR}/etc/llvm/include)
endif()

find_package(LLVM REQUIRED HINTS ${CMAKE_BINARY_DIR}/etc/llvm/cmake/modules/CMakeFiles)

add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(unittests libanalysis/test_analysis.cc libparse/helpers.cc libparse/test_lex_helpers.cc
        libparse/test_lex_stream.cc libparse/test_lexer.cc libparse/test_parser.cc libtranslate/test_translate.cc)

target_include_directories(unittests
        PRIVATE ../lib/libanalysis/include
        PRIVATE ../lib/libast/include
        PRIVATE ../lib/libparse/include
        PRIVATE ../lib/libtranslate/include
)

target_link_libraries(unittests gtest gtest_main analysis ast parse translate)
target_compile_features(unittests PRIVATE cxx_range_for)
add_test(unittests unittests)
