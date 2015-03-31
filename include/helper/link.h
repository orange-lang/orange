#ifndef __HELPER_LINK_H__
#define __HELPER_LINK_H__
#include <string>
#include <vector>

void invokeLinkerWithOptions(std::vector<const char *> options);
const char *linkerPath();

#endif