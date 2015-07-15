/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __RUN_SETTINGS_H__
#define __RUN_SETTINGS_H__

enum DebugLevel {
	NO_DEBUG 				= 0x0, 
	DEBUG_PARENTAGE = 0x1,
	DEBUG_AST				= 0x2,
	DEBUG_MODULE 		= 0x4,
	DUMP_MODULE 		= 0x8     
};

struct RunSettings {
	/**
	 * Whether or not you are in debug mode 
	 */
	int debug = NO_DEBUG; 

	/** 
	 * Returns true if a debug level is set 
	 */
	bool debugLevel(DebugLevel level) {
		return (debug & level) != NO_DEBUG; 
	}

	/**
	 * Output assembly 
	 */
	bool assembly = false; 

	bool skip_linking = false;
};

#endif 