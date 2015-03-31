#include <helper/link.h>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <unistd.h>
#include <strings.h>
#include <vector>
#include <algorithm>
#include <iterator>
#include <dirent.h>

void invokeLinkerWithOptions(std::vector<const char *> options) {
	const char *linker = linkerPath();
	if (linker == nullptr) {
		std::cerr << "Error: a linker could not be found on this machine." << std::endl;
		exit(1);
	} 

#if defined(__APPLE__) || defined(__linux__)
	std::vector<const char *> coptions(options);
	coptions.insert(coptions.begin(), "ld");
	coptions.push_back(nullptr);
	
	pid_t pid = fork(); 

	if (pid == -1) {
		std::cerr << "fatal: failed to create new process\n";
		exit(1);
	} else if (pid > 0) {
		int status;
		waitpid(pid, &status, 0);
	} else {
		execvp(linker, (char **) &coptions[0]);
		exit(1); // should never reach this
	}

#elif defined(_WIN32) 

	std::cerr << "Fatal: invokeLinkerWithOptions is not implemented on this platform.\n"; 
	exit(1);

#endif 
}

#if defined(__APPLE__) || defined(__linux__)
	const char pathDelimiter = ':';
#elif defined(_WIN32)
	const char pathDelimiter = ';';
#endif 

const char *linkerPath() {
	char *ret = nullptr;

	std::string toFind = "ld";
	std::stringstream ss(getenv("PATH"));
	std::vector<std::string> tokens;

	std::string item;
	while (std::getline(ss, item, pathDelimiter)) {
		tokens.push_back(item);
	}

	for (std::string path : tokens) {
		if (ret != nullptr) 
			break;

		DIR *dir;
		struct dirent *ent;

		const char *pathName = path.c_str();

		if ((dir = opendir(pathName)) != nullptr) {
			while ((ent = readdir(dir)) != nullptr) {
				if (toFind == ent->d_name) {
					std::string fullPath = path + "/" + ent->d_name;

					ret = new char[fullPath.length() + 1];
					bzero((void *)ret, fullPath.length());
					strcpy(ret, fullPath.c_str());
					break;
				}
			}

			closedir(dir);
		}
	}

	return (const char *)ret;
}