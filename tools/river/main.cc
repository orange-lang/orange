#include <iostream>
#include <helper/args.h>

int main(int argc, char **argv) {
	cOptions options("River version 0.1"); 

	cCommandOption version({"v", "version"}, "Prints version", false);
	options.mainState.add(&version);

	cOptionsState test("test", "Tests your orange project");

	cCommandOption testFailed({"f", "failed"}, "Only test tests that failed on the last run", false);
	test.add(&testFailed);

	options.mainState.addState(&test); 

	options.parse(argc, argv);

	if (version.isSet()) {
		std::cout << "River version 0.1" << std::endl;
		exit(0);
	}

	return 0;
}