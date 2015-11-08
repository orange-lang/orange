/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <vector>
#include <cstdlib>
#include <strings.h>

#include <cmd/OptionsState.h>
#include <cmd/ProgramOptions.h>
#include <cmd/StateFlag.h>
#include <test/TestLib.h>
#include <test/Comparisons.h>
#include <util/string.h>

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

	StateFlag* flag_short = new StateFlag("f", false);
	StateFlag* flag_long = new StateFlag("flag", false);
	StateFlag* flag_alias = new StateFlag("o", "other", false);
	StateFlag* flag_v_short = new StateFlag("v", true);
	StateFlag* flag_v_long = new StateFlag("value", true);
	StateFlag* flag_v_alias = new StateFlag("s", "shared", true);
private:
	void setup()
	{
		options->addState(state_a);
		state_a->addState(a_nested);
		options->addState(state_b);

		state_a->addFlag(flag_short);
		state_a->addFlag(flag_long);
		a_nested->addFlag(flag_alias);
		state_b->addFlag(flag_v_short);
		state_b->addFlag(flag_v_long);

		state_a->addFlag(flag_v_alias);
		state_b->addFlag(flag_v_alias);

	}
public:
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
		setup();
	}

	TestEnvironment(std::string cmd)
	{
		setup();

		run(cmd);
	}

	~TestEnvironment()
	{
		delete options;
		delete state_a;
		delete a_nested;
		delete state_b;

		delete flag_short;
		delete flag_long;
		delete flag_alias;
		delete flag_v_short;
		delete flag_v_long;
		delete flag_v_alias;
	}
};

START_TEST_MODULE();

/*
 * Basic tests
 */
ADD_TEST(TestEmptyInput, "Test the parser with no input.");
int TestEmptyInput()
{
	TestEnvironment basicEnvironment("");
	return pass();
}

/*
 * Test OptionsState
 */
ADD_TEST(TestOptionsStateNameEmpty, "OptionsState's name must not be empty");
int TestOptionsStateNameEmpty()
{
	EXPECT_EXCEPTION(OptionsState(""));
}

/*
 * Test StateFlag
 */
ADD_TEST(TestStateFlagNameEmpty, "StateFlag must not be empty.");
int TestStateFlagNameEmpty()
{
	EXPECT_EXCEPTION(StateFlag("", false));
}

ADD_TEST(TestStateFlagNameEquals, "StateFlag must not contain an equal sign.");
int TestStateFlagNameEquals()
{
	EXPECT_EXCEPTION(StateFlag("flag=", false));
}

/*
 * Test states
 */
ADD_TEST(TestMainState, "Test main state.");
int TestMainState()
{
	TestEnvironment env("");
	return cmpEq(env.options->getCurrentState(), env.options->getMainState());
}

ADD_TEST(TestStateA, "Test state a.");
int TestStateA()
{
	TestEnvironment env("a");
	return cmpEq(env.options->getCurrentState(), env.state_a);
}

ADD_TEST(TestStateB, "Test state b.");
int TestStateB()
{
	TestEnvironment env("state_b");
	return cmpEq(env.options->getCurrentState(), env.state_b);
}

ADD_TEST(TestNestedStates, "Test nested states.");
int TestNestedStates()
{
	TestEnvironment env("a a_nested");
	return cmpEq(env.options->getCurrentState(), env.a_nested);
}

ADD_TEST(TestStateAWithArgument, "Test state a with arguments.");
int TestStateAWithArgument()
{
	TestEnvironment env("a foobar");
	return cmpEq(env.options->getCurrentState(), env.state_a);
}

ADD_TEST(TestNestedStatesWithArgument, "Test nested states with args.");
int TestNestedStatesWithArgument()
{
	TestEnvironment env("a a_nested foobar");
	return cmpEq(env.options->getCurrentState(), env.a_nested);
}

/*
 * Test arguments
 */
ADD_TEST(TestTransitionAfterArg, "Test argument followed by transition");
int TestTransitionAfterArg()
{
	TestEnvironment env("a foobar a_nested");
	return cmpEq(env.options->getCurrentState(), env.a_nested);
}

ADD_TEST(TestArgStateA, "Test argument on state A");
int TestArgStateA()
{
	TestEnvironment env("a foobar");
	return cmpEq(env.state_a->args[0], "foobar");
}

ADD_TEST(TestArgsStateA, "Test arguments on state A.");
int TestArgsStateA()
{
	TestEnvironment env("a foobar baz");
	ASSERT_EQ(env.state_a->args[0], "foobar");
	ASSERT_EQ(env.state_a->args[1], "baz");
	return pass();
}

ADD_TEST(TestNestedArgs, "Test arguments on nested state.");
int TestNestedArgs()
{
	TestEnvironment env("a a_nested foobar");
	ASSERT_EQ(env.a_nested->args.size(), 1);
	return cmpEq(env.a_nested->args[0], "foobar");
}

ADD_TEST(TestArgumentWithTransition, "Test argument and transition");
int TestArgumentWithTransition()
{
    TestEnvironment env("a foobar a_nested");
    ASSERT_EQ(env.a_nested->args.size(), 1);
    return env.a_nested->args[0] != "foobar";
}

/*
 * Test flags
 */
ADD_TEST(TestShortHelpFlag, "Test the short help flag.");
int TestShortHelpFlag()
{
	TestEnvironment basicEnvironment("-h");
	return pass();
}

ADD_TEST(TestBothHelpFlags, "Test both help flags.");
int TestBothHelpFlags()
{
	TestEnvironment basicEnvironment("--help -h");
	return pass();
}

ADD_TEST(TestNonExistentFlag, "Test non-existent help flag.");
int TestNonExistentFlag()
{
	EXPECT_EXCEPTION(TestEnvironment("--thisFlagDoesNotExist"));
}

ADD_TEST(TestDefaultFlag, "Test flag defaults");
int TestDefaultFlag()
{
	TestEnvironment env("");
	ASSERT_EQ(env.flag_short->getUsed(), false);
	ASSERT_EQ(env.flag_long->getUsed(), false);
	ASSERT_EQ(env.flag_alias->getUsed(), false);
	ASSERT_EQ(env.flag_v_short->getUsed(), false);
	ASSERT_EQ(env.flag_v_long->getUsed(), false);
	ASSERT_EQ(env.flag_v_alias->getUsed(), false);
	return pass();
}

ADD_TEST(TestShortFlag, "Test short flag.");
int TestShortFlag()
{
	TestEnvironment env("a -f");
	return cmpEq(env.flag_short->getUsed(), true);
}

ADD_TEST(TestLongFlag, "Test long flag.");
int TestLongFlag()
{
	TestEnvironment env("a --flag");
	return cmpEq(env.flag_long->getUsed(), true);
}

ADD_TEST(TestFlagAliasShort, "Test aliased flag's short.");
int TestFlagAliasShort()
{
	TestEnvironment env("a a_nested -o");
	return cmpEq(env.flag_alias->getUsed(), true);
}

ADD_TEST(TestFlagAliasLong, "Test aliased flag's long.");
int TestFlagAliasLong()
{
	TestEnvironment env("a a_nested --other");
	return cmpEq(env.flag_alias->getUsed(), true);
}

ADD_TEST(TestShortFlagValSeparate, "Test short flag value separate.");
int TestShortFlagValSeparate()
{
	TestEnvironment env("state_b -v hello");
	ASSERT_EQ(env.flag_v_short->getUsed(), true);
	ASSERT_EQ(env.flag_v_short->getValue(), "hello");
	return pass();
}

ADD_TEST(TestShortFlagValCombined, "Test short flag value combined.");
int TestShortFlagValCombined()
{
	TestEnvironment env("state_b -vworld");
	ASSERT_EQ(env.flag_v_short->getUsed(), true);
	ASSERT_EQ(env.flag_v_short->getValue(), "world");
	return pass();
}

ADD_TEST(TestLongFlagValSeparate, "Test long flag value separate.");
int TestLongFlagValSeparate()
{
	TestEnvironment env("state_b --value fizz");
	ASSERT_EQ(env.flag_v_long->getUsed(), true);
	ASSERT_EQ(env.flag_v_long->getValue(), "fizz");
	return pass();
}

ADD_TEST(TestLongFlagValCombined, "Test long flag value combined.");
int TestLongFlagValCombined()
{
	TestEnvironment env("state_b --value=buzz");
	ASSERT_EQ(env.flag_v_long->getUsed(), true);
	ASSERT_EQ(env.flag_v_long->getValue(), "buzz");
	return pass();
}

ADD_TEST(TestShortAliasFlagValSeparateA, "Test A's aliased flag's short value separate.");
int TestShortAliasFlagValSeparateA()
{
	TestEnvironment env("a -s orange");
	ASSERT_EQ(env.flag_v_alias->getUsed(), true);
	ASSERT_EQ(env.flag_v_alias->getValue(), "orange");
	return pass();
}

ADD_TEST(TestShortAliasFlagValCombinedA, "Test A's aliased flag's short value combined.");
int TestShortAliasFlagValCombinedA()
{
	TestEnvironment env("a -sorange");
	ASSERT_EQ(env.flag_v_alias->getUsed(), true);
	ASSERT_EQ(env.flag_v_alias->getValue(), "orange");
	return pass();
}

ADD_TEST(TestLongAliasFlagValSeparateA, "Test A's aliased flag's long value separate.");
int TestLongAliasFlagValSeparateA()
{
	TestEnvironment env("a --shared orange");
	ASSERT_EQ(env.flag_v_alias->getUsed(), true);
	ASSERT_EQ(env.flag_v_alias->getValue(), "orange");
	return pass();
}


ADD_TEST(TestLongAliasFlagValCombinedA, "Test A's aliased flag's long value combined.");
int TestLongAliasFlagValCombinedA()
{
	TestEnvironment env("a --shared=orange");
	ASSERT_EQ(env.flag_v_alias->getUsed(), true);
	ASSERT_EQ(env.flag_v_alias->getValue(), "orange");
	return pass();
}

ADD_TEST(TestShortAliasFlagValSeparateB, "Test B's aliased flag's short value separate.");
int TestShortAliasFlagValSeparateB()
{
	TestEnvironment env("state_b -s orange");
	ASSERT_EQ(env.flag_v_alias->getUsed(), true);
	ASSERT_EQ(env.flag_v_alias->getValue(), "orange");
	return pass();
}

ADD_TEST(TestShortAliasFlagValCombinedB, "Test B's aliased flag's short value combined.");
int TestShortAliasFlagValCombinedB()
{
	TestEnvironment env("state_b -sorange");
	ASSERT_EQ(env.flag_v_alias->getUsed(), true);
	ASSERT_EQ(env.flag_v_alias->getValue(), "orange");
	return pass();
}

ADD_TEST(TestLongAliasFlagValSeparateB, "Test B's aliased flag's long value separate.");
int TestLongAliasFlagValSeparateB()
{
	TestEnvironment env("state_b --shared orange");
	ASSERT_EQ(env.flag_v_alias->getUsed(), true);
	ASSERT_EQ(env.flag_v_alias->getValue(), "orange");
	return pass();
}


ADD_TEST(TestLongAliasFlagValCombinedB, "Test B's aliased flag's long value combined.");
int TestLongAliasFlagValCombinedB()
{
	TestEnvironment env("state_b --shared=orange");
	ASSERT_EQ(env.flag_v_alias->getUsed(), true);
	ASSERT_EQ(env.flag_v_alias->getValue(), "orange");
	return pass();
}

RUN_TESTS();
