#ifndef ArbolAVL
#define ArbolAVL

#include <iostream>
#include "Nodo_AVL.h"

using namespace std;

template<typename N, typename M>
class Arbol {

private:
    Nodo<N,M>* raiz;

    // Métodos privados para el cálculo y balanceo AVL
    int altura(Nodo<N,M>* nodo) {
        if (nodo == nullptr) return 0;
        return nodo->altura;
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    int getBalance(Nodo<N,M>* nodo) {
        if (nodo == nullptr) return 0;
        return altura(nodo->izq) - altura(nodo->der);
    }

    Nodo<N,M>* rotacionDer(Nodo<N,M>* y) { //Rotaciones para balanceo, lo msimo para ambas solo cambia el sentido 
        Nodo<N,M>* x = y->izq;
        Nodo<N,M>* T2 = x->der;

        
        x->der = y;
        y->izq = T2;

        // Actualizar alturas consecutivas
        y->altura = max(altura(y->izq), altura(y->der)) + 1;
        x->altura = max(altura(x->izq), altura(x->der)) + 1;

        
        return x;
    }

    Nodo<N,M>* rotacionIzq(Nodo<N,M>* x) {
        Nodo<N,M>* y = x->der;
        Nodo<N,M>* T2 = y->izq;

        // Realizar rotación
        y->izq = x;
        x->der = T2;

        // Actualizar alturas consecutivas
        x->altura = max(altura(x->izq), altura(x->der)) + 1;
        y->altura = max(altura(y->izq), altura(y->der)) + 1;

        
        return y;
    }

    Nodo<N,M>* minVal(Nodo<N,M>* nodo) {
        Nodo<N,M>* actual = nodo;
        while (actual->izq != nullptr)
            actual = actual->izq;
        return actual;
    }

    // Metodos para la recursion
    void Orden(Nodo<N,M>* nodo);
    Nodo<N,M>* insertarN(Nodo<N,M>* nodo, N key, M value);
    Nodo<N,M>* BuscarN(Nodo<N,M>* nodo, N key);
    Nodo<N,M>* EliminarN(Nodo<N,M>* nodo, N key);

public: //Publicos para poderlos llamar
    Arbol();

    void insertar(N key, M value);
    M* buscar(N key);
    void eliminar(N key);
    void orden();
};


// Aca el resto de la implementacion de cada metodo

template<typename N, typename M>
Arbol<N,M>::Arbol() {
    raiz = nullptr;
}

template<typename N, typename M>
Nodo<N,M>* Arbol<N,M>::insertarN(Nodo<N,M>* nodo, N key, M value) {
    // Insercion binaria
    if (nodo == nullptr) {
        return new Nodo<N,M>(key, value);
    }

    if (key < nodo->key) {
        nodo->izq = insertarN(nodo->izq, key, value);
    }
    else if (key > nodo->key) {
        nodo->der = insertarN(nodo->der, key, value);
    }
    else {
        // Actualiza el registro
        nodo->value = value;
        return nodo;
    }

    // 2. Actualizar la altura de este nodo ancestro
    nodo->altura = 1 + max(altura(nodo->izq), altura(nodo->der));

    // 3. Obtener el factor de balance para verificar si se desbalanceó
    int balance = getBalance(nodo);

    // Caso Izquierda Izquierda (LL)
    if (balance > 1 && key < nodo->izq->key)
        return rotacionDer(nodo);

    // Caso Derecha Derecha (RR)
    if (balance < -1 && key > nodo->der->key)
        return rotacionIzq(nodo);

    // Caso Izquierda Derecha (LR)
    if (balance > 1 && key > nodo->izq->key) {
        nodo->izq = rotacionIzq(nodo->izq);
        return rotacionDer(nodo);
    }

    // Caso Derecha Izquierda (RL)
    if (balance < -1 && key < nodo->der->key) {
        nodo->der = rotacionDer(nodo->der);
        return rotacionIzq(nodo);
    }

    return nodo;
}

template<typename N, typename M>
void Arbol<N,M>::insertar(N key, M value) {
    raiz = insertarN(raiz, key, value);
}

// Búsqueda interna en el árbol
template<typename N, typename M>
Nodo<N,M>* Arbol<N,M>::BuscarN(Nodo<N,M>* nodo, N key) {
    if (nodo == nullptr || nodo->key == key)
        return nodo;

    if (key < nodo->key)
        return BuscarN(nodo->izq, key);

    return BuscarN(nodo->der, key);
}

// Retorna la dirección de memoria del valor para poder hacer SELECT u operaciones directas de UPDATE
template<typename N, typename M>
M* Arbol<N,M>::buscar(N key) {
    Nodo<N,M>* res = BuscarN(raiz, key);
    if (res != nullptr) return &(res->value);
    return nullptr;
}

// Eliminación con re-balanceo estructural AVL
template<typename N, typename M>
Nodo<N,M>* Arbol<N,M>::EliminarN(Nodo<N,M>* nodo, N key) {
    // Eliminacion por nodo
    if (nodo == nullptr)
        return nodo;

    if (key < nodo->key) { //Hacia la eleccion de la llave
        nodo->izq = EliminarN(nodo->izq, key);
    }
    else if (key > nodo->key) {
        nodo->der = EliminarN(nodo->der, key);
    }
    else {
        
        if ((nodo->izq == nullptr) || (nodo->der == nullptr)) {
            Nodo<N,M>* temp = nodo->izq ? nodo->izq : nodo->der;

            if (temp == nullptr) { // Caso sin hijos
                temp = nodo;
                nodo = nullptr;
            }
            else { // Caso con un único hijo superviviente
                Nodo<N,M>* viejo = nodo;
                nodo = temp; 
                temp = viejo;
            }
            delete temp;
        }
        else {
            // Caso con dos hijos: obtener el sucesor inorden (mínimo del subárbol derecho)
            Nodo<N,M>* temp = minVal(nodo->der);

            // Reemplazar la información clave-valor por la del sucesor
            nodo->key = temp->key;
            nodo->value = temp->value;

            // Eliminar físicamente el sucesor inorden duplicado
            nodo->der = EliminarN(nodo->der, temp->key);
        }
    }

    // Si el subárbol quedó vacío tras eliminar la única hoja existente, retornamos
    if (nodo == nullptr)
        return nodo;

    // 2. Actualizar la altura del nodo actual
    nodo->altura = 1 + max(altura(nodo->izq), altura(nodo->der));

    // 3. Obtener el factor de balance del nodo actual
    int balance = getBalance(nodo);

    // Caso Izquierda Izquierda (LL)
    if (balance > 1 && getBalance(nodo->izq) >= 0)
        return rotacionDer(nodo);

    // Caso Izquierda Derecha (LR)
    if (balance > 1 && getBalance(nodo->izq) < 0) {
        nodo->izq = rotacionIzq(nodo->izq);
        return rotacionDer(nodo);
    }

    // Caso Derecha Derecha (RR)
    if (balance < -1 && getBalance(nodo->der) <= 0)
        return rotacionIzq(nodo);

    // Caso Derecha Izquierda (RL)
    if (balance < -1 && getBalance(nodo->der) > 0) {
        nodo->der = rotacionDer(nodo->der);
        return rotacionIzq(nodo);
    }

    return nodo;
}

template<typename N, typename M>
void Arbol<N,M>::eliminar(N key) {
    raiz = EliminarN(raiz, key);
}

// Recorrido Inorder recursivo interno
template<typename N, typename M>
void Arbol<N,M>::Orden(Nodo<N,M>* nodo) {
    if (nodo != nullptr) {
        Orden(nodo->izq);
        cout << nodo->key << " " << nodo->value << endl;
        Orden(nodo->der);
    }
}

template<typename N, typename M>
void Arbol<N,M>::orden() {
    Orden(raiz);
}

#endif
