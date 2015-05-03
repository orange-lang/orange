/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_BUILD_H__
#define __ORANGE_BUILD_H__

#include <helper/args.h>
#include <helper/link.h>
#include "file.h"
#include "error.h"
#include "run.h"

/**
 * Invoked from the command line parser, this will build a file or project as 
 * invoked. 
 *
 * @param build The build state from the command line parser.
 */ 
void doBuildCommand(cOptionsState build, bool doDebug);

/**
 * Compile a single file into a binary.
 *
 * @return A RunResult, with a list of errors, if any.
 */
BuildResult buildFile(std::string filename, bool doDebug);

/**
 * Compile a whole project to a single binary.
 *
 * @return A RunResult that will contain if it succeeded with a list of errors, if any.
 */
BuildResult buildProject(path projectPath, bool doDebug);

#endif