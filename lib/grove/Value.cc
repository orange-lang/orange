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

#include <grove/exceptions/invalid_type_error.h>
#include <grove/exceptions/fatal_error.h>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Constants.h>

#include <string>

Value::Value()
{
	// Do nothing.
}

ASTNode* Value::copy() const
{
	auto val = new Value();
	val->setType(getType()->copyType());
	val->m_values = m_values;
	
	defineCopy(val);
	return val;
}

bool Value::isConstant() const
{
	return true;
}

int64_t Value::getInt() const
{
	return m_values.i;
}

uint64_t Value::getUInt() const
{
	return m_values.u;
}

double Value::getDouble() const
{
	return m_values.d;
}

void Value::resolve()
{
	if (m_char_const)
	{
    	m_type = IntType::get(getModule(),8);
	}
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
		throw fatal_error("invalid type for Value");
	}
}

void Value::convert(const Type* new_ty)
{
	if (new_ty->isIntTy() == false && new_ty->isFloatingPointTy())
	{
		throw fatal_error("invalid type for Value conversion");
	}
	
	auto old_ty = getType();
	
	if (old_ty == new_ty)
	{
		return;
	}
	
	if (old_ty->isIntTy() && old_ty->isSigned())
	{
		if (new_ty->isIntTy() && new_ty->isSigned() == false)
		{
			m_values.u = (uint64_t)m_values.i;
		}
		else if (new_ty->isFloatingPointTy())
		{
			m_values.d = (double)m_values.i;
		}
	}
	else if (old_ty->isIntTy() && old_ty->isSigned() == false)
	{
		if (new_ty->isIntTy() && new_ty->isSigned())
		{
			m_values.i = (uint64_t)m_values.u;
		}
		else if (new_ty->isFloatingPointTy())
		{
			m_values.d = (double)m_values.u;
		}
	}
	else if (old_ty->isFloatingPointTy())
	{
		if (new_ty->isIntTy() && new_ty->isSigned())
		{
			m_values.i = (uint64_t)m_values.d;
		}
		else if (new_ty->isIntTy() && new_ty->isSigned() == false)
		{
			m_values.u = (double)m_values.d;
		}
	}
	
	setType(new_ty);
}

Value* Value::addDelta(int64_t d) const
{
	Value* v = new Value();
	v->setType(getType());
	
	if (getType()->isIntTy() && getType()->isSigned())
	{
		v->m_values.i = m_values.i + d;
	}
	else if (getType()->isIntTy() && getType()->isSigned() == false)
	{
		v->m_values.u = m_values.u + d;
	}
	else if (getType()->isBoolTy())
	{
		v->m_values.u = m_values.u + d;
	}
	else if (getType()->isFloatingPointTy())
	{
		v->m_values.d = m_values.d + d;
	}
	
	return v;
}

void Value::negate()
{
	if (getType()->isIntTy() && getType()->isSigned() == false)
	{
		throw invalid_type_error(this, "cannot negate value of type", getType());
	}
	
	if (getType()->isIntTy())
	{
		m_values.i = -m_values.i;
	}
	else if (getType()->isFloatingPointTy())
	{
		m_values.d = -m_values.d;
	}
}

Value::Value(char c)
{
	m_values.i = (int)c;
	m_char_const = true;
}

Value::Value(std::string str, const Type* t, int base)
{
	if (t == nullptr)
	{
		throw fatal_error("type was null");
	}

	m_type = t;

	switch (t->PODTy())
	{
		case TYINT8:
			m_values.i = (int8_t)std::stoll(str, nullptr, base);
			break;
		case TYINT16:
			m_values.i = (int16_t)std::stoll(str, nullptr, base);
			break;
		case TYINT32:
			m_values.i = (int32_t)std::stoll(str, nullptr, base);
			break;
		case TYINT64:
			m_values.i = (int64_t)std::stoll(str, nullptr, base);
			break;
		case TYUINT1:
			if (str == "false")
			{
				m_values.u = 0;
			}
			else if (str == "true")
			{
				m_values.u = 1;
			}
			break;
		case TYUINT8:
			m_values.u = (uint8_t)std::stoull(str, nullptr, base);
			break;
		case TYUINT16:
			m_values.u = (uint16_t)std::stoull(str, nullptr, base);
			break;
		case TYUINT32:
			m_values.u = (uint32_t)std::stoull(str, nullptr, base);
			break;
		case TYUINT64:
			m_values.u = (uint64_t)std::stoull(str, nullptr, base);
			break;
		case TYFLOAT:
			m_values.d = (float)std::stof(str);
			break;
		case TYDOUBLE:
			m_values.d = (double)std::stod(str);
			break;
		default:
			throw fatal_error("invalid type to create Value");
	}
}
