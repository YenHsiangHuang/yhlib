#pragma once

#include <sstream>
#include <string>
#include <vector>

namespace StringUtil
{

std::vector<std::string> split_string(const std::string& s, char delimiter);

std::string& ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");
std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");
std::string& trim(std::string& str, const std::string& chars = "\t\n\v\f\r ");

bool startswith(const std::string& self, const std::string& other);
    
} // namespace StringUtil
