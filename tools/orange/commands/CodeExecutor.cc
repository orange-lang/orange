/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/commands/CodeExecutor.h>
#include <orange/runner.h>

void CodeExecutor::handleErrors() {
	if (m_result->passed() == true) return;

	for (auto msg : m_result->errors()) {
		if (msg.hasLineInfo()) {
			std::cout << msg.string() << std::endl;			
		} else {
			std::cout << "error: " << msg.what() << std::endl;			
		}
	}
}

void CodeExecutor::compileProject(std::string path) {
	CompilerMessage msg(NO_COMPILE, "project was not run.", path, -1, -1, -1, -1);
	m_result = new RunResult(path, false, 1, msg);
}

void CodeExecutor::reset() {
	if (m_runner != nullptr) {
		delete m_runner; 
	}
	
	m_runner = new Runner();	
}

void CodeExecutor::compileFile(std::string file) {
	m_runner->setTarget(file);

	auto debugOption = getOption("debug");
	if (debugOption != nullptr) {
  	m_runner->setDebug(debugOption->isSet());
	}

	m_runner->compile();
	m_result = m_runner->result();
}

void CodeExecutor::runCompiled() {
	if (m_result->finished()) return;

	m_runner->run();
	m_result = m_runner->result();
	m_ret_code = ((RunResult *)m_runner)->returnCode();
}

void CodeExecutor::buildCompiled() {
	if (m_result->finished()) return;

	m_runner->build();
	m_result = m_runner->result();
}


void CodeExecutor::run() {
	if (unparsed().size() > 1) {
		std::cerr << "fatal: compiling more than one file at once is not yet supported.\n";
		exit(1);
	} 

	if (unparsed().size() == 0) {
		// No arguments means we're running a project 

		try {
			auto dir = findProjectDirectory(); 
			compileProject(dir.string());
		} catch (std::runtime_error& e) {
			std::cerr << e.what() << std::endl;
			exit(1);
		}
	} else {
		// If there's only one argument, we're just building a single file  
		compileFile(unparsed().at(0));
	}
}

CodeExecutor::CodeExecutor(std::string name, std::string description, std::string usage, std::string info) : 
	cOptionsState(name, description, usage, info) 
{
	reset();
}


CodeExecutor::CodeExecutor() { 
	reset();
}

CodeExecutor::~CodeExecutor() {
	if (m_result) delete m_result;
	if (m_runner) delete m_runner; 
}
