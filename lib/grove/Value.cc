/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/Value.h>
#include <grove/types/Type.h>
#include <grove/types/IntType.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Constants.h>
#include <string>

ASTNode* Value::copy() const
{
	return new Value(m_str, m_type, m_base);
}

bool Value::isConstant() const
{
	return true;
}

void Value::build()
{
	auto ty = getType();

	if (ty->isIntTy() && ty->isSigned())
	{
		m_value = llvm::ConstantInt::get(getType()->getLLVMType(), m_values.i,
										 true);
	}
	else if (ty->isIntTy() && ty->isSigned() == false)
	{
		m_value = llvm::ConstantInt::get(getType()->getLLVMType(), m_values.u,
										 false);
	}
	else if (ty->isBoolTy())
	{
		m_value = llvm::ConstantInt::get(getType()->getLLVMType(), m_values.u,
    									 false);	
	}
	else if (ty->isFloatingPointTy())
	{
		m_value = llvm::ConstantFP::get(getType()->getLLVMType(), m_values.d);
	}
	else
	{
		throw std::invalid_argument("invalid type.");
	}
}

Value::Value(char c)
{
	m_values.i = (int)c;
	m_type = IntType::get(8);
}

Value::Value(std::string str, Type* t, int base)
{
	if (t == nullptr)
	{
		throw std::invalid_argument("type must not be null");
	}

	m_type = t;
	m_base = base;
	m_str = str;

	switch (t->PODTy())
	{
		case INT8:
			m_values.i = (int8_t)std::stoll(str, nullptr, base);
			break;
		case INT16:
			m_values.i = (int16_t)std::stoll(str, nullptr, base);
			break;
		case INT32:
			m_values.i = (int32_t)std::stoll(str, nullptr, base);
			break;
		case INT64:
			m_values.i = (int64_t)std::stoll(str, nullptr, base);
			break;
		case UINT1:
			if (str == "false")
			{
				m_values.u = 0;
			}
			else if (str == "true")
			{
				m_values.u = 1;
			}
			break;
		case UINT8:
			m_values.u = (uint8_t)std::stoull(str, nullptr, base);
			break;
		case UINT16:
			m_values.u = (uint16_t)std::stoull(str, nullptr, base);
			break;
		case UINT32:
			m_values.u = (uint32_t)std::stoull(str, nullptr, base);
			break;
		case UINT64:
			m_values.u = (uint64_t)std::stoull(str, nullptr, base);
			break;
		case FLOAT:
			m_values.d = (float)std::stof(str);
			break;
		case DOUBLE:
			m_values.d = (double)std::stod(str);
			break;
		default:
			throw std::invalid_argument("invalid type.");
	}
}
