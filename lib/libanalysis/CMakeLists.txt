##
## Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
## directory of this distribution.
##
## Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
## may not be copied, modified, or distributed except according to those terms.
##

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(analysis src/analyze.cc ../../include/libanalysis/analyze.h ../../include/libanalysis/error.h src/validate.cc include/resolve.h src/resolve.cc src/error.cc include/compatibility.h src/compatibility.cc)

target_include_directories(analysis PRIVATE include)

set_target_properties(analysis PROPERTIES LINKER_LANGUAGE CXX)

target_compile_features(analysis PRIVATE cxx_range_for)

target_link_libraries(analysis ast)

install(TARGETS analysis ARCHIVE DESTINATION lib)
