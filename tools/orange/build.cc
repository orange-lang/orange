/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/build.h>
#include <orange/runner.h>

void doBuildCommand(cOptionsState build, bool doDebug) {
	// If the user didn't enter anything, then we're going to build a project.
	if (build.unparsed().size() == 0) {
		BuildResult res; 

		// Try to find the project directory and build it. 
		try {
			res = buildProject(findProjectDirectory(), doDebug);
		} catch (std::runtime_error& e) {
			// we're probably not in a project. what happened?
			std::cerr << e.what() << std::endl;
			exit(1);
		}

		// show list of errors.
		if (res.passed() == false) {
			for (auto msg : res.errors()) {
				std::cout << "error: " << msg.what() << std::endl;
			}
		}

		return;
	}

	// for now, don't allow the user to build more than one file at once.
	if (build.unparsed().size() > 1) {
		std::cerr << "fatal: building more than one file is not yet supported.\n";
		return;
	} 

	// Run the file and see what happened.
	BuildResult res = buildFile(build.unparsed().at(0), doDebug);

	if (res.passed() == false) {
		for (auto msg : res.errors()) {
			if (msg.hasLineInfo()) {
				std::cout << msg.string() << std::endl;			
			} else {
				std::cout << "error: " << msg.what() << std::endl;			
			}
		}
	}
}

BuildResult buildFile(std::string filename, bool doDebug) {
	Runner *runner = new Runner(filename);
	runner->setDebug(doDebug);
	BuildResult res = runner->build();
	delete runner;
	return res; 
}

BuildResult buildProject(path projectPath, bool doDebug) {
	CompilerMessage msg(NO_COMPILE, "project was not built.", projectPath.string(), -1, -1, -1, -1);
	return BuildResult(projectPath.string(), false, msg);
}
