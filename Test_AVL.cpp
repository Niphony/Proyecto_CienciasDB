#include <iostream>
#include <string>

#include "Arbol_AVL.h"

using namespace std;

int main() {

    Arbol<int,string> arbol;

    // =========================
    // INSERTS
    // =========================

    cout << "Insertando nodos...\n";

    arbol.insertar(10, "Juan");
    arbol.insertar(20, "Ana");
    arbol.insertar(5, "Pedro");
    arbol.insertar(15, "Maria");
    arbol.insertar(30, "Carlos");

    // =========================
    // RECORRIDO
    // =========================

    cout << "\nRecorrido inorder:\n";

    arbol.orden();

    // =========================
    // BUSQUEDA
    // =========================
    //
    // cout << "\nBusqueda:\n";
    //
    // cout << "Key 15 -> ";
    // cout << arbol.Buscar(15) << endl;
    //
    // cout << "Key 5 -> ";
    // cout << arbol.Buscar(5) << endl;
    //
    // // =========================
    // DELETE
    // =========================
    //
    // cout << "\nEliminando key 20...\n";
    //
    // arbol.remove(20);
    //
    // =========================
    // RECORRIDO FINAL
    // =========================
//
    // cout << "\nRecorrido despues de eliminar:\n";
    //
    // arbol.orden();
    //
    return 0;
}
