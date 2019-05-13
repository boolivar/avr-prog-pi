#ifndef OPTIONS_H
#define OPTIONS_H

#include "config.h"

#include <unordered_map>
#include <string>

extern std::unordered_map<std::string, std::string> properties(int argc, char** argv);

extern Config config(const std::unordered_map<std::string, std::string>& properties);

#endif // OPTIONS_H
