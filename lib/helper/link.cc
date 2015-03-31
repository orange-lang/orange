#include <helper/link.h>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <iterator>

#if defined(__linux__) || defined(__APPLE__)
#include <unistd.h>
#include <strings.h>
#include <dirent.h>
#endif 

#ifdef __linux__
	#include <sys/types.h>
	#include <sys/wait.h>
#endif

#ifdef _WIN32
#include <windows.h>
#include <process.h>
#endif 

int invokeProgramWithOptions(const char *program, std::vector<const char *> options, bool do_close) {
	std::vector<const char *> coptions(options);
	coptions.insert(coptions.begin(), program);
	coptions.push_back(nullptr);

#if defined(__APPLE__) || defined(__linux__)
	pid_t pid = fork(); 

	if (pid == -1) {
		std::cerr << "fatal: failed to create new process\n";
		exit(1);
	} else if (pid > 0) {
		int status;
		waitpid(pid, &status, 0);
		return (int)WEXITSTATUS(status);
	} else {
		if (do_close == true) {
			close(0);
			close(1);
			close(2);
		}
		execvp(program, (char **) &coptions[0]);
		exit(1); // should never reach this
	}

#elif defined(_WIN32) 
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	std::string optionsStr = "";
	for (auto s : coptions) {
		if (s == nullptr) continue;
		optionsStr += s;
		optionsStr += " ";
	}

	CreateProcess(linker, (LPSTR)optionsStr.c_str(), nullptr, nullptr, false, 0, nullptr, nullptr, &si, &pi);
	WaitForSingleObject(pi.hProcess, INFINITE);

	DWORD dwExitCode = 9999;
	GetExitCodeProcess(pi.hProcess, &dwExitCode);

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return (int)dwExitCode;
#endif 
}

void invokeLinkerWithOptions(std::vector<const char *> options) {
	const char *linker = linkerPath();
	if (linker == nullptr) {
		std::cerr << "Error: a linker could not be found on this machine." << std::endl;
		exit(1);
	} 

	invokeProgramWithOptions(linker, options);
}

#if defined(__APPLE__) || defined(__linux__)
	const char pathDelimiter = ':';
#elif defined(_WIN32)
	const char pathDelimiter = ';';
#endif 

const char *programPath(std::string programName) {
	char *ret = nullptr;

	std::string toFind = programName;

#if defined(_WIN32)
	// On Win32, we want to use gcc as a linker instead.
	// Using ld.exe directly is a little iffy. 
	toFind = "gcc.exe";
#endif 

	std::stringstream ss(getenv("PATH"));
	std::vector<std::string> tokens;

	std::string item;
	while (std::getline(ss, item, pathDelimiter)) {
		tokens.push_back(item);
	}


	for (std::string path : tokens) {
		if (ret != nullptr) 
			break;

#if defined(__linux__) || defined(__APPLE__) 
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
#elif defined(_WIN32) 
		const char *pathName = (path + "\\*").c_str();

		WIN32_FIND_DATA FindFileData;
		HANDLE hFind = nullptr;


		hFind = FindFirstFile(pathName, &FindFileData); 
		if (hFind != INVALID_HANDLE_VALUE) {
			if (toFind == FindFileData.cFileName) {
				std::string fullPath = path + "\\" + FindFileData.cFileName;

				ret = new char[fullPath.length() + 1];
				for (int i = 0; i < fullPath.length(); i++)
					ret[i] = 0;
				strcpy(ret, fullPath.c_str());
				FindClose(hFind);
				break;
			}

			while (FindNextFile(hFind, &FindFileData)) {
				if (hFind == INVALID_HANDLE_VALUE)
					break;

				if (toFind == FindFileData.cFileName) {
					std::string fullPath = path + "\\" + FindFileData.cFileName;

					ret = new char[fullPath.length() + 1];
					for (int i = 0; i < fullPath.length(); i++)
						ret[i] = 0;
					strcpy(ret, fullPath.c_str());
					FindClose(hFind);
					break;
				}
			}
		}
#endif 
	}

	return (const char *)ret;
}

const char *linkerPath() {
	return programPath("ld");
}
