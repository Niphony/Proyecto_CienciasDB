
#include "Database.h"
#include "../Persistencia/Persistencia1.h"

#include <iostream>

Database::Database() {

}

void Database::createTable(
    std::string name,
    std::vector<std::string> columns
) {

    // VERIFICAR SI YA EXISTE

    for(Table& table : tables) {

        if(table.getName() == name) {

            std::cout
                << "La tabla ya existe"
                << std::endl;

            return;
        }
    }

    // CREAR TABLA

    Table newTable(
        name,
        columns
    );

    // GUARDAR TABLA

    tables.push_back(newTable);

    Persistencia1::guardarTabla(
    tables.back()
);
}

void Database::dropTable(
    std::string name
) {

    for(
        int i = 0;
        i < tables.size();
        i++
    ) {

        if(
            tables[i].getName() == name
        ) {

            tables.erase(
                tables.begin() + i
            );

            std::cout
                << "Tabla eliminada"
                << std::endl;

            return;
        }
    }

    std::cout
        << "Tabla no encontrada"
        << std::endl;
}

Table* Database::getTable(
    std::string name
) {

    for(
        int i = 0;
        i < tables.size();
        i++
    ) {

        if(
            tables[i].getName() == name
        ) {

            return &tables[i];
        }
    }

    return nullptr;
}

void Database::showTables() {

    if(tables.empty()) {

        std::cout
            << "No hay tablas"
            << std::endl;

        return;
    }

    std::cout
        << "Tablas:"
        << std::endl;

    for(Table& table : tables) {

        std::cout
            << "- "
            << table.getName()
            << std::endl;
    }
}

std::vector<Table>& Database::getTables() {

    return tables;
}