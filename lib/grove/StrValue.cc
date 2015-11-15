/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/StrValue.h>

#include <grove/types/PointerType.h>
#include <grove/types/IntType.h>

#include <llvm/IR/IRBuilder.h>

llvm::Value* StrValue::getValue() const
{
	return IRBuilder()->CreateConstGEP2_32(m_value, 0, 0);
}

void StrValue::build()
{
	auto val = IRBuilder()->CreateGlobalString(m_str);
	setValue(val);
}

StrValue::StrValue(std::string value)
{
	m_str = value;
	setType(PointerType::get(IntType::get(8)));
}