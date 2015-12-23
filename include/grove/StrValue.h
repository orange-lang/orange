/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include <string>

#include "Expression.h"

namespace llvm { class Value; }

/**
 * StrValue represents a constant string.
 */
class StrValue : public Expression {
private:
	std::string	m_str;
public:
	virtual llvm::Value* getValue() const override;
	
	virtual ASTNode* copy() const override;
	
	virtual void resolve() override;
	virtual void build() override;
	
	virtual bool isConstant() const override;
	
	StrValue(std::string value);
	StrValue(const StrValue& other);
};
