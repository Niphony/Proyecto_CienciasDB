#ifndef NodoAVL
#define NodoAVL





template<typename N, typename M> //Plantilla
                                 //
class Nodo{
public:  
  N key; //Para poder buscar desde el key, coincidencias y demas
  M value; //Valor asociado - Esquema Clave - Valor

  int altura;

  //Los correspondientes de cada lado

  Nodo<N,M> *izq; 
  Nodo<N,M> *der;

  Nodo(N key,M value){

    //Apuntamos al valor y asignamos el tipo 
    this->key = key;
    this->value = value;

    altura = 1;

    izq = nullptr; //para dejar referencia a algo vacio
    der = nullptr;
  }


};



#endif
