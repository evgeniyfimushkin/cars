// Utils.cpp
#include "Utils.h"

namespace Utils {

std::string trim(const std::string& str) {
    std::string result = str;
    result.erase(result.begin(), std::find_if(result.begin(), result.end(),
                                              [](unsigned char ch) { return !std::isspace(ch); }));
    result.erase(
        std::find_if(result.rbegin(), result.rend(), [](unsigned char ch) { return !std::isspace(ch); })
            .base(),
        result.end());
    return result;
}

std::string toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char ch) { return std::tolower(ch); });
    return result;
}

bool isNumber(const std::string& str) {
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}

}  // namespace Utils