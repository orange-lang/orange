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

llvm_map_components_to_libnames(llvm_libs core)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(translate src/translate.cc ../../include/libtranslate/translate.h include/translate_visitor.h src/translate_visitor.cc include/type_converter.h src/type_converter.cc include/llvm_helpers.h src/llvm_helpers.cc)

target_include_directories(translate PRIVATE include)
set_target_properties(translate PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(translate PRIVATE cxx_range_for)
target_link_libraries(translate ast analysis ${llvm_libs})

install(TARGETS translate ARCHIVE DESTINATION lib)
