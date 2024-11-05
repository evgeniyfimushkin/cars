// Client.h
#pragma once
#include <string>

class Client {
   public:
    int id;
    std::string firstName;
    std::string lastName;
    std::string patronymic;
    std::string passportData;

    Client();
    Client(int id, const std::string& firstName, const std::string& lastName, const std::string& patronymic,
           const std::string& passportData);

    // Методы для отображения информации
    std::string getFullName() const;
    void print() const;
};