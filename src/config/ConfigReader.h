// ConfigReader.h
#pragma once
#include <string>
#include <unordered_map>

class ConfigReader {
public:
    explicit ConfigReader(const std::string& filename);
    std::string get(const std::string& section, const std::string& key) const;

private:
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> data;
    void parseFile(const std::string& filename);
};
