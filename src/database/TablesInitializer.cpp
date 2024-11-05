// TableDataGateway.cpp
#include <iostream>

#include "TableDataGateway.h"

// Для работы с SQL типами данных
#include <sqltypes.h>

TableDataGateway::TableDataGateway(DatabaseConnection& dbConn) : dbConn(dbConn) {}

//
// Методы для работы с сотрудниками
//

std::vector<Employee> TableDataGateway::getAllEmployees() {
    std::vector<Employee> employees;

    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLAllocHandle(SQL_HANDLE_STMT, dbConn.getConnectionHandle(), &stmt);

    const char* sql =
        "SELECT employee_id, last_name, first_name, patronymic, address, date_of_birth, position_id, salary "
        "FROM Employees";

    ret = SQLExecDirect(stmt, (SQLCHAR*)sql, SQL_NTS);
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

void TableDataGateway::addEmployee(const Employee& employee) {
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLAllocHandle(SQL_HANDLE_STMT, dbConn.getConnectionHandle(), &stmt);

    const char* sql =
        "INSERT INTO Employees (last_name, first_name, patronymic, address, date_of_birth, position_id, "
        "salary) VALUES (?, ?, ?, ?, ?, ?, ?)";
    ret = SQLPrepare(stmt, (SQLCHAR*)sql, SQL_NTS);

    if (SQL_SUCCEEDED(ret)) {
        SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0,
                         (SQLPOINTER)employee.lastName.c_str(), 0, NULL);
        SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0,
                         (SQLPOINTER)employee.firstName.c_str(), 0, NULL);
        SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0,
                         (SQLPOINTER)employee.patronymic.c_str(), 0, NULL);
        SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 200, 0,
                         (SQLPOINTER)employee.address.c_str(), 0, NULL);
        SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_TYPE_DATE, 0, 0,
                         (SQLPOINTER)employee.dateOfBirth.c_str(), 0, NULL);
        SQLBindParameter(stmt, 6, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0,
                         (SQLPOINTER)&employee.positionId, 0, NULL);
        SQLBindParameter(stmt, 7, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_NUMERIC, 10, 2,
                         (SQLPOINTER)&employee.salary, 0, NULL);

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

void TableDataGateway::updateEmployee(const Employee& employee) {
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLAllocHandle(SQL_HANDLE_STMT, dbConn.getConnectionHandle(), &stmt);

    const char* sql =
        "UPDATE Employees SET last_name = ?, first_name = ?, patronymic = ?, address = ?, date_of_birth = ?, "
        "position_id = ?, salary = ? WHERE employee_id = ?";
    ret = SQLPrepare(stmt, (SQLCHAR*)sql, SQL_NTS);

    if (SQL_SUCCEEDED(ret)) {
        SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0,
                         (SQLPOINTER)employee.lastName.c_str(), 0, NULL);
        SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0,
                         (SQLPOINTER)employee.firstName.c_str(), 0, NULL);
        SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0,
                         (SQLPOINTER)employee.patronymic.c_str(), 0, NULL);
        SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 200, 0,
                         (SQLPOINTER)employee.address.c_str(), 0, NULL);
        SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_TYPE_DATE, 0, 0,
                         (SQLPOINTER)employee.dateOfBirth.c_str(), 0, NULL);
        SQLBindParameter(stmt, 6, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0,
                         (SQLPOINTER)&employee.positionId, 0, NULL);
        SQLBindParameter(stmt, 7, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_NUMERIC, 10, 2,
                         (SQLPOINTER)&employee.salary, 0, NULL);
        SQLBindParameter(stmt, 8, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, (SQLPOINTER)&employee.id,
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

    const char* sql = "DELETE FROM Employees WHERE employee_id = ?";
    ret = SQLPrepare(stmt, (SQLCHAR*)sql, SQL_NTS);

    if (SQL_SUCCEEDED(ret)) {
        SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, (SQLPOINTER)&employeeId, 0,
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
// Аналогичные методы для клиентов, автомобилей и запчастей
//

// Методы для работы с клиентами
// Реализация методов getAllClients(), getClientByIndex(), addClient(), updateClient(), deleteClient()

// Методы для работы с автомобилями
// Реализация методов getAllCars(), getCarByIndex(), addCar(), updateCar(), deleteCar()

// Методы для работы с запчастями
// Реализация методов getAllSpareParts(), getSparePartByIndex(), addSparePart(), updateSparePart(),
// deleteSparePart()