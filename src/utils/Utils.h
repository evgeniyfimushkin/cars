// Utils.h
#pragma once
#include <algorithm>
#include <cctype>
#include <string>

namespace Utils {
std::string trim(const std::string& str);
std::string toLower(const std::string& str);
bool isNumber(const std::string& str);
// Другие утилиты при необходимости
}  // namespace Utils