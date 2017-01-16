/*
** Copyright 2014-2017 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

/**
 * Defines a struct of settings to use when searching for a named node.
 */
struct SearchSettings {
	/// Whether or not to force type matching even if only one
	/// node with a name is found.
	bool forceTypeMatch;
	
	/// Whether or not to create generics on nodes found.
	bool createGeneric;
	
	/// Whether to search up the whole tree or just the current block.
	bool searchWholeTree;
	
	/// Whether or not to include a limit to stop searching.
	bool includeLimit;
	
	SearchSettings()
	{
		forceTypeMatch = false;
		createGeneric = true;
		searchWholeTree = true;
		includeLimit = true;
	}
};