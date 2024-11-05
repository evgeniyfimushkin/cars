// Employee.h
#pragma once
#include <string>

class Employee {
   public:
    int id;
    std::string lastName;
    std::string firstName;
    std::string patronymic;
    std::string address;
    std::string dateOfBirth;  // Формат: "YYYY-MM-DD"
    int positionId;
    double salary;

    Employee();
    Employee(int id, const std::string& lastName, const std::string& firstName, const std::string& patronymic,
             const std::string& address, const std::string& dateOfBirth, int positionId, double salary);

    // Методы для отображения информации
    std::string getFullName() const;
    void print() const;
};