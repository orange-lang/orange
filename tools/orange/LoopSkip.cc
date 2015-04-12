/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/LoopSkip.h>
#include <orange/Loop.h>
#include <orange/generator.h>

Value* LoopSkip::Codegen() {
 	Loop* curLoop = (Loop *)GE::runner()->symtab()->findStructure("Loop");

 	if (curLoop == nullptr) {
 		throw CompilerMessage(*this, "not in a loop!");
 	}

 	if (m_continue) {
 		GE::builder()->CreateBr(curLoop->afterthoughtBlock());
 	} else {
 		GE::builder()->CreateBr(curLoop->continueBlock()); 		
 	}

	return nullptr; 
}

LoopSkip::LoopSkip(bool isContinue) {
	m_continue = isContinue; 
}
