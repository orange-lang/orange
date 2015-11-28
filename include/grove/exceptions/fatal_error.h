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

/**
 * fatal_error is an exception class for fatal errors that are usually 
 * compiler bugs.
 */
class fatal_error : public std::exception
{
private:
	std::string m_error;
public:
	virtual const char* what() const noexcept override;
	
	fatal_error(std::string msg);
};
