##
## Copyright 2014-2017 Robert Fratto. See the LICENSE.txt file at the top-level
## directory of this distribution.
##
## Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
## may not be copied, modified, or distributed except according to those terms.
##

add_library(ast
	${INCLUDES}/ast/ast.h
	${INCLUDES}/ast/type.h
	${INCLUDES}/ast/module.h
	src/ast.cc
)

target_include_directories(ast PRIVATE include)
set_target_properties(ast PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(ast PRIVATE cxx_range_for)

install(TARGETS ast ARCHIVE DESTINATION lib)