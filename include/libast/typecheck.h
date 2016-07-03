/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include <libast/ast.h>

template <typename T>
bool isA(orange::ast::Node* node) { return dynamic_cast<T*>(node) != nullptr; }

template <typename T>
T* asA(orange::ast::Node* node) { return dynamic_cast<T*>(node); }


template <typename T>
bool isA(orange::ast::Flag* flag) { return dynamic_cast<T*>(flag) != nullptr; }

template <typename T>
T* asA(orange::ast::Flag* flag) { return dynamic_cast<T*>(flag); }

template <typename T>
bool isA(orange::ast::Type* type) { return dynamic_cast<T*>(type) != nullptr; }

template <typename T>
T* asA(orange::ast::Type* type) { return dynamic_cast<T*>(type); }

