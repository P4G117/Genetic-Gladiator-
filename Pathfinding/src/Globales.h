#ifndef PATHFINDING_GLOBALES_H
#define PATHFINDING_GLOBALES_H

//#include "AStar.h"
//#include "Node.h"

#include <iostream>
#include <queue>
//#include <vector>

using namespace std;

struct Location{
    int row, col;

    Location(){
        row = col = 0;
    };

    Location(int r, int c){
        row = r;
        col = c;
    };
};

const int IDIM =10; /// Longitud "Zona de Intimidacion"
const int JDIM = 5; /// Ancho de la "Zona de Intimidacion"
const int NDIR = 4; /// Posibilidades de los movimientos (Arriba, Abajo, Izquierda, Derecha)

const int iDir[NDIR] = {1, 0, -1, 0}; ///
const int jDir[NDIR] = {0, 1, 0, -1}; ///
extern int zonaDeIntimidacion[IDIM][JDIM];
extern int zonaDeIntimidacionB[IDIM][JDIM];


#endif //PATHFINDING_GLOBALES_H
