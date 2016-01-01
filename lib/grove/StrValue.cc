/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
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

bool StrValue::isConstant() const
{
	return true;
}

llvm::Value* StrValue::getValue() const
{
	return IRBuilder()->CreateConstGEP2_32(m_value, 0, 0);
}

ASTNode* StrValue::copy() const
{
	return new StrValue(*this);
}

std::vector<ObjectBase**> StrValue::getMemberNodes()
{
	return defMemberNodes();
}

std::vector<std::vector<ObjectBase *>*> StrValue::getMemberLists()
{
	return defMemberLists();
}

void StrValue::resolve()
{
	setType(Orange::PointerType::get(getModule(),
									 Orange::IntType::get(getModule(), 8)));
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
}

StrValue::StrValue(const StrValue& other)
{
	m_str = other.m_str;
	other.defineCopy(this);
}