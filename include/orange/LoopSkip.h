/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_LOOP_SKIP_H__
#define __ORANGE_LOOP_SKIP_H__

#include "AST.h"

class LoopSkip : public Statement {
private:
	/** 
	 * if true, then this is continue statement. Otherwise, this is a break.
	 */
	bool m_continue = false; 
public:
	virtual std::string getClass() { return "LoopSkip"; }

	virtual std::string string();

	virtual Value* Codegen();

	virtual ASTNode* clone() {
		return new LoopSkip(m_continue);
	}

	LoopSkip(bool isContinue);
}; 

#endif 