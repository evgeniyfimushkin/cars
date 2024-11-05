// TablesInitializer.h
#pragma once

#include "DatabaseConnection.h"

class TablesInitializer {
   public:
    TablesInitializer(DatabaseConnection& dbConn);
    void initializeTables();

   private:
    DatabaseConnection& dbConn;

    void createPositionsTable();
    void createEmployeesTable();
    void createEmployeeMovementsTable();
    void createClientsTable();
    void createDocumentsTable();
    void createCarsTable();
    void createSalesTable();
    void createPurchasesTable();
    void createSparePartsTable();
};