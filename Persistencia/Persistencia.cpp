#include "Persistencia1.h"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

/*
    GUARDA UNA TABLA EN:

    personas.csv
    productos.csv
    clientes.csv

    etc.
*/
void Persistencia1::guardarTabla(
    Table& table
) {

    string archivo =
        table.getName() + ".csv";

    ofstream file(archivo);

    if(!file.is_open()) {

        cout
            << "Error abriendo "
            << archivo
            << endl;

        return;
    }

    // =====================
    // GUARDAR COLUMNAS
    // =====================

    vector<string>& columns =
        table.getColumns();

    for(
        int i = 0;
        i < columns.size();
        i++
    ) {

        file << columns[i];

        if(
            i <
            columns.size() - 1
        ) {
            file << ",";
        }
    }

    file << endl;

    // =====================
    // GUARDAR REGISTROS
    // =====================

    vector<Record>& records =
        table.getRecords();

    for(
        Record& record :
        records
    ) {

        if(record.deleted) {
            continue;
        }

        for(
            int i = 0;
            i < record.values.size();
            i++
        ) {

            file
                << record.values[i];

            if(
                i <
                record.values.size()-1
            ) {
                file << ",";
            }
        }

        file << endl;
    }

    file.close();

    cout
        << "Tabla "
        << table.getName()
        << " guardada correctamente."
        << endl;
}

/*
    CARGA UNA TABLA DESDE:

    personas.csv
*/
void Persistencia1::cargarTabla(
    Table& table
) {

    string archivo =
        table.getName() + ".csv";

    ifstream file(archivo);

    if(!file.is_open()) {

        cout
            << "No existe "
            << archivo
            << ". Se creará al guardar."
            << endl;

        return;
    }

    string line;

    // =====================
    // SALTAR ENCABEZADO
    // =====================

    getline(
        file,
        line
    );

    // =====================
    // LEER REGISTROS
    // =====================

    while(
        getline(
            file,
            line
        )
    ) {

        if(line.empty()) {
            continue;
        }

        stringstream ss(line);

        Record record;

        string value;

        while(
            getline(
                ss,
                value,
                ','
            )
        ) {

            record.values.push_back(
                value
            );
        }

        table.getRecords().push_back(
            record
        );
    }

    file.close();

    // =====================
    // RECONSTRUIR AVL
    // =====================

    table.rebuildIndex();

    cout
        << "Tabla "
        << table.getName()
        << " cargada correctamente."
        << endl;
}