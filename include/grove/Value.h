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

namespace Orange { class Type; }

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
	
	Value();
	
	bool m_char_const = false;
public:
	virtual void resolve() override;
	virtual void build() override;
	
	virtual ASTNode* copy() const override;
	
	virtual std::vector<ObjectBase**> getMemberNodes() override;
	
	virtual std::vector<std::vector<ObjectBase *>*> getMemberLists() override;
	
	virtual bool isConstant() const override;
	
	int64_t getInt() const;
	uint64_t getUInt() const;
	double getDouble() const;
	
	/// Converts to a new type.
	void convert(const Orange::Type* newty);
	
	/// Gets a new value from this value with the added
	/// delta as the value.
	Value* addDelta(int64_t d) const;
	
	/// Negates this value (multiplies it by -1).
	/// Throws an error if this is unsigned.
	void negate();
	
	Value(char c);
	
	/**
	 * Constructs a new Value.
	 * @param str The string to convert to a value.
	 * @param t The type of the value.
	 */
	Value(std::string str, const Orange::Type* t, int base = 10);
	Value(const Value& other);
};
