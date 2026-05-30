#ifndef PERSISTENCIA1_H
#define PERSISTENCIA1_H

#include "../Datos/Table.h"

class Persistencia1{

public:

    static void guardarTabla(
        Table& table
    );

    static void cargarTabla(
        Table& table
    );
};

#endif