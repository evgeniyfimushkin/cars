// CommandLineInterface.cpp
#include "CommandLineInterface.h"

#include <iostream>
#include <limits>

void clearScreen() {
    std::cout << "\033[2J\033[1;1H";  // Очистить экран и вернуть курсор в начало
}
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
                clearScreen();
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
                clearScreen();
                back = true;
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
        }
    }
}

void CommandLineInterface::listEmployees() {
    clearScreen();
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
    bool back = false;
    while (!back) {
        std::cout << "\n=== Клиенты ===" << std::endl;
        std::cout << "1. Список клиентов" << std::endl;
        std::cout << "2. Добавить клиента" << std::endl;
        std::cout << "3. Изменить клиента" << std::endl;
        std::cout << "4. Удалить клиента" << std::endl;
        std::cout << "0. Назад" << std::endl;
        std::cout << "Выберите действие: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                listClients();
                break;
            case 2:
                addClient();
                break;
            case 3:
                updateClient();
                break;
            case 4:
                deleteClient();
                break;
            case 0:
                clearScreen();
                back = true;
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
        }
    }
}

// Методы для работы с клиентами
void CommandLineInterface::listClients() {
    clearScreen();
    std::vector<Client> clients = gateway.getAllClients();
    int index = 1;
    std::cout << "\nСписок клиентов:" << std::endl;
    for (const auto& client : clients) {
        std::cout << index++ << ". ";
        client.print();
    }
}

void CommandLineInterface::addClient() {
    Client client;
    std::cout << "Введите имя: ";
    std::getline(std::cin, client.firstName);
    std::cout << "Введите фамилию: ";
    std::getline(std::cin, client.lastName);
    std::cout << "Введите отчество: ";
    std::getline(std::cin, client.patronymic);
    std::cout << "Введите паспортные данные: ";
    std::getline(std::cin, client.passportData);

    gateway.addClient(client);
}

void CommandLineInterface::updateClient() {
    listClients();
    std::cout << "Выберите номер клиента для изменения: ";
    int index = getLogicalIndex(gateway.getAllClients().size());

    Client client = gateway.getClientByIndex(index - 1);

    std::cout << "Текущее имя (" << client.firstName << "): ";
    std::string input;
    std::getline(std::cin, input);
    if (!input.empty()) client.firstName = input;

    std::cout << "Текущая фамилия (" << client.lastName << "): ";
    std::getline(std::cin, input);
    if (!input.empty()) client.lastName = input;

    std::cout << "Текущее отчество (" << client.patronymic << "): ";
    std::getline(std::cin, input);
    if (!input.empty()) client.patronymic = input;

    std::cout << "Текущие паспортные данные (" << client.passportData << "): ";
    std::getline(std::cin, input);
    if (!input.empty()) client.passportData = input;

    gateway.updateClient(client);
}

void CommandLineInterface::deleteClient() {
    listClients();
    std::cout << "Выберите номер клиента для удаления: ";
    int index = getLogicalIndex(gateway.getAllClients().size());

    Client client = gateway.getClientByIndex(index - 1);

    gateway.deleteClient(client.id);
}

void CommandLineInterface::handleCars() {
    bool back = false;
    while (!back) {
        std::cout << "\n=== Автомобили ===" << std::endl;
        std::cout << "1. Список автомобилей" << std::endl;
        std::cout << "2. Добавить автомобиль" << std::endl;
        std::cout << "3. Изменить автомобиль" << std::endl;
        std::cout << "4. Удалить автомобиль" << std::endl;
        std::cout << "0. Назад" << std::endl;
        std::cout << "Выберите действие: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                listCars();
                break;
            case 2:
                addCar();
                break;
            case 3:
                updateCar();
                break;
            case 4:
                deleteCar();
                break;
            case 0:
                clearScreen();
                back = true;
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
        }
    }
}

// Методы для работы с автомобилями
void CommandLineInterface::listCars() {
    clearScreen();
    std::vector<Car> cars = gateway.getAllCars();
    int index = 1;
    std::cout << "\nСписок автомобилей:" << std::endl;
    for (const auto& car : cars) {
        std::cout << index++ << ". ";
        car.print();
    }
}

void CommandLineInterface::addCar() {
    Car car;
    std::cout << "Введите марку: ";
    std::getline(std::cin, car.make);
    std::cout << "Введите модель: ";
    std::getline(std::cin, car.model);
    std::cout << "Введите цвет: ";
    std::getline(std::cin, car.color);
    std::cout << "Введите номер двигателя: ";
    std::getline(std::cin, car.engineNumber);
    std::cout << "Введите регистрационный номер: ";
    std::getline(std::cin, car.registrationNumber);
    std::cout << "Введите номер кузова: ";
    std::getline(std::cin, car.bodyNumber);
    std::cout << "Введите номер шасси: ";
    std::getline(std::cin, car.chassisNumber);
    std::cout << "Введите дату выпуска (YYYY-MM-DD): ";
    std::getline(std::cin, car.manufactureDate);
    std::cout << "Введите пробег: ";
    std::cin >> car.mileage;
    std::cout << "Введите цену на момент выпуска: ";
    std::cin >> car.manufacturePrice;
    std::cout << "Введите цену продажи: ";
    std::cin >> car.salePrice;
    std::cout << "Введите цену покупки: ";
    std::cin >> car.purchasePrice;
    std::cin.ignore();
    std::cout << "Введите номер справки о тех. состоянии: ";
    std::getline(std::cin, car.technicalCertificateNumber);
    std::cout << "Введите дату справки о тех. состоянии (YYYY-MM-DD): ";
    std::getline(std::cin, car.technicalCertificateDate);
    std::cout << "Введите ID эксперта: ";
    std::cin >> car.expertId;
    std::cin.ignore();

    gateway.addCar(car);
}

void CommandLineInterface::updateCar() {
    listCars();
    std::cout << "Выберите номер автомобиля для изменения: ";
    int index = getLogicalIndex(gateway.getAllCars().size());

    Car car = gateway.getCarByIndex(index - 1);

    std::string input;
    std::cout << "Текущая марка (" << car.make << "): ";
    std::getline(std::cin, input);
    if (!input.empty()) car.make = input;

    // Аналогично для остальных полей автомобиля

    // ...

    gateway.updateCar(car);
}

void CommandLineInterface::deleteCar() {
    listCars();
    std::cout << "Выберите номер автомобиля для удаления: ";
    int index = getLogicalIndex(gateway.getAllCars().size());

    Car car = gateway.getCarByIndex(index - 1);

    gateway.deleteCar(car.id);
}

void CommandLineInterface::handleSpareParts() {
    bool back = false;
    while (!back) {
        std::cout << "\n=== Запчасти ===" << std::endl;
        std::cout << "1. Список запчастей" << std::endl;
        std::cout << "2. Добавить запчасть" << std::endl;
        std::cout << "3. Изменить запчасть" << std::endl;
        std::cout << "4. Удалить запчасть" << std::endl;
        std::cout << "0. Назад" << std::endl;
        std::cout << "Выберите действие: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                listSpareParts();
                break;
            case 2:
                addSparePart();
                break;
            case 3:
                updateSparePart();
                break;
            case 4:
                deleteSparePart();
                break;
            case 0:
                clearScreen();
                back = true;
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
        }
    }
}

// Методы для работы с запчастями
void CommandLineInterface::listSpareParts() {
    clearScreen();
    std::vector<SparePart> spareParts = gateway.getAllSpareParts();
    int index = 1;
    std::cout << "\nСписок запчастей:" << std::endl;
    for (const auto& sp : spareParts) {
        std::cout << index++ << ". ";
        sp.print();
    }
}

void CommandLineInterface::addSparePart() {
    SparePart sp;
    std::cout << "Введите наименование: ";
    std::getline(std::cin, sp.name);
    std::cout << "Введите марку автомобиля: ";
    std::getline(std::cin, sp.make);
    std::cout << "Введите модель автомобиля: ";
    std::getline(std::cin, sp.model);
    std::cout << "Введите цену: ";
    std::cin >> sp.price;
    std::cout << "Введите количество на складе: ";
    std::cin >> sp.stockQuantity;
    std::cin.ignore();

    gateway.addSparePart(sp);
}

void CommandLineInterface::updateSparePart() {
    listSpareParts();
    std::cout << "Выберите номер запчасти для изменения: ";
    int index = getLogicalIndex(gateway.getAllSpareParts().size());

    SparePart sp = gateway.getSparePartByIndex(index - 1);

    std::string input;
    std::cout << "Текущее наименование (" << sp.name << "): ";
    std::getline(std::cin, input);
    if (!input.empty()) sp.name = input;

    // Аналогично для остальных полей запчасти

    // ...

    gateway.updateSparePart(sp);
}

void CommandLineInterface::deleteSparePart() {
    listSpareParts();
    std::cout << "Выберите номер запчасти для удаления: ";
    int index = getLogicalIndex(gateway.getAllSpareParts().size());

    SparePart sp = gateway.getSparePartByIndex(index - 1);

    gateway.deleteSparePart(sp.id);
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