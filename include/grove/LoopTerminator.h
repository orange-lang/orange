/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "Statement.h"

/// LoopTerminator is any statement that terminates a loop (continue, loop, or
/// break).
class LoopTerminator : public Statement
{
private:
	OString m_terminator = "";
public:
	OString getTerminatorStr() const;
	
	virtual ASTNode* copy() const override;
	
	virtual void resolve() override;
	virtual void build() override;
	
	virtual bool isTerminator() const override;
	
	LoopTerminator(OString terminator);
	LoopTerminator(const LoopTerminator& other);
};
