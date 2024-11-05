

// main.cpp
#include <iostream>

#include "database/DatabaseConnection.h"
#include "database/TableDataGateway.h"
#include "database/TablesInitializer.h"
#include "ui/CommandLineInterface.h"

int main() {
    // Строка подключения к базе данных PostgreSQL через ODBC
    std::string connectionString =
        "DRIVER={PostgreSQL};SERVER=localhost;PORT=5432;DATABASE=cars;UID=admin;PWD=admin;";

    // Создаем объект подключения к базе данных
    DatabaseConnection dbConn(connectionString);

    // Пытаемся подключиться к базе данных
    if (!dbConn.connect()) {
        std::cerr << "Не удалось подключиться к базе данных." << std::endl;
        return 1;
    }

    // Инициализируем таблицы
    TablesInitializer initializer(dbConn);
    initializer.initializeTables();

    // Создаем объект шлюза данных
    TableDataGateway gateway(dbConn);

    // Запускаем пользовательский интерфейс
    CommandLineInterface cli(gateway);
    cli.run();

    // Отключаемся от базы данных
    dbConn.disconnect();

    return 0;
}