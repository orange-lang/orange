/*
 ** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
 ** directory of this distribution.
 **
 ** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
 ** may not be copied, modified, or distributed except according to those terms.
 */

#pragma once

#include <exception>
#include <string>

class CodeBase;

/**
 * code_error represents a user error in code.
 */
class code_error : public std::exception
{
protected:
	std::string m_error;
	
	CodeBase* m_element = nullptr;
	
	/// Gets the context of an element from its file.
	std::string getContext(CodeBase* element);
	
	/// Gets the string for a CodeBase where
	/// it is in the format of fileName:firstLine:firstCol.
	std::string fileWithPosition(CodeBase* element);
public:
	virtual const char* what() const noexcept override;
	
	code_error(CodeBase* element);
};
