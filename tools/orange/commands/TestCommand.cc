/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <sstream>
#include <fcntl.h>
#include <unistd.h>
#include <orange/commands/TestCommand.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Path.h>
#include <orange/config.h>

#ifdef _WIN32 
	const char* NULLFILE = "NUL";
#else 
	const char* NULLFILE = "/dev/null";
#endif 

TestCommand::TestCommand() : CodeExecutor("test", 
	"Tests files and projects in the test/ directory.", 
	"test [folder|filename|project]", 
	"The test command is used to test every file and project inside of the test/ folder. \
It will run recursively, through each subdirectory. If a subdirectory contains a orange.settings.json \
file, it is treated as a sub project. Otherwise, every file inside of the directory will be ran \
as its own individual program.") 
{

}

using namespace llvm::sys;

std::string appendPath(std::string a, std::string b) {
	llvm::SmallString<50> p_s; 
	Twine(a).toVector(p_s);
	path::append(p_s, b);
	return Twine(p_s).str();
}

void TestCommand::runOnPath(std::string p) {
	// If it's a directory _with_ a ORANGE_SETTINGS file, run the project only.
	// We need to know the path that's p + ORANGE_SETTINGS...
	std::string settingsPath = appendPath(p, ORANGE_SETTINGS);

	if (fs::is_directory(p) && fs::exists(Twine(settingsPath))) {
		// Run the project.
		reset();
		compileProject(p); 
		runCompiled();

		RunResult* testRun = (RunResult *)result();

		// Add a . if it passed, F otherwise. After printing a multiple 
		// of MAX_CHARACTERS_PER_LINE notices, print a newline.
		std::cout << (testRun->passed() ? "." : "F") << std::flush;
		if ((++m_added_characters % MAX_CHARACTERS_PER_LINE) == 0) std::cout << std::endl;

		m_results.push_back(testRun);
	} else if (fs::is_directory(p)) {
		// Go through each item in the directory recursively
		std::error_code err; 

		auto end = fs::recursive_directory_iterator();
		for (auto it = fs::recursive_directory_iterator(Twine(p), err); it != end; it.increment(err)) {
			if (fs::is_directory(it->path()) == true) continue;
			if (path::extension(it->path()).str() != ".or") continue; 

			runOnPath(it->path());
		}

	} else {
		// Disable output
		int bak, newFd;
		fflush(stdout);
		bak = dup(STDOUT_FILENO);
		newFd = open(NULLFILE, O_WRONLY);
		dup2(newFd, STDOUT_FILENO);
		close(newFd);

		// run a single file  
		reset();
		compileFile(p); 
		runCompiled();
		RunResult* testRun = (RunResult *)result();

		// Re-enable output		
		fflush(stdout);
		dup2(bak, STDOUT_FILENO);
		close(bak);

		// Add a . if it passed, F otherwise. After printing a multiple 
		// of MAX_CHARACTERS_PER_LINE notices, print a newline.
		std::cout << (testRun->passed() ? "." : "F") << std::flush;
		if ((++m_added_characters % MAX_CHARACTERS_PER_LINE) == 0) std::cout << std::endl;

		m_results.push_back(testRun);
	} 
}

float TestCommand::totalTestTime() {
	unsigned long long totTimeMS = 0;
	for (auto res : m_results) {
		totTimeMS += res->runtime();
	}
	return totTimeMS / 1000.0f;
}

float TestCommand::avgTestTime() {
	// Prevent a divide by zero here.
	if (m_results.size() == 0) return 0;

	unsigned long long totTimeMS = 0;
	for (auto res : m_results) {
		totTimeMS += res->runtime();
	}

	return (totTimeMS / m_results.size()) / 1000.0f;	
}

int TestCommand::numPassedTests() {
	int numPassed = 0;

	for (auto res : m_results) {
		if (res->passed()) numPassed++;
	}

	return numPassed; 
}

int TestCommand::numFailedTests() {
	int numFailed = 0;

	for (auto res : m_results) {
		if (res->passed() == false) numFailed++;
	}

	return numFailed; 
}

std::string TestCommand::makeRelative(std::string p) {
	StringRef path = StringRef(p);
	return path.substr(base_path.length() + 1).str();
}


std::string TestCommand::longestTest() {
	if (m_results.size() == 0) {
		return "(No tests have been ran)\n";
	}

	// The longest test, initially, is the first one.
	RunResult* longestTest = m_results[0]; 

	// For each result, if its runtime is longer, that one is the new longest.
	for (auto res : m_results) {
		if (res->runtime() > longestTest->runtime()) {
			longestTest = res; 
		}
	}

	// build a string from the test and return.
	std::stringstream ss; 
	ss << makeRelative(longestTest->filename()) << " (" << (longestTest->runtime() / 1000.0f) << " seconds)"; 
	return ss.str();
}

void TestCommand::displayResults() {
	// Print a newline, since calling runTest() doesn't add one at the end.
	std::cout << std::endl;

	// Print out a line break
	std::cout << std::endl;

	int percPassed = ((float)numPassedTests()/(float)m_results.size()) * 100;

	std::cout << "Test results (" << totalTestTime() << " seconds):\n";
	std::cout << "\t" << numPassedTests() << "/" << m_results.size() << " tests passed (" << percPassed << "%).\n";
	if (avgTestTime() > 0.00001f)
		std::cout << "\t" << avgTestTime() << " seconds to run on average.\n";
	std::cout << "\tLongest test was: " << longestTest() << "\n";

	// Print out the number of failed tests if we have any
	if (numFailedTests() > 0) {
		std::cout << "\nErrors:\n";
		for (auto res : m_results) {
			// Skip over anything that passed; only get fails.
			if (res->passed()) continue; 

			// Get only the filename itself, not the full path
			std::cout << "\t" << makeRelative(res->filename());

			// If we only have one error, print on same line and continue.
			if (res->errors().size() == 1) {
				std::cout << " (" << res->errors().at(0).what() << ")\n";
				continue; 
			}

			// Otherwise, print out everything indented.
			std::cout << ":\n"; 
			for (auto err : res->errors()) {
				std::cout << "\t\t" << err.what() << std::endl;
			}
		}
	}
}

void TestCommand::run() {
	// What are we going to do here? 
	std::string basePath;

	try {
		basePath = findProjectDirectory();
		base_path = basePath;
	} catch (std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		return;
	}

	auto testFolder = appendPath(basePath, "test");

	// If the user didn't enter anything, we'll just test everything in the test/ folder.
	if (unparsed().size() == 0) {
		runOnPath(testFolder);
	} else {
		for (auto& str : unparsed()) {
			std::string subPath = appendPath(testFolder, str);

			if (fs::exists(Twine(subPath)) == false) {
				std::cerr << "error: " << subPath << " doesn't exist.\n"; 
				continue;
			}

			// Add each result from every run to our results.
			runOnPath(subPath);
		}
	}

	displayResults();

	// Print a newline, since our runOnPath() wouldn't have.
	std::cout << "\n"; 
}

TestCommand::~TestCommand() { }