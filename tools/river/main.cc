#include <iostream>
#include <helper/args.h>
#include <helper/link.h>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/archives/json.hpp>
#include <boost/regex.hpp>
#include <fstream>
using namespace boost::filesystem;
using namespace boost;

#define RIVER_SETTINGS "river.settings.json"

void testFiles(std::vector<path> paths);
void runFailed();

class RiverConfig {
public:
	std::unordered_map<std::string, std::string> settings;

	template <class Archive>
	void serialize(Archive& ar) {
		ar(settings);
	}
};

int main(int argc, char **argv) {
	cOptions options("River version 0.1"); 

	// main state 
	cCommandOption version({"v", "version"}, "Prints version", false);
	options.mainState.add(&version);

	// test state 
	cOptionsState test("test", "Tests your orange project");

	cCommandOption testFailed({"f", "failed"}, "Only test tests that failed on the last run", false);
	test.add(&testFailed);

	options.mainState.addState(&test); 

	// settings state 
	cOptionsState settings("settings", "Sets or gets setting from orange");
	options.mainState.addState(&settings);

	// Parse command line 
	options.parse(argc, argv);

	if (version.isSet()) {
		std::cout << "River version 0.1" << std::endl;
		exit(0);
	}

	if (settings.isActive()) {
		if (settings.unparsed().size() == 0) {
			std::cout << "Usage: " << argv[0] << "settings [settingName]|[settingName settingValue]\n";
			return 0;
		}

		std::string setting = settings.unparsed()[0];
		if (settings.unparsed().size() > 1) {
			std::string value = settings.unparsed()[1];

			// change it in settings class. save settings class to file. 
			RiverConfig rc; 

			{
				std::ifstream is(RIVER_SETTINGS);
				if (is.is_open() == true) {
					cereal::JSONInputArchive ar(is);
					ar(rc);					
				}
			}

			rc.settings[setting] = value;

			{
				std::ofstream os(RIVER_SETTINGS);
				cereal::JSONOutputArchive ar(os);
				ar(rc);
			}

			return 0; 
		} else {
			// get it from settings class.
			{
				std::ifstream is(RIVER_SETTINGS);
				if (is.is_open() == false) {
					std::cerr << "fatal: no settings file exists yet.\n";
					exit(1);
				}

				cereal::JSONInputArchive ar(is);

				RiverConfig rc; 
				ar(rc);

				std::cout << rc.settings[setting] << std::endl;
			}
		}

		return 0;
	}

	if (test.isActive() && testFailed.isSet()) {
		runFailed();
	} else if (test.isActive() && test.unparsed().size() == 0) {
		// for now, test everything in test, going through each subdirectory.
		path p("test");

		regex filter(".*\\.or");
		std::vector<path> toTest;
		
		if (!exists(p)) {
			exit(0); 
		} else {
			for (auto& entry : make_iterator_range(recursive_directory_iterator(p), {})) {
				smatch what;
				if (!regex_match(entry.path().filename().string(), what, filter)) continue;
				toTest.push_back(entry.path());
			}

			testFiles(toTest);
		}
	} else if (test.isActive() && test.unparsed().size() > 0) {
		regex filter(".*\\.or");
		std::vector<path> toTest;

		for (std::string subdir : test.unparsed()) {
			std::string search = "test/" + subdir; 
			path p(search);

			if (!exists(p)) {
				std::cerr << "fatal: path " << search << " does not exist.\n";
				exit(1);
			}	

			for (auto& entry : make_iterator_range(recursive_directory_iterator(p), {})) {
				smatch what;
				if (!regex_match(entry.path().filename().string(), what, filter)) continue;
				toTest.push_back(entry.path());
			}
		
		}

		testFiles(toTest);
	}

	return 0;
}

class TestError {
public:
	std::string file; 
	std::string reason;

	std::string string() {
		return file + " (" + reason + ")";
	}
};

void runFailed() {
	std::vector<path> toTest;

	std::ifstream errorCache("build/test/.fails-cache.river", std::ios_base::in);
	std::string line;
	while (std::getline(errorCache, line)) {
		if (line == "") continue; 
		toTest.push_back(line);
	}

	testFiles(toTest);
}

void createFailCache(std::vector<TestError> fails) {
	std::ofstream errorCache("build/test/.fails-cache.river", std::ios_base::out | std::ios_base::trunc);
	if (errorCache.is_open() == false) {
		std::cerr << "fatal: could not create fail cache\n";
		exit(1);
	}

	for (TestError error : fails) {
		errorCache << error.file << std::endl;
	}

	errorCache.close();
}

void testFiles(std::vector<path> paths) {
  boost::posix_time::ptime startTime = boost::posix_time::microsec_clock::local_time();

	int total = 0;
	int failed = 0;
	int passed = 0;
	int warnings = 0;

	std::vector<TestError> errors;


	RiverConfig rc; 

	{
		std::ifstream is(RIVER_SETTINGS);
		if (is.is_open() == true) {
			cereal::JSONInputArchive ar(is);
			ar(rc);					
		}
	}

	const char *ocPath = programPath("oc");
	auto oc_path_it = rc.settings.find("oc_path");
	if (oc_path_it != rc.settings.end()) {
		ocPath = oc_path_it->second.c_str();
	} else if (ocPath == nullptr) {
		std::cerr << "fatal: could not find oc in $PATH.\n";
		exit(1);
	}

	path oc_p(ocPath);
	if (!exists(oc_p)) {
		std::cerr << "fatal: oc does not exist at " << ocPath << std::endl;
		exit(1);
	}



	try {
		boost::filesystem::create_directories("build/test");	
	} catch (filesystem_error e) {
		std::cerr << "fatal: could not build directory build/test\n"; 
		exit(1);
	}

	for (path p : paths) {
		std::vector<const char *> options;
		options.push_back(p.string().c_str());
		options.push_back("-o");

		std::string output = p.stem().string();
		output = "build/test/" + output;

#ifdef _WIN32 
		output += ".exe";
#endif 

		options.push_back(output.c_str());

		int status = invokeProgramWithOptions(ocPath, options, true);
		bool added_error = false;

		path output_p(output);

		if (!exists(output_p)) status = 1;

		if (status && !added_error) {
			TestError err; 
			err.file = p.string();
			err.reason = "compile failed";
			errors.push_back(err);
			added_error = true;
		}

		if (status == 0) {
			std::vector<const char *> roptions;
			status = invokeProgramWithOptions(output.c_str(), roptions, true);
		}

		if (status && !added_error) {
			TestError err; 
			err.file = p.string();
			err.reason = "program did not return 0";
			errors.push_back(err);
			added_error = true;
		}

		if (status == 0) {
			std::cout << "." << std::flush;
			passed++;
		} else {
			std::cout << "F" << std::flush;
			failed++;
		}

		if (exists(output_p)) {
			remove(output_p);		
		}

		total++;

		if ((total % 40) == 0) std::cout << "\n";
	}

	boost::posix_time::ptime endTime = boost::posix_time::microsec_clock::local_time();
  boost::posix_time::time_duration diff = endTime - startTime;
  long ms = diff.total_milliseconds();

	std::cout << "\n\nTest results (" << (float)ms/1000.0f << " seconds):\n";
	std::cout << "\t" << total << " tests total.\n";
	std::cout << "\t" << passed << " tests passed.\n";
	std::cout << "\t" << failed << " tests failed.\n";

	if (errors.size() > 0) {
		std::cout << "\nErrors:\n";
		for (TestError error : errors) {
			std::cout << "\t" << error.string() << std::endl;
		}
		std::cout << std::endl;
	}

	createFailCache(errors);
}
