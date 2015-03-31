#ifndef __HELPER_ARGS_H__
#define __HELPER_ARGS_H__

#include <string> 
#include <vector>
#include <functional>

// gets args from command line,
void getArgs(int argc, char **argv, std::function<void(std::vector<std::string> arg, int loc)> cb);
const char* getParameter(std::vector<std::string> a, int argc, char **argv, int loc);

#endif 