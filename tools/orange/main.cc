/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/archives/json.hpp>
#include <helper/args.h>
#include <helper/link.h>
#include <orange/file.h>

void doRunCommand(cOptionsState run);

int main(int argc, char** argv) {
	cOptions options("Orange WIP"); 

	/*
	 * Set up our "run" state to run files.
	 */
	cOptionsState run("run", "Runs a single file or a project.", "run [filename]", "The run command will\
 either run a file or a project directly.\nEntering run without a filename will run a project, if it exists.\
  \nIf you are not in a project, an error will be displayed.\nRunning a file does not require you to be in an Orange project.");
	options.mainState.addState(&run); 

	// Parse our options
	options.parse(argc, argv);

	if (run.isActive()) {
		doRunCommand(run);
	}


	return 0;
}

void doRunCommand(cOptionsState run) {
	// If the user didn't enter anything, then we're going to run a project.
	if (run.unparsed().size() == 0) {
		std::cerr << "fatal: running a project is not yet supported.\n";
		return;
	}

	if (run.unparsed().size() > 1) {
		std::cerr << "fatal: running more than one file is not yet supported.\n";
		return;
	} 

	// try to find our file.
	std::string fileName = run.unparsed()[0];
	FILE *file = fopen(fileName.c_str(), "r");
	if (file == nullptr) {
		std::cerr << "fatal: file " << fileName << " not found.\n";
		return; 
	}

	// TODO: parse it.

	fclose(file);
}
