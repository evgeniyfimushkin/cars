// DatabaseConnection.cpp
#include "DatabaseConnection.h"

#include <iostream>

DatabaseConnection::DatabaseConnection(const std::string& connStr)
    : env(SQL_NULL_HENV), dbc(SQL_NULL_HDBC), connectionString(connStr), connected(false) {}

DatabaseConnection::~DatabaseConnection() { disconnect(); }

bool DatabaseConnection::connect() {
    SQLRETURN ret;

    // Allocate environment handle
    ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
    if (!SQL_SUCCEEDED(ret)) {
        std::cerr << "Error allocating environment handle." << std::endl;
        return false;
    }

    // Set the ODBC version environment attribute
    ret = SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    if (!SQL_SUCCEEDED(ret)) {
        std::cerr << "Error setting ODBC version." << std::endl;
        return false;
    }

    // Allocate connection handle
    ret = SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        std::cerr << "Error allocating connection handle." << std::endl;
        return false;
    }

    // Connect to the data source
    SQLCHAR outConnStr[1024];
    SQLSMALLINT outConnStrLen;

    ret = SQLDriverConnect(dbc, NULL, (SQLCHAR*)connectionString.c_str(), SQL_NTS, outConnStr,
                           sizeof(outConnStr), &outConnStrLen, SQL_DRIVER_COMPLETE);

    if (SQL_SUCCEEDED(ret)) {
        std::cout << "Connected to the database." << std::endl;
        connected = true;
        return true;
    } else {
        std::cerr << "Failed to connect to the database." << std::endl;
        showError(SQL_HANDLE_DBC, dbc);
        disconnect();
        return false;
    }
}

void DatabaseConnection::disconnect() {
    if (connected) {
        SQLDisconnect(dbc);
        connected = false;
    }
    if (dbc != SQL_NULL_HDBC) {
        SQLFreeHandle(SQL_HANDLE_DBC, dbc);
        dbc = SQL_NULL_HDBC;
    }
    if (env != SQL_NULL_HENV) {
        SQLFreeHandle(SQL_HANDLE_ENV, env);
        env = SQL_NULL_HENV;
    }
}

bool DatabaseConnection::isConnected() const { return connected; }

SQLHDBC DatabaseConnection::getConnectionHandle() const { return dbc; }

void DatabaseConnection::showError(unsigned int handleType, const SQLHANDLE& handle) {
    SQLCHAR SQLState[1024];
    SQLCHAR message[1024];
    if (SQLGetDiagRec(handleType, handle, 1, SQLState, NULL, message, 1024, NULL) == SQL_SUCCESS) {
        std::cerr << "ODBC Error: " << message << " SQLState: " << SQLState << std::endl;
    }
}