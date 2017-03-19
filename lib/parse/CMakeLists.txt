##
## Copyright 2014-2017 Robert Fratto. See the LICENSE.txt file at the top-level
## directory of this distribution.
##
## Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
## may not be copied, modified, or distributed except according to those terms.
##

add_library(parse
	"include/tokens.h"
	"include/lexeme.h"
	"src/parse.cc"
	"src/lexer.cc"
)

target_include_directories(parse PRIVATE include)
set_target_properties(parse PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(parse PRIVATE cxx_range_for)

install(TARGETS parse ARCHIVE DESTINATION lib)
