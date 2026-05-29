#ifndef ArbolAVL
#define ArbolAVL

#include <iostream>
#include "Nodo_AVL.h"

template<typename N, typename M>

class Arbol {
  
private:

  Nodo<N,M>* raiz; //Usa la clase importada y se definen metodos sobre balance y demas operaciones que se pueden realizar
  
  int altura(Nodo<N,M>* nodo); //Se define apuntador hacia el nodo
  int balance(Nodo<N,M>* nodo);

  Nodo<N,M>* rotarder(Nodo<N,M>* y);
  Nodo<N,M>* rotarizq(Nodo<N,M>* x);

  Nodo<N,M>* insertarN( //Se inserta hacia el nodo con la llave y su valor
      Nodo<N,M>* nodo,
      N key,
      M value
      );
  
  Nodo<N,M>* eliminarN( //Elimina el nodo mediande su llave
    Nodo<N,M>* nodo,
    N key
    );

  Nodo<N,M>* BuscarNodo( //Busca por la llave
    Nodo<N,M>* nodo,
    N key    
      );

  Nodo<N,M>* minVal( //EL min valor apunta a un nuevo nodo
    Nodo<N,M>* nodo
      );

  
  Nodo<N,M>* Orden( //Apunta el orden a un nodo
    Nodo<N,M>* nodo
      );



public:

  Arbol(); //Inicia la clase y se definen los metodos publicos

  void insertar(N key, M value);

  void remove(N key, M value);

  M Buscar(N key);

  void orden();

};



#endif // !ArbolAVL

