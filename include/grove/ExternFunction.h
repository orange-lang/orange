/*
** Copyright 2014-2017 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include <vector>

#include "Statement.h"
#include "Typed.h"
#include "Named.h"
#include "Valued.h"

class Parameter;
class Type;

class ExternFunction
: public Statement, public Named, public Typed, public Valued
{
private:
	std::vector<Parameter *> m_params;
	
	Type* m_ret_type = nullptr;
	bool m_vararg = false;
public:
	virtual void build() override;
	
	/// Gets the list of parameters as a list of types.
	std::vector<Type *> getParamTys() const;
	
	/// Gets the list of parameters.
	std::vector<Parameter *> getParams() const;
	
	virtual ASTNode* copy() const override;
	
	ExternFunction(OString name, std::vector<Parameter *> params,
				   Type* retType, bool vaarg = false);
};
