/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "ObjectBase.h"

enum ProtectionLevel
{
	PROTECTION_DEFAULT,
	PROTECTION_PRIVATE,
	PROTECTION_PROTECTED,
	PROTECTION_PUBLIC
};

class ASTNode;

/**
 * Protectable defines a node that can have a protection level assigned 
 * to it.
 */
class Protectable : virtual public ObjectBase
{
protected:
	ProtectionLevel m_level = ProtectionLevel::PROTECTION_DEFAULT;
public:
	void setProtectionLevel(ProtectionLevel& level);
	
	const ProtectionLevel getProtectionLevel() const;
	
	/// Returns true if this Protectable instance is usable from
	/// a context, false otherwise.
	virtual bool usableFrom(const ASTNode* from) const = 0;
	
	virtual ProtectionLevel defaultProtectionLevel() const = 0;
};