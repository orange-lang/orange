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
	startTime = llvm::sys::TimeValue::now();
}

void BuildResult::finish(bool pass, CompilerMessage message) {
	// First, calculate the run time.
	endTime = llvm::sys::TimeValue::now();
  auto diff = endTime - startTime;
  m_runtime = diff.milliseconds();

	m_pass = pass;
	m_messages.push_back(message);	
}

void BuildResult::finish(bool pass, std::vector<CompilerMessage> messages) {
	// First, calculate the run time.
	endTime = llvm::sys::TimeValue::now();
  auto diff = endTime - startTime;
  m_runtime = diff.milliseconds();

	m_pass = pass;
	m_messages = messages;
	m_finished = true;
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
	endTime = llvm::sys::TimeValue::now();
  auto diff = endTime - startTime;
  m_runtime = diff.milliseconds();

	m_pass = pass;
	m_messages.push_back(message);	
	m_retcode = code;
	m_finished = true;
}

void RunResult::finish(bool pass, int code, std::vector<CompilerMessage> messages) {
	// First, calculate the run time.
	endTime = llvm::sys::TimeValue::now();
  auto diff = endTime - startTime;
  m_runtime = diff.milliseconds();


	m_pass = pass;
	m_messages = messages;
	m_retcode = code;
}


int RunResult::returnCode() const { return m_retcode; }

RunResult::RunResult(BuildResult result) {
	m_pass = result.m_pass;
	m_messages = result.messages();
	m_filename = result.m_filename;
	m_runtime = result.m_runtime;
	startTime = result.startTime;
	endTime = result.endTime;
	m_finished = result.m_finished;
}

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
