// TableDataGateway.h
#pragma once

#include <vector>

#include "../models/Car.h"
#include "../models/Client.h"
#include "../models/Employee.h"
#include "../models/SparePart.h"
#include "DatabaseConnection.h"

class TableDataGateway {
   public:
    TableDataGateway(DatabaseConnection& dbConn);

    // Методы для работы с сотрудниками
    std::vector<Employee> getAllEmployees();
    Employee getEmployeeByIndex(int index);
    void addEmployee(const Employee& employee);
    void updateEmployee(const Employee& employee);
    void deleteEmployee(int employeeId);

    // Методы для работы с клиентами
    std::vector<Client> getAllClients();
    Client getClientByIndex(int index);
    void addClient(const Client& client);
    void updateClient(const Client& client);
    void deleteClient(int clientId);

    // Методы для работы с автомобилями
    std::vector<Car> getAllCars();
    Car getCarByIndex(int index);
    void addCar(const Car& car);
    void updateCar(const Car& car);
    void deleteCar(int carId);

    // Методы для работы с запчастями
    std::vector<SparePart> getAllSpareParts();
    SparePart getSparePartByIndex(int index);
    void addSparePart(const SparePart& sparePart);
    void updateSparePart(const SparePart& sparePart);
    void deleteSparePart(int sparePartId);

   private:
    DatabaseConnection& dbConn;

    // Вспомогательные методы для обработки результатов запросов
};