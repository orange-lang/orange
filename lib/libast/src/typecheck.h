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
static bool isA(Node* node) { return dynamic_cast<T*>(node) != nullptr; }

template <typename T>
static T* asA(Node* node) { return dynamic_cast<T*>(node); }
