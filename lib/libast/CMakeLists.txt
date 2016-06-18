##
## Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
## directory of this distribution.
##
## Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
## may not be copied, modified, or distributed except according to those terms.
##

add_library(ast
        ${OR_INCLUDES}/libast/ast.h
        ${OR_INCLUDES}/libast/type.h
        ${OR_INCLUDES}/libast/visitor.h
        ${OR_INCLUDES}/libast/walker.h
        walker.cc ast.cc)

set_target_properties(ast PROPERTIES LINKER_LANGUAGE CXX)

target_compile_features(ast PRIVATE cxx_range_for)
