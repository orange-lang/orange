#include "helper/args.h"
#include <iostream>

void getArgs(int argc, char **argv, std::function<void(std::vector<std::string> arg, int loc)> cb) {
	for (int i = 1; i < argc; i++) {
		std::vector<std::string> a; 

		// Search until you find an argument that starts with - or -- 
		std::string arg = argv[i]; 
		if (arg.substr(0, 2) == "--") {
			// Begins with -- 
			a.push_back(arg.substr(0));
		} else if (arg[0] == '-') {
			// Begins with - 

			a.push_back(arg.substr(0, 2));

			if (arg.substr(2) != "")
				a.push_back(arg.substr(2));
		}

		if (a.size() != 0) {
			cb(a, i);
		}

		// TODO: windows machine arguments (/)
	}
}

const char* getParameter(std::vector<std::string> a, int argc, char **argv, int loc) {
	if (a.size() > 1) {
		return a[1].c_str();
	}

	int search = loc + 1;
	if (search >= argc) {
		return nullptr; 
	} 

	if (argv[search][0] == '-')
		return nullptr; 

	return argv[search];
}
