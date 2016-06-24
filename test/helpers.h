//
// Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#pragma once

#include <gtest/gtest.h>
#include <libparse/lex.h>

template <typename T>
bool tokensEq(orange::parser::Token* tok, T to);

template <typename T>
void expectToken(orange::parser::Lexer& l, T val);
