// CommandLineInterface.cpp
#include "CommandLineInterface.h"

#include <iostream>
#include <limits>

CommandLineInterface::CommandLineInterface(TableDataGateway& gateway) : gateway(gateway) {}

void CommandLineInterface::run() {
    bool running = true;
    while (running) {
        showMainMenu();
        int choice;
        std::cin >> choice;
        std::cin.ignore();  // Очистка буфера ввода

        switch (choice) {
            case 1:
                handleEmployees();
                break;
            case 2:
                handleClients();
                break;
            case 3:
                handleCars();
                break;
            case 4:
                handleSpareParts();
                break;
            case 0:
                running = false;
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
        }
    }
}

void CommandLineInterface::showMainMenu() {
    std::cout << "\n===== Главное меню =====" << std::endl;
    std::cout << "1. Работа с сотрудниками" << std::endl;
    std::cout << "2. Работа с клиентами" << std::endl;
    std::cout << "3. Работа с автомобилями" << std::endl;
    std::cout << "4. Работа с запчастями" << std::endl;
    std::cout << "0. Выход" << std::endl;
    std::cout << "Выберите действие: ";
}

void CommandLineInterface::handleEmployees() {
    bool back = false;
    while (!back) {
        std::cout << "\n=== Сотрудники ===" << std::endl;
        std::cout << "1. Список сотрудников" << std::endl;
        std::cout << "2. Добавить сотрудника" << std::endl;
        std::cout << "3. Изменить сотрудника" << std::endl;
        std::cout << "4. Удалить сотрудника" << std::endl;
        std::cout << "0. Назад" << std::endl;
        std::cout << "Выберите действие: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                listEmployees();
                break;
            case 2:
                addEmployee();
                break;
            case 3:
                updateEmployee();
                break;
            case 4:
                deleteEmployee();
                break;
            case 0:
                back = true;
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
        }
    }
}

void CommandLineInterface::listEmployees() {
    std::vector<Employee> employees = gateway.getAllEmployees();
    int index = 1;
    std::cout << "\nСписок сотрудников:" << std::endl;
    for (const auto& emp : employees) {
        std::cout << index++ << ". ";
        emp.print();
    }
}

void CommandLineInterface::addEmployee() {
    Employee emp;
    std::cout << "Введите фамилию: ";
    std::getline(std::cin, emp.lastName);
    std::cout << "Введите имя: ";
    std::getline(std::cin, emp.firstName);
    std::cout << "Введите отчество: ";
    std::getline(std::cin, emp.patronymic);
    std::cout << "Введите адрес: ";
    std::getline(std::cin, emp.address);
    std::cout << "Введите дату рождения (YYYY-MM-DD): ";
    std::getline(std::cin, emp.dateOfBirth);
    std::cout << "Введите ID должности: ";
    std::cin >> emp.positionId;
    std::cout << "Введите оклад: ";
    std::cin >> emp.salary;
    std::cin.ignore();

    gateway.addEmployee(emp);
}

void CommandLineInterface::updateEmployee() {
    listEmployees();
    std::cout << "Выберите номер сотрудника для изменения: ";
    int index = getLogicalIndex(gateway.getAllEmployees().size());

    Employee emp = gateway.getEmployeeByIndex(index - 1);

    std::cout << "Текущая фамилия (" << emp.lastName << "): ";
    std::string input;
    std::getline(std::cin, input);
    if (!input.empty()) emp.lastName = input;

    std::cout << "Текущее имя (" << emp.firstName << "): ";
    std::getline(std::cin, input);
    if (!input.empty()) emp.firstName = input;

    std::cout << "Текущее отчество (" << emp.patronymic << "): ";
    std::getline(std::cin, input);
    if (!input.empty()) emp.patronymic = input;

    std::cout << "Текущий адрес (" << emp.address << "): ";
    std::getline(std::cin, input);
    if (!input.empty()) emp.address = input;

    std::cout << "Текущая дата рождения (" << emp.dateOfBirth << "): ";
    std::getline(std::cin, input);
    if (!input.empty()) emp.dateOfBirth = input;

    std::cout << "Текущий ID должности (" << emp.positionId << "): ";
    std::getline(std::cin, input);
    if (!input.empty()) emp.positionId = std::stoi(input);

    std::cout << "Текущий оклад (" << emp.salary << "): ";
    std::getline(std::cin, input);
    if (!input.empty()) emp.salary = std::stod(input);

    gateway.updateEmployee(emp);
}

void CommandLineInterface::deleteEmployee() {
    listEmployees();
    std::cout << "Выберите номер сотрудника для удаления: ";
    int index = getLogicalIndex(gateway.getAllEmployees().size());

    Employee emp = gateway.getEmployeeByIndex(index - 1);

    gateway.deleteEmployee(emp.id);
}

void CommandLineInterface::handleClients() {
    // Аналогично обработке сотрудников
}

void CommandLineInterface::handleCars() {
    // Аналогично обработке сотрудников
}

void CommandLineInterface::handleSpareParts() {
    // Аналогично обработке сотрудников
}

// Вспомогательный метод для получения корректного логического индекса
int CommandLineInterface::getLogicalIndex(int maxIndex) {
    int index;
    while (true) {
        std::cin >> index;
        std::cin.ignore();
        if (index >= 1 && index <= maxIndex) {
            return index;
        } else {
            std::cout << "Неверный номер. Попробуйте снова: ";
        }
    }
}