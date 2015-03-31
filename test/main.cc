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
	_execvp(argv[1], nullptr);
#endif 

	return 0;
}