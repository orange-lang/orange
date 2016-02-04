/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <stdexcept>

#include <libast/Module.h>

#include <libast/Parameter.h>
#include <libast/Value.h>
#include <libast/Statement.h>
#include <libast/OString.h>
#include <libast/Protectable.h>
#include "parser.hh"

extern struct YYLTYPE yylloc;

void yyerror(Module* mod, const char* str)
{
	std::stringstream ss;
	ss << mod->getFile() << ":" << yylloc.last_line << ":" <<
 		yylloc.last_column << ": " << str;
	
	throw std::runtime_error(ss.str());
}