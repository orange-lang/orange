/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include <vector>
#include <string>

#include "Statement.h"
#include "Named.h"
#include "Accessible.h"
#include "Typed.h"
#include "Valued.h"

class Value;

/**
 * EnumStmt represents enums.
 */
class EnumStmt : public Statement, public Typed, public Named,
	public Accessible, public Valued
{
private:
	struct EnumValPair
	{
		std::string name;
		Value* val = nullptr;
		
		EnumValPair(std::string name, Value* val)
		: name(name), val(val)
		{
			// Do nothing
		}
	};
	
	std::vector<EnumValPair> m_members;
public:
	virtual ASTNode* copy() const override;
	
	virtual void build() override;
	
	virtual bool isAccessible() const override;
	
	virtual Expression* access(std::string name, Type* hint) const override;
	
	void addMember(std::string name, Value* val);
	
	EnumStmt(std::string name, Type* baseType);
};
