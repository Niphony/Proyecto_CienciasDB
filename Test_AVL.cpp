
#include <iostream>
#include <string>
#include <sstream>


#include "Arbol_AVL.h"
#include "Persistencia.h"

using namespace std;

int main() {
    // Instanciamos el índice usando 'int' para la key
    // y 'string' para guardar el contenido completo del registro.
    Arbol<int, string> db;

    Persistencia<int,string>::cargar(db,"personas.csv"); // Carga inicial desde el archivo CSV (si existe)

    string lineaCompleta;
    
  
    cout << "====================================================" << endl;
    cout << "                 AVL DATABASE CLI                   " << endl;
    cout << "====================================================" << endl;
    cout << "Comandos:" << endl;
    cout << "  insertar <id> <texto o datos del registro>" << endl;
    cout << "  seleccionar <id>  o sel <id>" << endl;
    cout << "  actualizar o act <id> <nuevos datos>" << endl;
    cout << "  borrar <id>" << endl;
    cout << "  orden" << endl;
    cout << "  salir o ctrl+c" << endl;
    cout << "====================================================" << endl << endl;

    while (true) {
      cout << "db> ";
      if (!getline(cin, lineaCompleta)){
        
        break;

      }
    

        if (lineaCompleta.empty()) continue; // Si presiona Enter vacío, vuelve a preguntar
        stringstream ss(lineaCompleta);
        string comando;
        ss >> comando; // Extrae la primera palabra clave (el comando)

        
        //
        if (comando == "salir" || comando == "exit") {
            break;
        }
        else if (comando == "insertar") {
            int id;
            if (ss >> id) {
                string registro; //Para tomar la linea
                getline(ss, registro); 
                

                if (registro.empty()) {
                    cout << "-> Error: El contenido del registro no puede estar vacío." << endl;
                } else {
                    db.insertar(id, registro);
                    Persistencia<int,string>::guardar(db, "personas.csv");// Guarda después de cada inserción para mantener la persistencia actualizada
                    cout << "-> OK: Registro [" << id << "] indexado en el árbol AVL." << endl;
                }
            } else {
                cout << "-> Error de sintaxis: INSERT <id_entero> <datos del registro>" << endl;
            }
        }
        else if (comando == "seleccionar" || comando == "sel") {
            int id;
            if (ss >> id) {
                string* registro = db.buscar(id);
                if (registro != nullptr) {
                    cout << "-> Encontrado: [" << id << "] => " << *registro << endl;
                } else {
                    cout << "-> Error: El ID " << id << " no esta en el inidice." << endl;
                }
            } else {
                cout << "-> Error de sintaxis, coloca bien el comando: " << comando << " <id_entero>" << endl;
            }
        }
        else if (comando == "actualizar" || comando == "act") {
            int id;
            if (ss >> id) {
                string nuevosDatos;
                getline(ss, nuevosDatos);
                

                if (nuevosDatos.empty()) {
                    cout << "-> Error: No hay nada nuevo." << endl;
                } else {
                    string* registro = db.buscar(id);
                    if (registro != nullptr) {
                        *registro = nuevosDatos; // Modificación directa sobre el nodo usando el puntero
                        Persistencia<int,string>::guardar(db, "personas.csv");// Guarda después de cada actualización para mantener la persistencia actualizada
                        cout << "-> OK: Registro [" << id << "] actualizado." << endl;
                    } else {
                        cout << "-> Error: El ID " << id << " no existe. Use insertar si desea crearlo." << endl;
                    }
                }
            } else {
                cout << "-> Error de sintaxis: actualizar | act <id_entero> <nuevos datos>" << endl;
            }
        }
        else if (comando == "borrar") {
            int id;
            if (ss >> id) {
                string* registro = db.buscar(id);
                if (registro != nullptr) {
                    db.eliminar(id); // Ejecuta el quitar tal y el rebalanceo AVL
                    Persistencia<int,string>::guardar(db, "personas.csv");// Guarda después de cada eliminación para mantener la persistencia actualizada
                    cout << "-> OK: Registro [" << id << "] eliminado." << endl;
                } else {
                    cout << "-> Error: No se puede eliminar algo que no exite. "<< id <<" no esta" << endl;
                }
            } else {
                cout << "-> Error de sintaxis: borrar <id_entero>" << endl;
            }
        }
        else if (comando == "orden") {
            cout << "--- Contenido de la DB (Ordenado por Clave N) ---" << endl;
            db.orden();
            cout << "--------------------------------------------------------" << endl;
        }
        else {
            cout << "-> Error: Comando '" << comando << "' no reconocido por el sistema." << endl;
        }    
      
    }

    return 0;
}
