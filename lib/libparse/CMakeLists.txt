##
## Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
## directory of this distribution.
##
## Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
## may not be copied, modified, or distributed except according to those terms.
##

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(parse lex.h lex.cc stream_helpers.h char_types.cc char_types.h lex_helpers.h lex_helpers.cc)

set_target_properties(parse PROPERTIES LINKER_LANGUAGE CXX)

target_compile_features(parse PRIVATE cxx_range_for)
