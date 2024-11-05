// DatabaseConnection.h
#pragma once

#include <sql.h>
#include <sqlext.h>

#include <string>

class DatabaseConnection {
   public:
    DatabaseConnection(const std::string& connectionString);
    ~DatabaseConnection();

    bool connect();
    void disconnect();
    bool isConnected() const;

    SQLHDBC getConnectionHandle() const;

    void showError(unsigned int handleType, const SQLHANDLE& handle);

   private:
    SQLHENV env;
    SQLHDBC dbc;
    std::string connectionString;
    bool connected;
};