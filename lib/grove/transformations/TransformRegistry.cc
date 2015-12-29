/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/transformations/TransformRegistry.h>

TransformRegistry* TransformRegistry::m_shared = new TransformRegistry();

TransformRegistry::TransformRegistry()
{
	// Do nothing.
}

TransformRegistry* TransformRegistry::get()
{
	return m_shared;
}

std::vector<const TransformBase*> TransformRegistry::getTransforms() const
{
	return m_registered;
}

void TransformRegistry::registerTransform(const TransformBase *transform)
{
	m_registered.push_back(transform);
}