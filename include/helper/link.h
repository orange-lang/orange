#ifndef __HELPER_LINK_H__
#define __HELPER_LINK_H__
#include <string>
#include <vector>

int invokeProgramWithOptions(const char *program, std::vector<const char *> options, bool close = false);
const char *programPath(std::string programName);

void invokeLinkerWithOptions(std::vector<const char *> options);
const char *linkerPath();

#endif