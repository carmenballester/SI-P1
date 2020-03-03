#ifndef SOLVER_H
#define SOLVER_H

#include "tablero.h"

#include <QObject>
#include <list>

using namespace std;

// Para almacenar los dominios de las casillas, creamos un tipo Dominio y un tipo TDominios
typedef vector<int> Dominio;
typedef vector<vector<Dominio>> TDominios;

// Para almacenar una lista de Aristas
struct Casilla {
    int fil;
    int col;
};

struct Arista {
    Casilla inicial;
    Casilla final;
};

class Solver : public QObject
{
    Q_OBJECT
public:
    explicit Solver(QObject *parent = nullptr);

    void ejecutarBT(Tablero *);
    void ejecutarAC3(Tablero *);
    void ejecutarFC(Tablero *);

    bool cumpleRestricciones(Tablero *, int, int);
    void inicializarDominio(Tablero *);
    bool backtracking(Tablero *, int, int);

    void inicializarQ(list<Arista> *, Tablero *);
    bool comprobarRestriccionesBinarias(Arista, Tablero *);
    bool comprobarConsist (Arista, int, Tablero *);

    void inicializarPodados(Tablero *);
    bool comprobarR(Arista, int, int, Tablero *);
    bool forward(Tablero *, int, int, int);
    void restaurar(Tablero *, int, int);
    bool forwardChecking(Tablero *, int, int);



signals:

public slots:

private:
    int backTrackingJumps;
    TDominios tDom;
    bool domInc = false;

    TDominios podados;
};

#endif // SOLVER_H
