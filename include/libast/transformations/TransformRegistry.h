/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include <vector>

class TransformBase;

class TransformRegistry
{
private:
	std::vector<const TransformBase *> m_registered;
	
	TransformRegistry();
	
	static TransformRegistry* m_shared;
public:
	static TransformRegistry* get();
	
	std::vector<const TransformBase *> getTransforms() const;
	
	void registerTransform(const TransformBase* transform);
};