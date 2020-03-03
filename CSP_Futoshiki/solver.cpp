#include "solver.h"

Solver::Solver(QObject *parent) : QObject(parent) {
    backTrackingJumps = 0;
}

//__________________________________________________________________BACKTRACKING

/**
 * @brief cumpleRestricciones Comprueba que un valor cumpla todas las restricciones
 * @param tablero Tablero cargado que se va a resolver [0..size-1][0..size-1]
 * @param fill Fila de la casilla de la que queremos comprobar las restricciones [0..size-1]
 * @param col Columna de la casilla de la que queremos comprobar las restricciones [0..size-1]
 * @return true si cumple las restricciones
 */
bool Solver::cumpleRestricciones(Tablero *tablero, int fil, int col) {
    bool rest = false;
    bool sigH = true, sigV = true;

    // Comprobar si esa casilla cumple las restricciones de fila y columna, y las binarias siguientes
    if((tablero->comprobarBinariaSiguienteHorizontal(fil,col) == false) && (tablero->comprobarBinariaSiguienteVertical(fil,col) == false) && (tablero->estaEnCol(fil,col) == false) && (tablero->estaEnFila(fil,col)) == false) {
        //Si existe la casilla anterior en la fila, comprobar que se cumple la restricción binaria
        if(col-1 >= 0) {
            sigH = !(tablero->comprobarBinariaSiguienteHorizontal(fil,col-1));
        }
        //Si existe la casilla anterior en la columna, comprobar que se cumple la restricción binaria
        if(fil-1 >= 0) {
            sigV = !(tablero->comprobarBinariaSiguienteVertical(fil-1,col));
        }

        rest = sigH && sigV;
    }

    return rest;
}

/**
 * @brief inicializarDominio Inicializa los valores del dominio de cada casilla del tablero
 * @param tablero Tablero cargado que se va a resolver [0..size-1][0..size-1]
 */
void Solver::inicializarDominio(Tablero *tablero) {
    int s = tablero->getSize();
    Dominio dom;
    vector<Dominio> col;

    domInc = true;
    // Recorrer cada casilla del tablero
    for(int i=0; i<s; i++) {
        for(int j=0; j<s; j++) {
          // Si la casilla ya tiene un valor, es su único valor de dominio
            if(tablero->getCasilla(i,j)!=0) {
                dom.push_back(tablero->getCasilla(i,j));
            }
            // Si no, se ponen los valores [0..size-1] en tDom
            else {
                for(int k=0; k<s; k++) {
                    dom.push_back(k+1);
                }
            }
            col.push_back(dom);
            dom.clear();
        }
        tDom.push_back(col);
        col.clear();
    }

    return;
}

/**
 * @brief backtracking Ejecuta el algoritmo recursivo de backtracking
 * @param tablero Tablero cargado que se va a resolver [0..size-1][0..size-1]
 * @param fill Fila de la casilla actual [0..size-1]
 * @param col Columna de la casilla actual [0..size-1]
 * @return true si se resuelve backtracking
 */
bool Solver::backtracking(Tablero *tablero, int fil, int col) {
    int s = tablero->getSize();
    // Comprobar si se ha podido completar el tablero (caso base)
    if(tablero->tableroCompleto())
        return true;

    // Comprobar si la casilla actual tiene un valor asignado
    if(tablero->getCasilla(fil,col) != 0) {
       // Si podemos desplazarnos en la fila, llamada recursiva con la siguiente columna de la fila
        if(col+1<s) {
            if(backtracking(tablero,fil,col+1)) {
                return true;
            }
        }
        // Si no, llamada recursiva con la primera casilla de la siguiente fila
        else {
            if(backtracking(tablero,fil+1,0)) {
                return true;
            }
        }
        // Devolver false si no se puede encontrar una solución a partir de esta casilla
        return false;
    }

    else {
        // Recorrer el dominio de la casilla actual y asignarle sus valores
        for(size_t i=0; i<tDom[size_t(fil)][size_t(col)].size(); i++) {
            tablero->setCasilla(fil,col,tDom[size_t(fil)][size_t(col)][i]);
            // Comprobar si ese valor del dominio cumple las restricciones del tablero
            if(cumpleRestricciones(tablero, fil, col)) {
                // Si podemos desplazarnos en la fila, llamada recursiva con la siguiente columna de la fila
                if(col+1<s) {
                    if(backtracking(tablero,fil,col+1)) {
                        return true;
                    }
                }
                // Si no, llamada recursiva con la primera casilla de la siguiente fila
                else {
                    if(backtracking(tablero,fil+1,0)) {
                        return true;
                    }
                }
            }
        }
        // Restaurar la casilla si no encontramos una solución
        tablero->setCasilla(fil,col,0);

        // Devolver false si no se puede encontrar una solución a partir de esta casilla
        backTrackingJumps++;
        return false;
    }
}

/**
 * @brief Solver::ejecutarBT Ejecuta backtracking como método de un objeto de la clase Solver
 * @param tablero Tablero cargado que se va a resolver [0..size-1][0..size-1]
 */
void Solver::ejecutarBT(Tablero *tablero) {
    backTrackingJumps = 0;

    if(tablero->tableroCompleto()){
        cout << "Para ejecutar backtracking carga un tablero no resuelto" << endl;
        return;
    }

    if(!domInc)
        inicializarDominio(tablero);
    auto start = clock();
    backtracking(tablero, 0,0);
    auto end = clock();

    float time = 1000.0*(end - start)/CLOCKS_PER_SEC;

    cout << "Saltos hacia atrás: " << backTrackingJumps << endl;
    cout << "Tiempo de ejecución: " << time << endl;

    return;
}

//___________________________________________________________________________AC3

/**
 * @brief inicializarQ Inicializa el conjunto Q que contiene todas las aristas del problema
 * @param Q lista de Aristas que contiene todas las aristas del problema
 * @param tablero Tablero cargado que se va a resolver [0..size-1][0..size-1]
 */
void Solver::inicializarQ(list<Arista> *Q, Tablero *tablero) {
    Arista ar;

    int s = tablero->getSize();
    // Recorrer cada casilla del tablero y establecerla como nodo inicial
    for(int i=0; i<s; i++) {
        for(int j=0; j<s; j++) {
            ar.inicial.fil = i;
            ar.inicial.col = j;
            // Añadir a Q las casillas de la misma fila distintas a la actual
            ar.final.fil = i;
            for(int k=0; k<s; k++) {
                if (k != j) {
                    ar.final.col = k;
                    Q->push_back(ar);
                }
            }
            // Añadir a Q las casillas de la misma columna distintas a la actual
            ar.final.col = j;
            for(int k=0; k<s; k++) {
                if (k != i) {
                    ar.final.fil = k;
                    Q->push_back(ar);
                }
            }
        }
    }
}

/**
 * @brief comprobarRestriccionesBinarias Comprueba que entre las dos casillas de una arista se cumplan las restricciones binarias
 * @param ar Arista que contiene el nodo inicial y final del que queremos comprobar las restricciones
 * @param tablero Tablero cargado que se va a resolver [0..size-1][0..size-1]
 * @return true si cumple las restricciones
 */
bool Solver::comprobarRestriccionesBinarias(Arista ar, Tablero *tablero) {
    bool restFilAnt = true, restFilSig = true, restColAnt = true, restColSig = true;

    // Comprobar restricción si el nodo final está arriba del inicial
    if((ar.inicial.fil-1 == ar.final.fil) && (ar.inicial.col == ar.final.col)) {
        restColAnt = !(tablero->comprobarBinariaSiguienteVertical(ar.inicial.fil-1,ar.inicial.col));
    }
  // Comprobar restricción si el nodo final está abajo del inicial
    else if((ar.inicial.fil+1 == ar.final.fil) && (ar.inicial.col == ar.final.col)) {
        restColSig = !(tablero->comprobarBinariaSiguienteVertical(ar.inicial.fil,ar.inicial.col));
    }
    // Comprobar restricción si el nodo final está a la izquierda del inicial
    else if((ar.inicial.fil == ar.final.fil) && (ar.inicial.col-1 == ar.final.col)) {
        restFilAnt = !(tablero->comprobarBinariaSiguienteHorizontal(ar.inicial.fil,ar.inicial.col-1));
    }
    // Comprobar restricción si el nodo final está a la derecha del inicial
    else if((ar.inicial.fil == ar.final.fil) && (ar.inicial.col+1 == ar.final.col)) {
        restFilAnt = !(tablero->comprobarBinariaSiguienteHorizontal(ar.inicial.fil,ar.inicial.col));
    }

    return (restColAnt && restColSig && restFilAnt && restFilSig);
}

/**
 * @brief comprobarConsist Comprueba la consistencia de una arista para un valor a del dominio del nodo inicial de esta
 * @param ar Arista que contiene el nodo inicial y final del que queremos comprobar las restricciones
 * @param a Valor del dominio del nodo inicial con el que queremos comprobar la consistencia
 * @param tablero Tablero cargado que se va a resolver [0..size-1][0..size-1]
 * @return true si la arista es consistente para ese valor
 */
bool Solver::comprobarConsist (Arista ar, int a, Tablero *tablero) {
    int vIn, vFin;

    // Guardar los valores iniciales de las casillas para restaurarlos luego
    vIn = tablero->getCasilla(ar.inicial.fil,ar.inicial.col);
    vFin = tablero->getCasilla(ar.final.fil,ar.final.col);

    // Poner en la casilla inicial el valor a y en la casilla final los valores de su dominio
    tablero->setCasilla(ar.inicial.fil, ar.inicial.col, a);
    for(size_t b=0; b<tDom[size_t(ar.final.fil)][size_t(ar.final.col)].size(); b++) {
        tablero->setCasilla(ar.final.fil, ar.final.col, tDom[size_t(ar.final.fil)][size_t(ar.final.col)][b]);
        // Comprobar que los dos valores no sean iguales (restricciones de fila y columna) y las restricciones binarias
        if(a != tDom[size_t(ar.final.fil)][size_t(ar.final.col)][b]) {
            if(comprobarRestriccionesBinarias(ar, tablero)) {
                // Restaurar los valores iniciales y devolver true si es consistente
                tablero->setCasilla(ar.inicial.fil, ar.inicial.col, vIn);
                tablero->setCasilla(ar.final.fil, ar.final.col, vFin);
                return true;
            }
        }
    }

    // Restaurar los valores iniciales y devolver false si no es consistente
    tablero->setCasilla(ar.inicial.fil, ar.inicial.col, vIn);
    tablero->setCasilla(ar.final.fil, ar.final.col, vFin);

    return false;
}

/**
 * @brief Solver::ejecutarAC3 Ejecuta el algoritmo AC3 como método de un objeto de la clase Solver
 * @param tablero Tablero cargado que se va a resolver [0..size-1][0..size-1]
 */
void Solver::ejecutarAC3(Tablero *tablero) {
    list<Arista> Q, elimQ;
    Arista ar;
    bool cambioDom;

    if(tablero->tableroCompleto()){
        cout << "Para ejecutar AC3 carga un tablero no resuelto" << endl;
        return;
    }

    // Inicializar el dominio y la lista de aristas del problema
    if(!domInc)
        inicializarDominio(tablero);

    inicializarQ(&Q, tablero);

    // Bucle principal del algoritmo, comprobar la consistencia todas las aristas de la lista Q hasta que esta se quede vacía
    while(!(Q.empty())) {
        // Extraer la primera arista de la lista, eliminarla de Q y añadirla al conjunto de elimQ por si hay que restaurarla
        ar = Q.front();
        Q.pop_front();
        elimQ.push_back(ar);
        cambioDom = false;

        // Comprobar si la casilla inicial está vacía
        if(tablero->getCasilla(ar.inicial.fil,ar.inicial.col) == 0) {
            // Comprobar la consistencia de la arista para cada valor a del dominio de la casilla inicial
            for(size_t a=0; a<tDom[size_t(ar.inicial.fil)][size_t(ar.inicial.col)].size(); a++) {
                    // Si no es consistente, eliminamos el valor a que causa la inconsistencia y ponemos a true la variable que indica si hemos modificado el dominio o no
                    if(!comprobarConsist(ar, tDom[size_t(ar.inicial.fil)][size_t(ar.inicial.col)][a], tablero)) {
                    cambioDom = true;
                    tDom[size_t(ar.inicial.fil)][size_t(ar.inicial.col)].erase(tDom[size_t(ar.inicial.fil)][size_t(ar.inicial.col)].begin()+int(a));
                    a--;
                }
            }
            // Si el dominio se queda vacío, salir sin solución
            if(tDom[size_t(ar.inicial.fil)][size_t(ar.inicial.col)].empty()) {
                cout << "No hay solución AC3" << endl;
                return;
            }
            // Si hemos modificado el dominio de la casilla inicial, retaurar en Q las aristas de elimQ que acaban en el nodo inicial y que no son la que se acaba de comprobar
            if (cambioDom) {
                for(list<Arista>::iterator it=elimQ.begin(); it != elimQ.end(); ++it) {
                    if((ar.inicial.fil == it->final.fil) && (ar.inicial.col == it->final.col) && ((ar.final.fil != it->inicial.fil) || (ar.final.col != it->inicial.col))) {
                        Q.push_back(*it);
                    }
                }
            }
        }
    }


    // Mostrar los dominios resultantes en pantalla
    cout << "Después de ejecutar AC3, los dominios de cada caslla son:" << endl;
    for(size_t i=0; i<tDom.size(); i++) {
        for(size_t j=0; j<tDom[i].size(); j++) {
            for(size_t k=0; k<tDom[i][j].size(); k++) {
                cout << tDom[i][j][k] << " ";
            }
            cout << "\t";
        }
        cout << endl;
    }
    cout << "Para resolver el tablero, ejecutar backtracking" << endl;

    return;
}

void Solver::ejecutarFC(Tablero *tablero) {
    cout << "Esta función no está implementada" << endl;

    return;
}
