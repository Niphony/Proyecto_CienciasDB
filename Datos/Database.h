#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>

#include "Table.h"

class Database {

private:

    std::vector<Table> tables;

public:

    Database();

    void createTable(
        std::string name,
        std::vector<std::string> columns
    );

    void dropTable(
        std::string name
    );

    Table* getTable(
        std::string name
    );

    void showTables();

    std::vector<Table>& getTables();
};

#endif