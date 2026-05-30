# AVL Database CLI

Esta es una aplicación de base de datos de consola simple que utiliza un **Árbol AVL** para la gestión eficiente de datos (clave-valor). El sistema incluye persistencia en archivos CSV y operaciones básicas CRUD.

## Requisitos Previos

* Compilador de C++ compatible con el estándar C++11 o superior.
* Los archivos de dataset (archivos `.csv`) deben estar ubicados **en la misma carpeta que el ejecutable del proyecto** para que la persistencia funcione correctamente.



## Instrucciones de Ejecución

1. **Compilación**: Asegúrate de tener todos los archivos fuente (`Arbol_AVL.h`, `Nodo_AVL.h`, `Persistencia.h` y el archivo principal `.cpp`) en el mismo directorio. Compila utilizando tu compilador preferido (ej. g++):
```bash
g++ main.cpp -o avl_db

```



```

2.  **Ejecución**: Ejecuta el programa desde la terminal:
    ```bash
./avl_db

```

## Comandos Disponibles

Una vez dentro de la interfaz `db>`, puedes utilizar los siguientes comandos:

| Comando | Descripción | Ejemplo |
| --- | --- | --- |
| `insertar` | Agrega un nuevo registro con su ID y datos.

 | `db> insertar 101 Juan Perez` |
| `seleccionar` / `sel` | Busca un registro específico por su ID.

 | `db> sel 101` |
| `actualizar` / `act` | Modifica los datos de un ID existente.

 | `db> act 101 Juan Alberto Perez` |
| `borrar` | Elimina un registro existente del árbol.

 | `db> borrar 101` |
| `orden` | Muestra todos los registros ordenados por clave.

 | `db> orden` |
| `salir` | Termina la ejecución del programa.

 | `db> salir` |

## Persistencia

* **Datasets**: El programa carga automáticamente los datos desde un archivo llamado `personas.csv` al iniciar.


* **Sincronización**: Cada vez que realizas una inserción, actualización o eliminación, el sistema actualiza automáticamente el archivo `personas.csv` en la carpeta del proyecto para asegurar que los cambios se guarden.


* **Nota**: Asegúrate de que los archivos de datos tengan el formato `key,value` (ejemplo: `1, Ejemplo de dato`).


