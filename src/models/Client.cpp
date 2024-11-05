// Client.cpp
#include "Client.h"

#include <iostream>

Client::Client() : id(0) {}

Client::Client(int id, const std::string& firstName, const std::string& lastName,
               const std::string& patronymic, const std::string& passportData)
    : id(id), firstName(firstName), lastName(lastName), patronymic(patronymic), passportData(passportData) {}

std::string Client::getFullName() const { return lastName + " " + firstName + " " + patronymic; }

void Client::print() const {
    std::cout << "ID: " << id << ", ФИО: " << getFullName() << ", Паспортные данные: " << passportData
              << std::endl;
}