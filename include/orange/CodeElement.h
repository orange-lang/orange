/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __CODE_ELEMENT_H__
#define __CODE_ELEMENT_H__

class CodeLocation {
public:
	int row_begin = 0, row_end = 0;
	int col_begin = 0, col_end = 0;

	CodeLocation() {};
	CodeLocation(int row_begin, int row_end, int col_begin, int col_end) : row_begin(row_begin), row_end(row_end), 
		col_begin(col_begin-1), col_end(col_end-1) { }
};

/**
 * Code element is the root class that contains information about code location.
 */
class CodeElement {
protected:
	/**
	 * Indicates where the code is located in a file.
	 */
	CodeLocation m_location;
public:
	/**
	 * Gets the current code location
	 *
	 * @return The location where this fragment of code resides.
	 */
	CodeLocation location() const { return m_location; }

	/**
	 * Sets the code location
	 *
	 * @param location The new location to use.
	 */
	void setLocation(CodeLocation location) { m_location = location; }  
};


#endif 