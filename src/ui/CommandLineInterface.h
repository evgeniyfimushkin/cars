// CommandLineInterface.h
#pragma once
#include "../database/TableDataGateway.h"

class CommandLineInterface {
   public:
    CommandLineInterface(TableDataGateway& gateway);
    void run();

   private:
    TableDataGateway& gateway;

    void showMainMenu();
    void handleEmployees();
    void handleClients();
    void handleCars();
    void handleSpareParts();

    // Методы для работы с сотрудниками
    void listEmployees();
    void addEmployee();
    void updateEmployee();
    void deleteEmployee();

    // Методы для работы с клиентами
    void listClients();
    void addClient();
    void updateClient();
    void deleteClient();

    // Методы для работы с автомобилями
    void listCars();
    void addCar();
    void updateCar();
    void deleteCar();

    // Методы для работы с запчастями
    void listSpareParts();
    void addSparePart();
    void updateSparePart();
    void deleteSparePart();

    // Вспомогательные методы
    int getLogicalIndex(int maxIndex);
};