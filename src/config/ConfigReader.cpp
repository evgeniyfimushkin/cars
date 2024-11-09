// ConfigReader.cpp
#include "ConfigReader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

ConfigReader::ConfigReader(const std::string& filename) {
    parseFile(filename);
}

void ConfigReader::parseFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Could not open config file");
    }

    std::string line, section;
    while (std::getline(file, line)) {
        // Удаляем пробелы в начале и в конце строки
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);

        // Пропускаем комментарии и пустые строки
        if (line.empty() || line[0] == '#') continue;

        if (line[0] == '[' && line.back() == ']') {
            // Новая секция [section]
            section = line.substr(1, line.size() - 2);
        } else {
            // Ключ-значение key=value
            std::istringstream kv(line);
            std::string key, value;
            if (std::getline(kv, key, '=') && std::getline(kv, value)) {
                // Удаляем пробелы
                key.erase(key.find_last_not_of(" \t\r\n") + 1);
                value.erase(0, value.find_first_not_of(" \t\r\n"));
                data[section][key] = value;
            }
        }
    }
}

std::string ConfigReader::get(const std::string& section, const std::string& key) const {
    auto sec = data.find(section);
    if (sec != data.end()) {
        auto kv = sec->second.find(key);
        if (kv != sec->second.end()) {
            return kv->second;
        }
    }
    throw std::runtime_error("Key not found in config: " + section + "." + key);
}
