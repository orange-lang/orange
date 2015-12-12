/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "NodeType.h"

class ReferenceType : public NodeType
{
protected:
	OString m_name;
	ASTNode* m_reference = nullptr;
public:
	OString getName() const;
	
	ASTNode* getReference() const;
	
	virtual void resolve();
	
	ReferenceType(OString name);
};