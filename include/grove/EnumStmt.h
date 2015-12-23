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
		OString name;
		Value* val = nullptr;
		
		EnumValPair(OString name, Value* val)
		: name(name), val(val)
		{
			// Do nothing
		}
	};
	
	const Type* m_base_type = nullptr;
	std::vector<EnumValPair> m_members;
public:
	virtual ASTNode* copy() const override;
	
	virtual void resolve() override;
	virtual void build() override;
	
	virtual bool isAccessible() const override;
	
	virtual Expression* access(OString name, const ASTNode* hint) const override;
	
	void addMember(OString name, Value* val);
	
	EnumStmt(OString name, Module* mod, const Type* baseType);
	EnumStmt(const EnumStmt& other);
};
