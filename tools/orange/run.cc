/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 
#include <orange/run.h>

bool RunResult::passed() const { return m_pass; }

std::vector<CompilerMessage> RunResult::messages() const { return m_messages; }

std::vector<CompilerMessage> RunResult::errors() const { 
	std::vector<CompilerMessage> retList;

	// add everything to retList that *is not* a warning,
	// since technically that would be an error.
	for (auto msg : m_messages) {
		if (msg.type() != WARNING) {
			retList.push_back(msg);
		}
	}

	return retList; 
}

std::vector<CompilerMessage> RunResult::warnings() const {
	std::vector<CompilerMessage> retList;

	// add everything to retlist that *is* a warning.
	for (auto msg : m_messages) {
		if (msg.type() == WARNING) {
			retList.push_back(msg);
		}
	}

	return retList; 
}

void RunResult::start() {
	// Get the current time in microsecs from the clock.
  startTime = boost::posix_time::microsec_clock::local_time();
}

void RunResult::finish(bool pass, int code, CompilerMessage message) {
	// First, calculate the run time.
	boost::posix_time::ptime endTime = boost::posix_time::microsec_clock::local_time();
  boost::posix_time::time_duration diff = endTime - startTime;
  m_runtime = diff.total_milliseconds();

	m_pass = pass;
	m_messages.push_back(message);	
	m_retcode = code;	
}

void RunResult::finish(bool pass, int code, std::vector<CompilerMessage> messages) {
	// First, calculate the run time.
	boost::posix_time::ptime endTime = boost::posix_time::microsec_clock::local_time();
  boost::posix_time::time_duration diff = endTime - startTime;
  m_runtime = diff.total_milliseconds();

	m_pass = pass;
	m_messages = messages;
	m_retcode = code;
}

unsigned long long RunResult::runtime() const { return m_runtime; }
int RunResult::returnCode() const { return m_retcode; }
std::string RunResult::filename() const { return m_filename; }



RunResult::RunResult(std::string filename, bool pass, int code, CompilerMessage message) {
	m_filename = filename;
	start();
	finish(pass, code, message);
}

RunResult::RunResult(std::string filename, bool pass, int code, std::vector<CompilerMessage> messages) {
	m_filename = filename;
	start();
	finish(pass, code, messages);
}

RunResult runFile(std::string filename) {
	// try to find our file.
	FILE *file = fopen(filename.c_str(), "r");
	if (file == nullptr) {
		CompilerMessage msg(NO_FILE, "file " + filename + " not found.", filename, -1, -1, -1, -1);
		return RunResult(filename, false, 1, msg);
	}

	// TODO: parse it.

	fclose(file);

	// for now, temporarily return that we didn't run it.
	CompilerMessage msg(NO_COMPILE, "file was not run.", filename, -1, -1, -1, -1);
	return RunResult(filename, false, 1, msg);
}

RunResult runProject(path projectPath) {
	// for now, temporarily return that we didn't run it.
	CompilerMessage msg(NO_COMPILE, "project was not run.", projectPath.string(), -1, -1, -1, -1);
	return RunResult(projectPath.string(), false, 1, msg);
}

void doRunCommand(cOptionsState run) {
	// If the user didn't enter anything, then we're going to run a project.
	if (run.unparsed().size() == 0) {
		RunResult res; 

		// Try to find the project directory and run it. 
		try {
			res = runProject(findProjectDirectory());
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

	// for now, don't allow the user to run more than one file at once.
	if (run.unparsed().size() > 1) {
		std::cerr << "fatal: running more than one file is not yet supported.\n";
		return;
	} 

	// Run the file and see what happened.
	RunResult res = runFile(run.unparsed().at(0));

	if (res.passed() == false) {
		for (auto msg : res.errors()) {
			std::cout << "error: " << msg.what() << std::endl;
		}
	}
}