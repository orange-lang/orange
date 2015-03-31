/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 
#include <orange/run.h>
#include <orange/runner.h>

bool BuildResult::passed() const { return m_pass; }

std::vector<CompilerMessage> BuildResult::messages() const { return m_messages; }

std::vector<CompilerMessage> BuildResult::errors() const { 
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

std::vector<CompilerMessage> BuildResult::warnings() const {
	std::vector<CompilerMessage> retList;

	// add everything to retlist that *is* a warning.
	for (auto msg : m_messages) {
		if (msg.type() == WARNING) {
			retList.push_back(msg);
		}
	}

	return retList; 
}

void BuildResult::start() {
	// Get the current time in microsecs from the clock.
  startTime = boost::posix_time::microsec_clock::local_time();
}

void BuildResult::finish(bool pass, CompilerMessage message) {
	// First, calculate the run time.
	boost::posix_time::ptime endTime = boost::posix_time::microsec_clock::local_time();
  boost::posix_time::time_duration diff = endTime - startTime;
  m_runtime = diff.total_milliseconds();

	m_pass = pass;
	m_messages.push_back(message);	
}

void BuildResult::finish(bool pass, std::vector<CompilerMessage> messages) {
	// First, calculate the run time.
	boost::posix_time::ptime endTime = boost::posix_time::microsec_clock::local_time();
  boost::posix_time::time_duration diff = endTime - startTime;
  m_runtime = diff.total_milliseconds();

	m_pass = pass;
	m_messages = messages;
}


BuildResult::BuildResult(std::string filename, bool pass, CompilerMessage message) {
	m_filename = filename;
	start();
	finish(pass, message);
}

BuildResult::BuildResult(std::string filename, bool pass, std::vector<CompilerMessage> messages) {
	m_filename = filename;
	start();
	finish(pass, messages);
}

unsigned long long BuildResult::runtime() const { return m_runtime; }
std::string BuildResult::filename() const { return m_filename; }

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


int RunResult::returnCode() const { return m_retcode; }

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
	Runner *runner = new Runner(filename);
	RunResult res = runner->run();
	delete runner;
	return res; 
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
			if (msg.hasLineInfo()) {
				std::cout << msg.string() << std::endl;			
			} else {
				std::cout << "error: " << msg.what() << std::endl;			
			}
		}
	}
}