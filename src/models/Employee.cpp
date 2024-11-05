// Employee.cpp
#include "Employee.h"

#include <iostream>

Employee::Employee() : id(0), positionId(0), salary(0.0) {}

Employee::Employee(int id, const std::string& lastName, const std::string& firstName,
                   const std::string& patronymic, const std::string& address, const std::string& dateOfBirth,
                   int positionId, double salary)
    : id(id),
      lastName(lastName),
      firstName(firstName),
      patronymic(patronymic),
      address(address),
      dateOfBirth(dateOfBirth),
      positionId(positionId),
      salary(salary) {}

std::string Employee::getFullName() const { return lastName + " " + firstName + " " + patronymic; }

void Employee::print() const {
    std::cout << "ID: " << id << ", ФИО: " << getFullName() << ", Должность ID: " << positionId
              << ", Оклад: " << salary << std::endl;
}