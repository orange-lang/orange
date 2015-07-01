/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __CODE_EXECUTOR_H__ 
#define __CODE_EXECUTOR_H__ 

#include <helper/args.h> 
#include "../run.h"


class Runner; 

class CodeExecutor : public cOptionsState {
protected: 
	BuildResult* m_result = nullptr; 
	Runner* m_runner = nullptr;

	int m_ret_code = 0;

	void reset();
public:
	BuildResult* result() const { return m_result; }
	int retCode() const { return m_ret_code; }

	void compileProject(std::string path); 
	void compileFile(std::string file); 

	void runCompiled();

	void buildCompiled();

	void handleErrors();

	virtual void run();

	CodeExecutor(std::string name, std::string description, std::string usage = "", std::string info = "");
	CodeExecutor();
	virtual ~CodeExecutor();
};

#endif 