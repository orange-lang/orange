/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include <exception>

class Module;

/**
 * file_error is an exception class for file errors
 */
class file_error : public std::exception
{
private:
	Module* m_module = nullptr;
	std::string m_error; 
public:
	virtual const char* what() const noexcept override;
	
	file_error(Module* mod);
};