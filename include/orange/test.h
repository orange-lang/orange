/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 
#ifndef __ORANGE_TEST_H__
#define __ORANGE_TEST_H__

#include <orange/run.h>

#include <helper/args.h>
#include <helper/link.h>
#include "file.h"
#include "error.h"

/**
 * Run tests on a certain path. This will run the test for each file in the directory, 
 * and recurse to children directories. If the directory contains an ORANGE_SETTINGS 
 * file, it will run it as a project.
 */
std::vector<RunResult*> runTest(path p);

/**
 * Gets the total test time in seconds.
 *
 * @return The total test time, in seconds.
 */
float totalTestTime(std::vector<RunResult*> results);

/**
 * Gets the average test time in seconds.
 *
 * @return The average time between tests, in seconds.
 */
float avgTestTime(std::vector<RunResult*> results);

/**
 * Gets the number of passed tests.
 *
 * @return The number of passed tests.
 */
int numPassedTests(std::vector<RunResult*> results);

/**
 * Gets the number of failed tests.
 *
 * @return The number of failed tests.
 */
int numFailedTests(std::vector<RunResult*> results);

/**
 * Gets a string containing information about the longest 
 * test.
 *
 * @return A string with information about the longest test.
 */
std::string getLongestTest(std::vector<RunResult*> results);

/**
 * Prints out stats from the test run, including which 
 * tests have failed. 
 */
void showTestResults(std::vector<RunResult*> results);

/**
 * Invoked from the command line parser, this will test a file or project as 
 * invoked. 
 *
 * @param test The test  state from the command line parser.
 */ 
void doTestCommand(cOptionsState test);

#endif