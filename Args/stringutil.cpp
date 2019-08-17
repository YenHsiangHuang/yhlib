#include "stringutil.hpp"

std::vector<std::string> StringUtil::split_string(const std::string& s, char delimiter) {
    std::string buf;
    std::istringstream ss(s);

    std::vector<std::string> res;
    while (std::getline(ss, buf, delimiter)) {
        res.push_back(buf);
    }

    return res;
}

// Note: takes & as an input and returns the same &
//       makes a good operation flow
std::string& StringUtil::ltrim(std::string& str, const std::string& chars) {
    str.erase(0, str.find_first_not_of(chars));
    return str;
}

std::string& StringUtil::rtrim(std::string& str, const std::string& chars) {
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}

std::string& StringUtil::trim(std::string& str, const std::string& chars) {
    return ltrim(rtrim(str, chars), chars);
}

/**
 * edge cases:
 *     self = "xxx", other = "" -> true
 *     self = ""   , other = "" -> true
 */
bool StringUtil::startswith(const std::string& self, const std::string& other) {
    if (other.empty()) return true;
    if (self.empty()) return false;

    int cmp_res = self.compare(other);

    return cmp_res == 0 || (cmp_res > 0 && self[0] == other[0]);
}