
#include "Table.h"
#include "../Persistencia/Persistencia1.h"

#include <iostream>

Table::Table() {

}

Table::Table(
    std::string name,
    std::vector<std::string> columns
) {

    this->name = name;

    this->columns = columns;
}

void Table::insert(
    std::vector<std::string> values
) {

    // VALIDAR CANTIDAD DE COLUMNAS

    if(
        values.size() != columns.size()
    ) {

        std::cout
            << "Cantidad de valores invalida"
            << std::endl;

        return;
    }

    // CREAR RECORD

    Record record;

    record.values = values;

    // AGREGAR AL VECTOR

    records.push_back(record);

    // POSICION EN VECTOR

    int position =
        records.size() - 1;

    // CLAVE PRIMARIA

    int key;
    
    try {
    key = stoi(values[0]);
}
catch(...) {
    cout << "Clave primaria inválida";
    return;
}

    // INSERTAR EN AVL

    primaryIndex.insertar(
        key,
        position
    );
    Persistencia1::guardarTabla(
    *this
    );
}

Record* Table::select(int key) {

    int* pos =
        primaryIndex.buscar(key);

    if(pos == nullptr) {
        return nullptr;
    }

    int position = *pos;

    if(
        position < 0 ||
        position >= records.size()
    ) {
        return nullptr;
    }

    if(records[position].deleted) {
        return nullptr;
    }

    return &records[position];
}

void Table::update(
    int key,
    int columnIndex,
    std::string newValue
) {

    Record* record =
        select(key);

    if(record == nullptr) {

        std::cout
            << "Registro no encontrado"
            << std::endl;

        return;
    }

    if(
        columnIndex < 0 ||
        columnIndex >= record->values.size()
    ) {

        std::cout
            << "Indice de columna invalido"
            << std::endl;

        return;
    }

    record->values[columnIndex] =
        newValue;
    
    Persistencia1::guardarTabla(
    *this
    );    
}

void Table::remove(
    int key
) {

    try {
            int* pos =
            primaryIndex.buscar(key);

            if(pos == nullptr) {

            std::cout
             << "Registro no encontrado"
            << std::endl;

            return;
}

int position = *pos;

        records[position].deleted =
            true;

        primaryIndex.eliminar(key);

        Persistencia1::guardarTabla(
        *this
        );
    }

    catch(...) {

        std::cout
            << "Error eliminando registro"
            << std::endl;
    }
}

void Table::print() {

    // IMPRIMIR COLUMNAS

    for(
        std::string column :
        columns
    ) {

        std::cout
            << column
            << "\t";
    }

    std::cout << std::endl;

    // IMPRIMIR REGISTROS

    for(
        Record& record :
        records
    ) {

        if(record.deleted) {

            continue;
        }

        for(
            std::string value :
            record.values
        ) {

            std::cout
                << value
                << "\t";
        }

        std::cout << std::endl;
    }
}

std::string Table::getName() {

    return name;
}

std::vector<Record>& Table::getRecords() {

    return records;
}

std::vector<std::string>& Table::getColumns() {

    return columns;
}
void Table::rebuildIndex() {

    for(
        int i = 0;
        i < records.size();
        i++
    ) {

        if(records[i].deleted) {
            continue;
        }

        int key =
            stoi(records[i].values[0]);

        primaryIndex.insertar(
            key,
            i
        );
    }
}