/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

template <typename T>
std::vector<T> copyVector(std::vector<T>&& orig)
{
	std::vector<T> ret;
	
	for (auto element : orig)
	{
		ret.push_back(element->copy()->template as<T>());
	}
	
	return ret;
}

