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

const void replaceAll(std::string& str, const std::string& from,
					  const std::string& to)
{
	if (from.empty())
	{
		return;
	}
	
	std::string::size_type start_pos = 0;
	
	while ((start_pos = str.find(from, start_pos)) != std::string::npos)
	{
		str.replace(start_pos, from.length(), to);
		
		// Add length in case 'to' contains 'from', like replacing 'x' with 'yx'
		start_pos += to.length(); 
	}
}

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
	m_str = value.substr(1, value.size() - 2);
	replaceAll(m_str, "\\n", "\n");
	replaceAll(m_str, "\\t", "\t");
	replaceAll(m_str, "\\r", "\r");

	setType(PointerType::get(IntType::get(8)));
}