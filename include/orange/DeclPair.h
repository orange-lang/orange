/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_DECL_PAIR_H__
#define __ORANGE_DECL_PAIR_H__

#include "AST.h"

struct DeclPair {
	std::string name; 
	Expression* expression; 

	DeclPair() {}
	DeclPair(std::string name, Expression* expression) : name(name), expression(expression) {}
};

#endif 
