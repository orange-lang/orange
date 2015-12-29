/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <stdexcept>

#include <grove/Module.h>

#include <grove/Parameter.h>
#include <grove/Value.h>
#include <grove/Statement.h>
#include <grove/OString.h>
#include <grove/Protectable.h>
#include "parser.hh"

extern struct YYLTYPE yylloc;

void yyerror(Module* mod, const char* str)
{
	std::stringstream ss;
	ss << mod->getFile() << ":" << yylloc.last_line << ":" <<
 		yylloc.last_column << ": " << str;
	
	throw std::runtime_error(ss.str());
}