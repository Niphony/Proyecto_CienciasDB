#ifndef PERSISTENCIA
#define PERSISTENCIA

#include <iostream>
#include <fstream>
#include <sstream>


#include "Nodo_AVL.h"

using namespace std;

template<typename N, typename M>
class Persistencia {

public:

    template<typename ArbolTipo>// Método para guardar cualquier árbol que tenga un método obtenerRaiz() y nodos con key y value
    static void guardar(ArbolTipo& arbol, string archivo) { 
        string temporal = archivo + ".tmp";// Archivo temporal para escribir antes de reemplazar el original
        ofstream file(temporal);

        // VALIDAR APERTURA
        if(!file.is_open()) {
            cout
                << "-> Error abriendo archivo temporal.\n";
            return;
        }

        // GUARDAR DATOS
        guardarRecursivo(arbol.obtenerRaiz(), file);

        file.flush();// Asegurar que todos los datos se escriban en el archivo

        // VALIDAR ERRORES
        if(file.fail()) {
            cout << "-> Error escribiendo persistencia.\n";
            file.close();// Cerrar el archivo antes de eliminar el temporal
            remove(temporal.c_str()); // Eliminar el archivo temporal si hubo un error de escritura);

            return;
        }
        file.close();// Cerrar el archivo antes de reemplazar el original

        // REEMPLAZAR ORIGINAL
        remove(archivo.c_str());// Eliminar el archivo original antes de renombrar el temporal, para evitar conflictos en sistemas que no permiten renombrar sobre un archivo existente

        if(rename(temporal.c_str(), archivo.c_str() ) != 0) {

        cout << "-> Error reemplazando archivo original.\n";

    return;
}
    }

    // CARGAR

    template<typename ArbolTipo>// Método para cargar cualquier árbol que tenga un método insertar(N key, M value)
    static void cargar(ArbolTipo& arbol, string archivo) { 
        ifstream file(archivo);

        if(!file.is_open()) {// Si el archivo no existe, no es un error, simplemente no hay datos previos que cargar
            return;
        }
        string linea;

        // LEER

        while(getline(file,linea)) {// Leer línea por línea, cada línea representa un nodo con formato "key,value"

            stringstream ss(linea);

            string keyStr;
            string value;

            getline(ss,keyStr,',');

            getline(ss,value);

            N key = stoi(keyStr);

            arbol.insertar(
                key,
                value
            );
        }

        file.close();
    }

private:

    // GUARDAR RECURSIVO

    static void guardarRecursivo(Nodo<N,M>* nodo, ofstream& file) {// Recorrido Inorder para guardar en orden de claves (N)

        if(nodo != nullptr) {

            guardarRecursivo(nodo->izq, file);// Guardar el nodo actual después de procesar el subárbol izquierdo

            file
                << nodo->key
                << ","
                << nodo->value
                << endl;

            guardarRecursivo(nodo->der, file);// Guardar el nodo actual después de procesar el subárbol derecho  );
        }
    }
};

#endif
