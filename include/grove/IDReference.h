/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include "NodeReference.h"

/**
 * IDReference is a class that can refer to any ID by name.
 */
class IDReference : public NodeReference {
private:
	OString m_name;
public:
	/// Gets the name that this node is referring to.
	OString getName() const;
	
	virtual void findDependencies() override;
	
	virtual ASTNode* copy() const override;
	
	IDReference(OString name);
};
