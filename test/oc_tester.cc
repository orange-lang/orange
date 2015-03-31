#include <iostream>

#if defined(__linux__) || defined(__APPLE__)
#include <unistd.h>
#endif 

#ifdef _WIN32
#include <windows.h>
#include <process.h>
#endif 

int main(int argc, char **argv) {
	if (argc < 2) {
		return 1; 
	}

	FILE *f = fopen(argv[1], "r");
	if (f == nullptr) {
		return 1; 
	}

	fclose(f);

#if defined(__linux__) || defined(__APPLE__)
	execvp(argv[1], nullptr);
#elif defined(_WIN32) 
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	std::string optionsStr = "";

	CreateProcess(argv[1], (LPSTR)optionsStr.c_str(), nullptr, nullptr, false, 0, nullptr, nullptr, &si, &pi);
	WaitForSingleObject(pi.hProcess, INFINITE);

	DWORD ExitCode; 
	GetExitCodeProcess(pi.hProcess, &ExitCode);

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return (int)ExitCode;
#endif 

	return 0;
}