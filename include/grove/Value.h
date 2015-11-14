/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include <cstdint>
#include "Expression.h"

class Type;

/**
 * Value represents a hard-coded numeric value.
 */
class Value : public Expression {
private:
	union {
		int64_t  i;
		uint64_t u;
		
		double   d;
	} m_values;
public:
	virtual void build() override;
	
	/** 
	 * Constructs a new Value.
	 * @param str The string to convert to a value.
	 * @param t The type of the value.
	 */
	Value(std::string str, Type* t);
};