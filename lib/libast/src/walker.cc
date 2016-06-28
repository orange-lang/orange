//
// Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <stdexcept>
#include <libast/ast.h>
#include <libast/walker.h>
#include "typecheck.h"

using namespace orange::ast;

void Walker::WalkNode(Visitor* visitor, Node* node) {
}

void Walker::WalkExpr(Visitor* visitor, Expression* node) {
}

void Walker::WalkStmt(Visitor* visitor, Statement* node) {
}

