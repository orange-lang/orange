/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/commands/RunCommand.h>

RunCommand::RunCommand() : CodeExecutor("run", 
	"Runs a single file or a project",
	"run [filename]", 
	"The run command will \
either run a file or a project directly. Entering run without a filename will run a project, if it exists. \
If you are not in a project, an error will be displayed. Running a file does not require you to be in an Orange project.") 
{

}

void RunCommand::run() {
	CodeExecutor::run();

	runCompiled();
	handleErrors();
}