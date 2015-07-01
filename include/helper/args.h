/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __HELPER_ARGS_H__
#define __HELPER_ARGS_H__

#include <string> 
#include <vector>
#include <functional>

// gets args from command line,
void getArgs(int argc, char **argv, std::function<void(std::vector<std::string> arg, int loc)> cb);
const char* getParameter(std::vector<std::string> a, int argc, char **argv, int loc);

class cOptionsState;
class cOptions;

class cCommandOption {
friend cOptions;
friend cOptionsState;
private:
	bool m_set = false;
	std::vector<std::string> names; 
	std::string description;
	std::string arg_value;
	bool m_hasArg;
public:
	bool isSet() const;
	bool hasArg() const { return m_hasArg; }
	std::string argValue() const { return arg_value; }

	cCommandOption(std::vector<std::string> names, std::string description, bool arg);
};

class cOptionsState {
friend cOptions;
private:
	bool mActive = false;
	std::string name = "";
	std::string description;
	std::vector<cCommandOption*> options;
	std::vector<cOptionsState*> states; 
	std::vector<std::string> m_unparsed;
	std::string customUsage = "";
	std::string customInfo = "";

protected:
	cOptionsState() { }
public:
	bool isActive() const { return mActive; }

	cCommandOption* getOption(std::string option);

	virtual void run() { } 

	void add(cCommandOption* option);
	void addState(cOptionsState* state);

	std::vector<std::string> unparsed() const;

	cOptionsState(std::string name, std::string description, std::string usage = "", std::string info = "");
};

class cOptions {
private:
	std::string name;
	cOptionsState *curState;

	void printHelp();
public:
	cOptionsState mainState;

	cOptionsState* currentState() const { return curState; } 

	void parse(int argc, char **argv);

	cOptions(std::string name) : name(name) {}
};

#endif 