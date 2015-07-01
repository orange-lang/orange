/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/commands/BuildCommand.h>
#include <orange/runner.h>

BuildCommand::BuildCommand() : CodeExecutor("build", 
	"Compiles a single file or project", 
	"build [filename]", 
	"The build command will \
either compile a file or a project directly. Entering compile without a filename will compile a project, if it exists. \
If you are not in a project, an error will be displayed. Building a file does not require you to be in an Orange project.")
{

}

void BuildCommand::run() {
	CodeExecutor::run();

	auto outputOption = getOption("o");
	if (outputOption->isSet()) {
  	m_runner->setOutputName(outputOption->argValue());
	}

	buildCompiled();
	handleErrors();
}