// TablesInitializer.cpp
#include <iostream>

#include "TablesInitializer.h"

TablesInitializer::TablesInitializer(DatabaseConnection& dbConn) : dbConn(dbConn) {}

void TablesInitializer::initializeTables() {
    createPositionsTable();
    createEmployeesTable();
    createEmployeeMovementsTable();
    createClientsTable();
    createDocumentsTable();
    createCarsTable();
    createSalesTable();
    createPurchasesTable();
    createSparePartsTable();
}

void TablesInitializer::createPositionsTable() {
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLAllocHandle(SQL_HANDLE_STMT, dbConn.getConnectionHandle(), &stmt);

    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS Positions (
            position_id SERIAL PRIMARY KEY,
            position_name VARCHAR(100) NOT NULL
        )
    )";

    ret = SQLExecDirect(stmt, (SQLCHAR*)sql, SQL_NTS);
    if (SQL_SUCCEEDED(ret)) {
        std::cout << "Positions table is ready." << std::endl;
    } else {
        std::cerr << "Error creating Positions table." << std::endl;
        dbConn.showError(SQL_HANDLE_STMT, stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void TablesInitializer::createEmployeesTable() {
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLAllocHandle(SQL_HANDLE_STMT, dbConn.getConnectionHandle(), &stmt);

    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS Employees (
            employee_id SERIAL PRIMARY KEY,
            last_name VARCHAR(50) NOT NULL,
            first_name VARCHAR(50) NOT NULL,
            patronymic VARCHAR(50),
            address VARCHAR(200),
            date_of_birth DATE,
            position_id INT REFERENCES Positions(position_id),
            salary NUMERIC(10,2)
        )
    )";

    ret = SQLExecDirect(stmt, (SQLCHAR*)sql, SQL_NTS);
    if (SQL_SUCCEEDED(ret)) {
        std::cout << "Employees table is ready." << std::endl;
    } else {
        std::cerr << "Error creating Employees table." << std::endl;
        dbConn.showError(SQL_HANDLE_STMT, stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void TablesInitializer::createEmployeeMovementsTable() {
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLAllocHandle(SQL_HANDLE_STMT, dbConn.getConnectionHandle(), &stmt);

    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS EmployeeMovements (
            movement_id SERIAL PRIMARY KEY,
            employee_id INT REFERENCES Employees(employee_id),
            position_id INT REFERENCES Positions(position_id),
            reason VARCHAR(200),
            order_number VARCHAR(50),
            order_date DATE
        )
    )";

    ret = SQLExecDirect(stmt, (SQLCHAR*)sql, SQL_NTS);
    if (SQL_SUCCEEDED(ret)) {
        std::cout << "EmployeeMovements table is ready." << std::endl;
    } else {
        std::cerr << "Error creating EmployeeMovements table." << std::endl;
        dbConn.showError(SQL_HANDLE_STMT, stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void TablesInitializer::createClientsTable() {
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLAllocHandle(SQL_HANDLE_STMT, dbConn.getConnectionHandle(), &stmt);

    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS Clients (
            client_id SERIAL PRIMARY KEY,
            first_name VARCHAR(50) NOT NULL,
            last_name VARCHAR(50) NOT NULL,
            patronymic VARCHAR(50),
            passport_data VARCHAR(100) NOT NULL
        )
    )";

    ret = SQLExecDirect(stmt, (SQLCHAR*)sql, SQL_NTS);
    if (SQL_SUCCEEDED(ret)) {
        std::cout << "Clients table is ready." << std::endl;
    } else {
        std::cerr << "Error creating Clients table." << std::endl;
        dbConn.showError(SQL_HANDLE_STMT, stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void TablesInitializer::createDocumentsTable() {
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLAllocHandle(SQL_HANDLE_STMT, dbConn.getConnectionHandle(), &stmt);

    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS Documents (
            document_id SERIAL PRIMARY KEY,
            document_number VARCHAR(50),
            document_name VARCHAR(100),
            issue_date DATE,
            issued_by VARCHAR(100)
        )
    )";

    ret = SQLExecDirect(stmt, (SQLCHAR*)sql, SQL_NTS);
    if (SQL_SUCCEEDED(ret)) {
        std::cout << "Documents table is ready." << std::endl;
    } else {
        std::cerr << "Error creating Documents table." << std::endl;
        dbConn.showError(SQL_HANDLE_STMT, stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void TablesInitializer::createCarsTable() {
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLAllocHandle(SQL_HANDLE_STMT, dbConn.getConnectionHandle(), &stmt);

    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS Cars (
            car_id SERIAL PRIMARY KEY,
            make VARCHAR(50),
            model VARCHAR(50),
            color VARCHAR(30),
            engine_number VARCHAR(50),
            registration_number VARCHAR(20),
            body_number VARCHAR(50),
            chassis_number VARCHAR(50),
            manufacture_date DATE,
            mileage INT,
            manufacture_price NUMERIC(10,2),
            sale_price NUMERIC(10,2),
            purchase_price NUMERIC(10,2),
            technical_certificate_number VARCHAR(50),
            technical_certificate_date DATE,
            expert_id INT REFERENCES Employees(employee_id)
        )
    )";

    ret = SQLExecDirect(stmt, (SQLCHAR*)sql, SQL_NTS);
    if (SQL_SUCCEEDED(ret)) {
        std::cout << "Cars table is ready." << std::endl;
    } else {
        std::cerr << "Error creating Cars table." << std::endl;
        dbConn.showError(SQL_HANDLE_STMT, stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void TablesInitializer::createSalesTable() {
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLAllocHandle(SQL_HANDLE_STMT, dbConn.getConnectionHandle(), &stmt);

    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS Sales (
            sale_id SERIAL PRIMARY KEY,
            client_id INT REFERENCES Clients(client_id),
            car_id INT REFERENCES Cars(car_id),
            sale_date DATE,
            account_number VARCHAR(50),
            payment_method VARCHAR(50)
        )
    )";

    ret = SQLExecDirect(stmt, (SQLCHAR*)sql, SQL_NTS);
    if (SQL_SUCCEEDED(ret)) {
        std::cout << "Sales table is ready." << std::endl;
    } else {
        std::cerr << "Error creating Sales table." << std::endl;
        dbConn.showError(SQL_HANDLE_STMT, stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void TablesInitializer::createPurchasesTable() {
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLAllocHandle(SQL_HANDLE_STMT, dbConn.getConnectionHandle(), &stmt);

    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS Purchases (
            purchase_id SERIAL PRIMARY KEY,
            client_id INT REFERENCES Clients(client_id),
            car_id INT REFERENCES Cars(car_id),
            purchase_date DATE,
            document_id INT REFERENCES Documents(document_id)
        )
    )";

    ret = SQLExecDirect(stmt, (SQLCHAR*)sql, SQL_NTS);
    if (SQL_SUCCEEDED(ret)) {
        std::cout << "Purchases table is ready." << std::endl;
    } else {
        std::cerr << "Error creating Purchases table." << std::endl;
        dbConn.showError(SQL_HANDLE_STMT, stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void TablesInitializer::createSparePartsTable() {
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLAllocHandle(SQL_HANDLE_STMT, dbConn.getConnectionHandle(), &stmt);

    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS SpareParts (
            spare_part_id SERIAL PRIMARY KEY,
            name VARCHAR(100),
            make VARCHAR(50),
            model VARCHAR(50),
            price NUMERIC(10,2),
            stock_quantity INT
        )
    )";

    ret = SQLExecDirect(stmt, (SQLCHAR*)sql, SQL_NTS);
    if (SQL_SUCCEEDED(ret)) {
        std::cout << "SpareParts table is ready." << std::endl;
    } else {
        std::cerr << "Error creating SpareParts table." << std::endl;
        dbConn.showError(SQL_HANDLE_STMT, stmt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}