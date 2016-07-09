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

/// Returns whether or not a type is an integer type.
bool IsIntegerType(orange::ast::Type* type);

/// Gets whether or not the type is signed.
bool IsSignedType(orange::ast::Type* type);

/// Gets whether or not a type is a floating point type.
bool IsFloatingPointType(orange::ast::Type* type);

/// Gets whether or not a type is a void type.
bool IsVoidType(orange::ast::Type* type);

/// Gets the integer bit width of a type. Return -1 if the type is not an integer type.
int GetIntegerBitWidth(orange::ast::Type* type);
