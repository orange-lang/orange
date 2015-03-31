/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/file.h>
#include <orange/config.h>

path findProjectDirectory() {
	path p = current_path(); 

	// While our current directory exists, try to find ORANGE_SETTINGS
	while (exists(p)) {
		for (auto& entry : make_iterator_range(directory_iterator(p), directory_iterator())) {
			// if we found it, return it.
			if (entry.path().filename().string() == ORANGE_SETTINGS) {
				return p; 
			}
		}

		// it wasn't in this directory, so move up to the parent.
		// if p is currently the root directory, p.parent_path does not exist, which will
		// end our loop.
		p = p.parent_path(); 
	}

	// we didn't find the path, so throw our exception here.
	throw std::runtime_error("fatal: not in an orange project!");
}