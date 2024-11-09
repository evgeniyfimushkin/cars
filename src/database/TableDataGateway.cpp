// TableDataGateway.cpp
#include "TableDataGateway.h"

#include <iostream>

// Для работы с SQL типами данных
#include <sqltypes.h>

TableDataGateway::TableDataGateway(DatabaseConnection &dbConn) : dbConn(dbConn) {
}

//
// Методы для работы с сотрудниками
//

std::vector<Employee> TableDataGateway::getAllEmployees() {
    std::vector<Employee> employees;

    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLAllocHandle(SQL_HANDLE_STMT, dbConn.getConnectionHandle(), &stmt);

    const char *sql =
            "SELECT employee_id, last_name, first_name, patronymic, address, date_of_birth, position_id, salary "
            "FROM Employees";

    ret = SQLExecDirect(stmt, (SQLCHAR *) sql, SQL_NTS);
    if (SQL_SUCCEEDED(ret)) {
        while (SQLFetch(stmt) == SQL_SUCCESS) {
            Employee emp;
            char lastName[51], firstName[51], patronymic[51], address[201], dateOfBirth[11];
            SQLINTEGER employeeId, positionId;
            SQLDOUBLE salary;

            SQLGetData(stmt, 1, SQL_C_SLONG, &employeeId, 0, NULL);
            SQLGetData(stmt, 2, SQL_C_CHAR, lastName, sizeof(lastName), NULL);
            SQLGetData(stmt, 3, SQL_C_CHAR, firstName, sizeof(firstName), NULL);
            SQLGetData(stmt, 4, SQL_C_CHAR, patronymic, sizeof(patronymic), NULL);
            SQLGetData(stmt, 5, SQL_C_CHAR, address, sizeof(address), NULL);
            SQLGetData(stmt, 6, SQL_C_CHAR, dateOfBirth, sizeof(dateOfBirth), NULL);
            SQLGetData(stmt, 7, SQL_C_SLONG, &positionId, 0, NULL);
            SQLGetData(stmt, 8, SQL_C_DOUBLE, &salary, 0, NULL);

            emp.id = employeeId;
            emp.lastName = lastName;
            emp.firstName = firstName;
            emp.patronymic = patronymic;
            emp.address = address;
            emp.dateOfBirth = dateOfBirth;
            emp.positionId = positionId;
            emp.salary = salary;

            employees.push_back(emp);
        }
    } else {
        std::cerr << "Error fetching employees." << std::endl;
        dbConn.showError(SQL_HANDLE_STMT, stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    return employees;
}

Employee TableDataGateway::getEmployeeByIndex(int index) {
    std::vector<Employee> employees = getAllEmployees();
    if (index >= 0 && index < employees.size()) {
        return employees[index];
    } else {
        throw std::out_of_range("Invalid employee index.");
    }
}

void TableDataGateway::addEmployee(const Employee &employee) {
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLAllocHandle(SQL_HANDLE_STMT, dbConn.getConnectionHandle(), &stmt);

    const char *sql =
            "INSERT INTO Employees (last_name, first_name, patronymic, address, date_of_birth, position_id, "
            "salary) VALUES (?, ?, ?, ?, ?, ?, ?)";
    ret = SQLPrepare(stmt, (SQLCHAR *) sql, SQL_NTS);

    if (SQL_SUCCEEDED(ret)) {
        SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0,
                         (SQLPOINTER) employee.lastName.c_str(), 0, NULL);
        SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0,
                         (SQLPOINTER) employee.firstName.c_str(), 0, NULL);
        SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0,
                         (SQLPOINTER) employee.patronymic.c_str(), 0, NULL);
        SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 200, 0,
                         (SQLPOINTER) employee.address.c_str(), 0, NULL);
        SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_TYPE_DATE, 0, 0,
                         (SQLPOINTER) employee.dateOfBirth.c_str(), 0, NULL);
        SQLBindParameter(stmt, 6, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0,
                         (SQLPOINTER) &employee.positionId, 0, NULL);
        SQLBindParameter(stmt, 7, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_NUMERIC, 10, 2,
                         (SQLPOINTER) &employee.salary, 0, NULL);

        ret = SQLExecute(stmt);
        if (SQL_SUCCEEDED(ret)) {
            std::cout << "Employee added successfully." << std::endl;
        } else {
            std::cerr << "Error adding employee." << std::endl;
            dbConn.showError(SQL_HANDLE_STMT, stmt);
        }
    } else {
        std::cerr << "Error preparing statement for adding employee." << std::endl;
        dbConn.showError(SQL_HANDLE_STMT, stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void TableDataGateway::updateEmployee(const Employee &employee) {
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLAllocHandle(SQL_HANDLE_STMT, dbConn.getConnectionHandle(), &stmt);

    const char *sql =
            "UPDATE Employees SET last_name = ?, first_name = ?, patronymic = ?, address = ?, date_of_birth = ?, "
            "position_id = ?, salary = ? WHERE employee_id = ?";
    ret = SQLPrepare(stmt, (SQLCHAR *) sql, SQL_NTS);

    if (SQL_SUCCEEDED(ret)) {
        SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0,
                         (SQLPOINTER) employee.lastName.c_str(), 0, NULL);
        SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0,
                         (SQLPOINTER) employee.firstName.c_str(), 0, NULL);
        SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0,
                         (SQLPOINTER) employee.patronymic.c_str(), 0, NULL);
        SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 200, 0,
                         (SQLPOINTER) employee.address.c_str(), 0, NULL);
        SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_TYPE_DATE, 0, 0,
                         (SQLPOINTER) employee.dateOfBirth.c_str(), 0, NULL);
        SQLBindParameter(stmt, 6, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0,
                         (SQLPOINTER) &employee.positionId, 0, NULL);
        SQLBindParameter(stmt, 7, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_NUMERIC, 10, 2,
                         (SQLPOINTER) &employee.salary, 0, NULL);
        SQLBindParameter(stmt, 8, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, (SQLPOINTER) &employee.id,
                         0, NULL);

        ret = SQLExecute(stmt);
        if (SQL_SUCCEEDED(ret)) {
            std::cout << "Employee updated successfully." << std::endl;
        } else {
            std::cerr << "Error updating employee." << std::endl;
            dbConn.showError(SQL_HANDLE_STMT, stmt);
        }
    } else {
        std::cerr << "Error preparing statement for updating employee." << std::endl;
        dbConn.showError(SQL_HANDLE_STMT, stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void TableDataGateway::deleteEmployee(int employeeId) {
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLAllocHandle(SQL_HANDLE_STMT, dbConn.getConnectionHandle(), &stmt);

    const char *sql = "DELETE FROM Employees WHERE employee_id = ?";
    ret = SQLPrepare(stmt, (SQLCHAR *) sql, SQL_NTS);

    if (SQL_SUCCEEDED(ret)) {
        SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, (SQLPOINTER) &employeeId, 0,
                         NULL);

        ret = SQLExecute(stmt);
        if (SQL_SUCCEEDED(ret)) {
            std::cout << "Employee deleted successfully." << std::endl;
        } else {
            std::cerr << "Error deleting employee." << std::endl;
            dbConn.showError(SQL_HANDLE_STMT, stmt);
        }
    } else {
        std::cerr << "Error preparing statement for deleting employee." << std::endl;
        dbConn.showError(SQL_HANDLE_STMT, stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

//
// Методы для работы с клиентами
//

std::vector<Client> TableDataGateway::getAllClients() {
    std::vector<Client> clients;

    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLAllocHandle(SQL_HANDLE_STMT, dbConn.getConnectionHandle(), &stmt);

    const char *sql = "SELECT client_id, first_name, last_name, patronymic, passport_data FROM Clients";

    ret = SQLExecDirect(stmt, (SQLCHAR *) sql, SQL_NTS);
    if (SQL_SUCCEEDED(ret)) {
        while (SQLFetch(stmt) == SQL_SUCCESS) {
            Client client;
            char firstName[51], lastName[51], patronymic[51], passportData[101];
            SQLINTEGER clientId;

            SQLGetData(stmt, 1, SQL_C_SLONG, &clientId, 0, NULL);
            SQLGetData(stmt, 2, SQL_C_CHAR, firstName, sizeof(firstName), NULL);
            SQLGetData(stmt, 3, SQL_C_CHAR, lastName, sizeof(lastName), NULL);
            SQLGetData(stmt, 4, SQL_C_CHAR, patronymic, sizeof(patronymic), NULL);
            SQLGetData(stmt, 5, SQL_C_CHAR, passportData, sizeof(passportData), NULL);

            client.id = clientId;
            client.firstName = firstName;
            client.lastName = lastName;
            client.patronymic = patronymic;
            client.passportData = passportData;

            clients.push_back(client);
        }
    } else {
        std::cerr << "Error fetching clients." << std::endl;
        dbConn.showError(SQL_HANDLE_STMT, stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    return clients;
}

Client TableDataGateway::getClientByIndex(int index) {
    std::vector<Client> clients = getAllClients();
    if (index >= 0 && index < clients.size()) {
        return clients[index];
    } else {
        throw std::out_of_range("Invalid client index.");
    }
}

void TableDataGateway::addClient(const Client &client) {
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLAllocHandle(SQL_HANDLE_STMT, dbConn.getConnectionHandle(), &stmt);

    const char *sql =
            "INSERT INTO Clients (first_name, last_name, patronymic, passport_data) VALUES (?, ?, ?, ?)";
    ret = SQLPrepare(stmt, (SQLCHAR *) sql, SQL_NTS);

    if (SQL_SUCCEEDED(ret)) {
        SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0,
                         (SQLPOINTER) client.firstName.c_str(), 0, NULL);
        SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0,
                         (SQLPOINTER) client.lastName.c_str(), 0, NULL);
        SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0,
                         (SQLPOINTER) client.patronymic.c_str(), 0, NULL);
        SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 100, 0,
                         (SQLPOINTER) client.passportData.c_str(), 0, NULL);

        ret = SQLExecute(stmt);
        if (SQL_SUCCEEDED(ret)) {
            std::cout << "Client added successfully." << std::endl;
        } else {
            std::cerr << "Error adding client." << std::endl;
            dbConn.showError(SQL_HANDLE_STMT, stmt);
        }
    } else {
        std::cerr << "Error preparing statement for adding client." << std::endl;
        dbConn.showError(SQL_HANDLE_STMT, stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void TableDataGateway::updateClient(const Client &client) {
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLAllocHandle(SQL_HANDLE_STMT, dbConn.getConnectionHandle(), &stmt);

    const char *sql =
            "UPDATE Clients SET first_name = ?, last_name = ?, patronymic = ?, passport_data = ? WHERE client_id "
            "= ?";
    ret = SQLPrepare(stmt, (SQLCHAR *) sql, SQL_NTS);

    if (SQL_SUCCEEDED(ret)) {
        SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0,
                         (SQLPOINTER) client.firstName.c_str(), 0, NULL);
        SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0,
                         (SQLPOINTER) client.lastName.c_str(), 0, NULL);
        SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0,
                         (SQLPOINTER) client.patronymic.c_str(), 0, NULL);
        SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 100, 0,
                         (SQLPOINTER) client.passportData.c_str(), 0, NULL);
        SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, (SQLPOINTER) &client.id, 0,
                         NULL);

        ret = SQLExecute(stmt);
        if (SQL_SUCCEEDED(ret)) {
            std::cout << "Client updated successfully." << std::endl;
        } else {
            std::cerr << "Error updating client." << std::endl;
            dbConn.showError(SQL_HANDLE_STMT, stmt);
        }
    } else {
        std::cerr << "Error preparing statement for updating client." << std::endl;
        dbConn.showError(SQL_HANDLE_STMT, stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void TableDataGateway::deleteClient(int clientId) {
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLAllocHandle(SQL_HANDLE_STMT, dbConn.getConnectionHandle(), &stmt);

    const char *sql = "DELETE FROM Clients WHERE client_id = ?";
    ret = SQLPrepare(stmt, (SQLCHAR *) sql, SQL_NTS);

    if (SQL_SUCCEEDED(ret)) {
        SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, (SQLPOINTER) &clientId, 0,
                         NULL);

        ret = SQLExecute(stmt);
        if (SQL_SUCCEEDED(ret)) {
            std::cout << "Client deleted successfully." << std::endl;
        } else {
            std::cerr << "Error deleting client." << std::endl;
            dbConn.showError(SQL_HANDLE_STMT, stmt);
        }
    } else {
        std::cerr << "Error preparing statement for deleting client." << std::endl;
        dbConn.showError(SQL_HANDLE_STMT, stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
} // TableDataGateway.cpp

//
// Методы для работы с автомобилями
//

std::vector<Car> TableDataGateway::getAllCars() {
    std::vector<Car> cars;

    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLAllocHandle(SQL_HANDLE_STMT, dbConn.getConnectionHandle(), &stmt);

    const char *sql = R"(
        SELECT car_id, make, model, color, engine_number, registration_number, body_number,
               chassis_number, manufacture_date, mileage, manufacture_price, sale_price, purchase_price,
               technical_certificate_number, technical_certificate_date, expert_id
        FROM Cars
    )";

    ret = SQLExecDirect(stmt, (SQLCHAR *) sql, SQL_NTS);
    if (SQL_SUCCEEDED(ret)) {
        while (SQLFetch(stmt) == SQL_SUCCESS) {
            Car car;
            char make[51], model[51], color[31], engineNumber[51], registrationNumber[21], bodyNumber[51],
                    chassisNumber[51], manufactureDate[11], technicalCertificateNumber[51],
                    technicalCertificateDate[11];
            SQLINTEGER carId, mileage, expertId;
            SQLDOUBLE manufacturePrice, salePrice, purchasePrice;

            SQLGetData(stmt, 1, SQL_C_SLONG, &carId, 0, NULL);
            SQLGetData(stmt, 2, SQL_C_CHAR, make, sizeof(make), NULL);
            SQLGetData(stmt, 3, SQL_C_CHAR, model, sizeof(model), NULL);
            SQLGetData(stmt, 4, SQL_C_CHAR, color, sizeof(color), NULL);
            SQLGetData(stmt, 5, SQL_C_CHAR, engineNumber, sizeof(engineNumber), NULL);
            SQLGetData(stmt, 6, SQL_C_CHAR, registrationNumber, sizeof(registrationNumber), NULL);
            SQLGetData(stmt, 7, SQL_C_CHAR, bodyNumber, sizeof(bodyNumber), NULL);
            SQLGetData(stmt, 8, SQL_C_CHAR, chassisNumber, sizeof(chassisNumber), NULL);
            SQLGetData(stmt, 9, SQL_C_CHAR, manufactureDate, sizeof(manufactureDate), NULL);
            SQLGetData(stmt, 10, SQL_C_SLONG, &mileage, 0, NULL);
            SQLGetData(stmt, 11, SQL_C_DOUBLE, &manufacturePrice, 0, NULL);
            SQLGetData(stmt, 12, SQL_C_DOUBLE, &salePrice, 0, NULL);
            SQLGetData(stmt, 13, SQL_C_DOUBLE, &purchasePrice, 0, NULL);
            SQLGetData(stmt, 14, SQL_C_CHAR, technicalCertificateNumber, sizeof(technicalCertificateNumber),
                       NULL);
            SQLGetData(stmt, 15, SQL_C_CHAR, technicalCertificateDate, sizeof(technicalCertificateDate),
                       NULL);
            SQLGetData(stmt, 16, SQL_C_SLONG, &expertId, 0, NULL);

            car.id = carId;
            car.make = make;
            car.model = model;
            car.color = color;
            car.engineNumber = engineNumber;
            car.registrationNumber = registrationNumber;
            car.bodyNumber = bodyNumber;
            car.chassisNumber = chassisNumber;
            car.manufactureDate = manufactureDate;
            car.mileage = mileage;
            car.manufacturePrice = manufacturePrice;
            car.salePrice = salePrice;
            car.purchasePrice = purchasePrice;
            car.technicalCertificateNumber = technicalCertificateNumber;
            car.technicalCertificateDate = technicalCertificateDate;
            car.expertId = expertId;

            cars.push_back(car);
        }
    } else {
        std::cerr << "Error fetching cars." << std::endl;
        dbConn.showError(SQL_HANDLE_STMT, stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    return cars;
}

Car TableDataGateway::getCarByIndex(int index) {
    std::vector<Car> cars = getAllCars();
    if (index >= 0 && index < cars.size()) {
        return cars[index];
    } else {
        throw std::out_of_range("Invalid car index.");
    }
}

void TableDataGateway::addCar(const Car &car) {
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLAllocHandle(SQL_HANDLE_STMT, dbConn.getConnectionHandle(), &stmt);

    const char *sql = R"(
        INSERT INTO Cars (make, model, color, engine_number, registration_number, body_number,
                          chassis_number, manufacture_date, mileage, manufacture_price, sale_price,
                          purchase_price, technical_certificate_number, technical_certificate_date, expert_id)
        VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
    )";

    ret = SQLPrepare(stmt, (SQLCHAR *) sql, SQL_NTS);

    if (SQL_SUCCEEDED(ret)) {
        // Привязка параметров
        SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0,
                         (SQLPOINTER) car.make.c_str(), 0, NULL);
        SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0,
                         (SQLPOINTER) car.model.c_str(), 0, NULL);
        SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 30, 0,
                         (SQLPOINTER) car.color.c_str(), 0, NULL);
        SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0,
                         (SQLPOINTER) car.engineNumber.c_str(), 0, NULL);
        SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 20, 0,
                         (SQLPOINTER) car.registrationNumber.c_str(), 0, NULL);
        SQLBindParameter(stmt, 6, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0,
                         (SQLPOINTER) car.bodyNumber.c_str(), 0, NULL);
        SQLBindParameter(stmt, 7, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0,
                         (SQLPOINTER) car.chassisNumber.c_str(), 0, NULL);
        SQLBindParameter(stmt, 8, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_TYPE_DATE, 0, 0,
                         (SQLPOINTER) car.manufactureDate.c_str(), 0, NULL);
        SQLBindParameter(stmt, 9, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, (SQLPOINTER) &car.mileage,
                         0, NULL);
        SQLBindParameter(stmt, 10, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_NUMERIC, 10, 2,
                         (SQLPOINTER) &car.manufacturePrice, 0, NULL);
        SQLBindParameter(stmt, 11, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_NUMERIC, 10, 2,
                         (SQLPOINTER) &car.salePrice, 0, NULL);
        SQLBindParameter(stmt, 12, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_NUMERIC, 10, 2,
                         (SQLPOINTER) &car.purchasePrice, 0, NULL);
        SQLBindParameter(stmt, 13, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0,
                         (SQLPOINTER) car.technicalCertificateNumber.c_str(), 0, NULL);
        SQLBindParameter(stmt, 14, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_TYPE_DATE, 0, 0,
                         (SQLPOINTER) car.technicalCertificateDate.c_str(), 0, NULL);
        SQLBindParameter(stmt, 15, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, (SQLPOINTER) &car.expertId,
                         0, NULL);

        ret = SQLExecute(stmt);
        if (SQL_SUCCEEDED(ret)) {
            std::cout << "Car added successfully." << std::endl;
        } else {
            std::cerr << "Error adding car." << std::endl;
            dbConn.showError(SQL_HANDLE_STMT, stmt);
        }
    } else {
        std::cerr << "Error preparing statement for adding car." << std::endl;
        dbConn.showError(SQL_HANDLE_STMT, stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void TableDataGateway::updateCar(const Car &car) {
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLAllocHandle(SQL_HANDLE_STMT, dbConn.getConnectionHandle(), &stmt);

    const char *sql = R"(
        UPDATE Cars SET make = ?, model = ?, color = ?, engine_number = ?, registration_number = ?, body_number = ?,
                        chassis_number = ?, manufacture_date = ?, mileage = ?, manufacture_price = ?, sale_price = ?,
                        purchase_price = ?, technical_certificate_number = ?, technical_certificate_date = ?, expert_id = ?
        WHERE car_id = ?
    )";

    ret = SQLPrepare(stmt, (SQLCHAR *) sql, SQL_NTS);

    if (SQL_SUCCEEDED(ret)) {
        // Привязка параметров (аналогично методу addCar)
        // ...
        // Привязка параметра car_id
        SQLBindParameter(stmt, 16, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, (SQLPOINTER) &car.id, 0,
                         NULL);

        ret = SQLExecute(stmt);
        if (SQL_SUCCEEDED(ret)) {
            std::cout << "Car updated successfully." << std::endl;
        } else {
            std::cerr << "Error updating car." << std::endl;
            dbConn.showError(SQL_HANDLE_STMT, stmt);
        }
    } else {
        std::cerr << "Error preparing statement for updating car." << std::endl;
        dbConn.showError(SQL_HANDLE_STMT, stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void TableDataGateway::deleteCar(int carId) {
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLAllocHandle(SQL_HANDLE_STMT, dbConn.getConnectionHandle(), &stmt);

    const char *sql = "DELETE FROM Cars WHERE car_id = ?";
    ret = SQLPrepare(stmt, (SQLCHAR *) sql, SQL_NTS);

    if (SQL_SUCCEEDED(ret)) {
        SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, (SQLPOINTER) &carId, 0,
                         NULL);

        ret = SQLExecute(stmt);
        if (SQL_SUCCEEDED(ret)) {
            std::cout << "Car deleted successfully." << std::endl;
        } else {
            std::cerr << "Error deleting car." << std::endl;
            dbConn.showError(SQL_HANDLE_STMT, stmt);
        }
    } else {
        std::cerr << "Error preparing statement for deleting car." << std::endl;
        dbConn.showError(SQL_HANDLE_STMT, stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

std::vector<SparePart> TableDataGateway::getAllSpareParts() {
    std::vector<SparePart> spareParts;

    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLAllocHandle(SQL_HANDLE_STMT, dbConn.getConnectionHandle(), &stmt);

    const char *sql = "SELECT spare_part_id, name, make, model, price, stock_quantity FROM SpareParts";

    ret = SQLExecDirect(stmt, (SQLCHAR *) sql, SQL_NTS);
    if (SQL_SUCCEEDED(ret)) {
        while (SQLFetch(stmt) == SQL_SUCCESS) {
            SparePart sp;
            char name[101], make[51], model[51];
            SQLINTEGER sparePartId, stockQuantity;
            SQLDOUBLE price;

            SQLGetData(stmt, 1, SQL_C_SLONG, &sparePartId, 0, NULL);
            SQLGetData(stmt, 2, SQL_C_CHAR, name, sizeof(name), NULL);
            SQLGetData(stmt, 3, SQL_C_CHAR, make, sizeof(make), NULL);
            SQLGetData(stmt, 4, SQL_C_CHAR, model, sizeof(model), NULL);
            SQLGetData(stmt, 5, SQL_C_DOUBLE, &price, 0, NULL);
            SQLGetData(stmt, 6, SQL_C_SLONG, &stockQuantity, 0, NULL);

            sp.id = sparePartId;
            sp.name = name;
            sp.make = make;
            sp.model = model;
            sp.price = price;
            sp.stockQuantity = stockQuantity;

            spareParts.push_back(sp);
        }
    } else {
        std::cerr << "Error fetching spare parts." << std::endl;
        dbConn.showError(SQL_HANDLE_STMT, stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    return spareParts;
}

SparePart TableDataGateway::getSparePartByIndex(int index) {
    std::vector<SparePart> spareParts = getAllSpareParts();
    if (index >= 0 && index < spareParts.size()) {
        return spareParts[index];
    } else {
        throw std::out_of_range("Invalid spare part index.");
    }
}

void TableDataGateway::addSparePart(const SparePart &sparePart) {
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLAllocHandle(SQL_HANDLE_STMT, dbConn.getConnectionHandle(), &stmt);

    const char *sql =
            "INSERT INTO SpareParts (name, make, model, price, stock_quantity) VALUES (?, ?, ?, ?, ?)";
    ret = SQLPrepare(stmt, (SQLCHAR *) sql, SQL_NTS);

    if (SQL_SUCCEEDED(ret)) {
        SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 100, 0,
                         (SQLPOINTER) sparePart.name.c_str(), 0, NULL);
        SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0,
                         (SQLPOINTER) sparePart.make.c_str(), 0, NULL);
        SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0,
                         (SQLPOINTER) sparePart.model.c_str(), 0, NULL);
        SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_NUMERIC, 10, 2,
                         (SQLPOINTER) &sparePart.price, 0, NULL);
        SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0,
                         (SQLPOINTER) &sparePart.stockQuantity, 0, NULL);

        ret = SQLExecute(stmt);
        if (SQL_SUCCEEDED(ret)) {
            std::cout << "Spare part added successfully." << std::endl;
        } else {
            std::cerr << "Error adding spare part." << std::endl;
            dbConn.showError(SQL_HANDLE_STMT, stmt);
        }
    } else {
        std::cerr << "Error preparing statement for adding spare part." << std::endl;
        dbConn.showError(SQL_HANDLE_STMT, stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void TableDataGateway::updateSparePart(const SparePart &sparePart) {
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLAllocHandle(SQL_HANDLE_STMT, dbConn.getConnectionHandle(), &stmt);

    const char *sql =
            "UPDATE SpareParts SET name = ?, make = ?, model = ?, price = ?, stock_quantity = ? WHERE "
            "spare_part_id = ?";
    ret = SQLPrepare(stmt, (SQLCHAR *) sql, SQL_NTS);

    if (SQL_SUCCEEDED(ret)) {
        // Привязка параметров
        SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 100, 0,
                         (SQLPOINTER) sparePart.name.c_str(), 0, NULL);
        SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0,
                         (SQLPOINTER) sparePart.make.c_str(), 0, NULL);
        SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0,
                         (SQLPOINTER) sparePart.model.c_str(), 0, NULL);
        SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_NUMERIC, 10, 2,
                         (SQLPOINTER) &sparePart.price, 0, NULL);
        SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0,
                         (SQLPOINTER) &sparePart.stockQuantity, 0, NULL);
        SQLBindParameter(stmt, 6, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, (SQLPOINTER) &sparePart.id,
                         0, NULL);

        ret = SQLExecute(stmt);
        if (SQL_SUCCEEDED(ret)) {
            std::cout << "Spare part updated successfully." << std::endl;
        } else {
            std::cerr << "Error updating spare part." << std::endl;
            dbConn.showError(SQL_HANDLE_STMT, stmt);
        }
    } else {
        std::cerr << "Error preparing statement for updating spare part." << std::endl;
        dbConn.showError(SQL_HANDLE_STMT, stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void TableDataGateway::deleteSparePart(int sparePartId) {
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLAllocHandle(SQL_HANDLE_STMT, dbConn.getConnectionHandle(), &stmt);

    const char *sql = "DELETE FROM SpareParts WHERE spare_part_id = ?";
    ret = SQLPrepare(stmt, (SQLCHAR *) sql, SQL_NTS);

    if (SQL_SUCCEEDED(ret)) {
        SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, (SQLPOINTER) &sparePartId,
                         0, NULL);

        ret = SQLExecute(stmt);
        if (SQL_SUCCEEDED(ret)) {
            std::cout << "Spare part deleted successfully." << std::endl;
        } else {
            std::cerr << "Error deleting spare part." << std::endl;
            dbConn.showError(SQL_HANDLE_STMT, stmt);
        }
    } else {
        std::cerr << "Error preparing statement for deleting spare part." << std::endl;
        dbConn.showError(SQL_HANDLE_STMT, stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}
