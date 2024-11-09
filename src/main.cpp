// main.cpp
#include <iostream>
#include "database/DatabaseConnection.h"
#include "database/TableDataGateway.h"
#include "database/TablesInitializer.h"
#include "ui/CommandLineInterface.h"
#include "config/ConfigReader.h"

int main() {
    try {
        // Загружаем конфигурацию
        ConfigReader config("src/config.ini");
        
        // Формируем строку подключения
        std::string connectionString = "DRIVER={" + config.get("database", "driver") + "};"
                                       "SERVER=" + config.get("database", "server") + ";"
                                       "PORT=" + config.get("database", "port") + ";"
                                       "DATABASE=" + config.get("database", "database") + ";"
                                       "UID=" + config.get("database", "username") + ";"
                                       "PWD=" + config.get("database", "password") + ";";

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
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
