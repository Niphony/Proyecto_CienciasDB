#ifndef RECORD_H
#define RECORD_H

#include <vector>
#include <string>

class Record {
//se define la clase publica para poder acceder 
public:
    //se crea un vector values donde se almacenaran los datos que se proporciones y esto definira el nuemero de columnas
    std::vector<std::string> values;
    //se ingresa para ver si la fila sue eliminada o no esta en uso 
    bool deleted;
    //constructor(se inicializa apenas se llama la clase)
    Record() {
        //se inicializa el la variable en falso para que aparezca activa
        deleted = false;
    }
};

#endif