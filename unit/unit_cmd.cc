/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <vector>
#include <cstdlib>

#include <cmd/OptionsState.h>
#include <cmd/ProgramOptions.h>
#include <cmd/StateFlag.h>
#include <test/TestLib.h>

void unreachable(std::string error)
{
	fprintf(stderr, "%s\n", error.c_str());
	exit(1);
}

template <typename T>
void assertEq(T a, T b, std::string err)
{
	if (a != b)
	{
		unreachable(err);
	}
}

const char* stringToCharArray(std::string str)
{
	char* arr = new char[str.length()];
	strncpy(arr, str.c_str(), str.length());
	return arr;
}

std::vector<const char*> strToArgs(std::string str)
{
	std::vector<const char*> arguments;
	arguments.push_back(stringToCharArray("program-name"));

	// The character to split on.
	char split_char = ' ';

	std::string curArgument = "";
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == split_char && curArgument != "")
		{
			arguments.push_back(stringToCharArray(curArgument));

			// Reset variables
			split_char = ' ';
			curArgument = "";
			continue;
		}
		else if (str[i] == ' ' && curArgument == "")
		{
			continue;
		}

		// If we found a ", don't stop looking for the argument until the
		// other " is found.
		if (str[i] == '\"')
		{
			split_char = '\"';
			continue;
		}

		curArgument += str[i];
	}

	if (curArgument != "")
	{
		arguments.push_back(stringToCharArray(curArgument));
	}

	return arguments;
}

class TestState : public OptionsState
{
public:
	std::vector<std::string> args;
	bool hit = false;

	TestState(std::string n) : OptionsState(n)
	{

	}

	virtual void run(std::vector<std::string> args)
	{
		this->args = args;
		hit = true;
	}

	virtual ~TestState()
	{

	}
};

class TestEnvironment
{
public:
	ProgramOptions* options = new ProgramOptions("test-cmd");
	TestState* state_a = new TestState("a");
	TestState* a_nested = new TestState("a_nested");
	TestState* state_b = new TestState("state_b");

	void run(std::string cmd)
	{
		auto args = strToArgs(cmd);
    	options->parse(args.size(), (char **)&args[0]);

    	for (auto arg : args)
    	{
    		delete arg;
    	}
	}

	TestEnvironment()
	{
		options->addState(state_a);
		state_a->addState(a_nested);
		options->addState(state_b);
	}

	TestEnvironment(std::string cmd)
	{
		options->addState(state_a);
		state_a->addState(a_nested);
		options->addState(state_b);

		run(cmd);
	}


	~TestEnvironment()
	{
		delete options;
		delete state_a;
		delete a_nested;
		delete state_b;
	}
};

START_TEST_MODULE();

ADD_TEST(TestEmptyInput, "Test the parser with no input.");
int TestEmptyInput()
{
	TestEnvironment basicEnvironment("");
	return 0;
}

ADD_TEST(TestLongHelpFlag, "Tests the long help flag.");
int TestLongHelpFlag()
{
	TestEnvironment basicEnvironment("--help");
	return 0;
}

ADD_TEST(TestShortHelpFlag, "Test the short help flag.");
int TestShortHelpFlag()
{
	TestEnvironment basicEnvironment("-h");
	return 0;
}

ADD_TEST(TestBothHelpFlags, "Test both help flags.");
int TestBothHelpFlags()
{
	TestEnvironment basicEnvironment("--help -h");
	return 0;
}

ADD_TEST(TestNonExistentFlag, "Test non-existent help flag.");
int TestNonExistentFlag()
{
	TestEnvironment basicEnvironment;

	try
	{
    	basicEnvironment.run("--thisFlagDoesNotExist");
	}
	catch (std::invalid_argument& e)
	{
			return 0;
	}

	return 1;
}

ADD_TEST(TestMainState, "Test main state.");
int TestMainState()
{
	TestEnvironment env("");
	return env.options->getCurrentState() != env.options->getMainState();
}

ADD_TEST(TestStateA, "Test state a.");
int TestStateA()
{
	TestEnvironment env("a");
	return env.options->getCurrentState() != env.state_a;
}

ADD_TEST(TestStateB, "Test state b.");
int TestStateB()
{
	TestEnvironment env("state_b");
	return env.options->getCurrentState() != env.state_b;
}

ADD_TEST(TestNestedStates, "Test nested states.");
int TestNestedStates()
{
	TestEnvironment env("a a_nested");
	return env.options->getCurrentState() != env.a_nested;
}

ADD_TEST(TestStateAWithArgument, "Test state a with arguments.");
int TestStateAWithArgument()
{
	TestEnvironment env("a foobar");
	return env.options->getCurrentState() != env.state_a;
}

ADD_TEST(TestNestedStatesWithArgument, "Test nested states with args.");
int TestNestedStatesWithArgument()
{
	TestEnvironment env("a a_nested foobar");
	return env.options->getCurrentState() != env.a_nested;
}

ADD_TEST(TestTransitionAfterArg, "Test argument followed by transition");
int TestTransitionAfterArg()
{
	TestEnvironment env("a foobar a_nested");
	return env.options->getCurrentState() != env.a_nested;
}

ADD_TEST(TestArgStateA, "Test argument on state A");
int TestArgStateA()
{
	TestEnvironment env("a foobar");
	return env.state_a->args[0] != "foobar";
}

ADD_TEST(TestArgsStateA, "Test arguments on state A.");
int TestArgsStateA()
{
	TestEnvironment env("a foobar baz");
	return env.state_a->args[0] != "foobar" ||
		env.state_a->args[1] != "baz";
}

ADD_TEST(TestNestedArgs, "Test arguments on nested state.");
int TestNestedArgs()
{
	TestEnvironment env("a a_nested foobar");
	return env.a_nested->args[0] != "foobar";
}

ADD_TEST(TestArgumentWithTransition, "Test argument and transition");
int TestArgumentWithTransition()
{
	TestEnvironment env("a foobar a_nested");
	return env.a_nested->args[0] != "foobar";
}

RUN_TESTS();
