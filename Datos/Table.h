#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <string>

#include "../Estructura/Arbol_AVL.h"
#include "Record.h"

class Table {

private:

    std::string name;

    std::vector<std::string> columns;

    std::vector<Record> records;

    Arbol<int,int> primaryIndex;

public:

    Table();

    Table(
        std::string name,
        std::vector<std::string> columns
    );

    void insert(
        std::vector<std::string> values
    );

    Record* select(int key);

    void update(
        int key,
        int columnIndex,
        std::string newValue
    );

    void remove(int key);

    void print();

    std::string getName();

    std::vector<Record>& getRecords();

    std::vector<std::string>& getColumns();

    void rebuildIndex();
};

#endif