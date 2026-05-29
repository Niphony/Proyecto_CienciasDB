#ifndef ArbolAVL
#define ArbolAVL

#include <iostream>
#include "Nodo_AVL.h"

using namespace std;

template<typename N, typename M>
class Arbol {

private:

    Nodo<N,M>* raiz;

    void Orden(Nodo<N,M>* nodo);

    Nodo<N,M>* insertarN(
        Nodo<N,M>* nodo,
        N key,
        M value
    );

public:

    Arbol();

    void insertar(N key, M value);

    void orden();
};



// ============================
// IMPLEMENTACIONES
// ============================

template<typename N, typename M>
Arbol<N,M>::Arbol() {

    raiz = nullptr;
}

template<typename N, typename M>
Nodo<N,M>* Arbol<N,M>::insertarN(
    Nodo<N,M>* nodo,
    N key,
    M value
) {

    // Insercion BST normal primero

    if(nodo == nullptr) {

        return new Nodo<N,M>(key,value);
    }

    if(key < nodo->key) {

        nodo->izq = insertarN(
            nodo->izq,
            key,
            value
        );
    }

    else if(key > nodo->key) {

        nodo->der = insertarN(
            nodo->der,
            key,
            value
        );
    }

    return nodo;
}

template<typename N, typename M>
void Arbol<N,M>::insertar(
    N key,
    M value
) {

    raiz = insertarN(
        raiz,
        key,
        value
    );
}

template<typename N, typename M>
void Arbol<N,M>::Orden(
    Nodo<N,M>* nodo
) {

    if(nodo != nullptr) {

        Orden(nodo->izq);

        cout
            << nodo->key
            << " "
            << nodo->value
            << endl;

        Orden(nodo->der);
    }
}

template<typename N, typename M>
void Arbol<N,M>::orden() {

    Orden(raiz);
}

#endif
