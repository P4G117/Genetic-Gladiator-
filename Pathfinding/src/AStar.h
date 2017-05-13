//
// Created by victork on 07/05/17.
//

#ifndef PATHFINDING_ASTAR_H
#define PATHFINDING_ASTAR_H

#include "Globales.h"
#include "Node.h"
#include "InithPathfinding.h"




class AStar {
private:
    // list of closed (check-out) nodes
    int listaCerrada[IDIM][JDIM];

    // list of open (not-yet-checked-out) nodes
    int listaAbierta[IDIM][JDIM];

    // map of directions -> 0: Derecha / 3: Arriba / 2: Izquierda / 1: Abajo
    int mapaDeDirecciones[IDIM][JDIM];

    int numeroTorres = 3; ///Iinicialmente se colocaran 3 torres en la "Zona de Intimidacion"

    string pathAux = "";
    int listaCerradaB[IDIM][JDIM];

    // list of open (not-yet-checked-out) nodes
    int listaAbiertaB[IDIM][JDIM];

    // map of directions -> 0: Derecha / 3: Arriba / 2: Izquierda / 1: Abajo
    int mapaDeDireccionesB[IDIM][JDIM];

    int numeroTorresB = 3; ///Iinicialmente se colocaran 3 torres en la "Zona de Intimidacion"

    string pathAuxB = "";


public:
    string pathFind( const Location &locStart, const Location &locFinish);
    string pathFindB( const Location &locStart, const Location &locFinish);
	int getNumeroTorres() const;
	void setNumeroTorres(int numeroTorres);



	void setPathAux(const string& pathAux) {
		this->pathAux = pathAux;
	}
	void setPathAuxB(const string& pathAuxB) {
			this->pathAuxB = pathAuxB;
		}
	const string& getPathAux() const;
	const string& getPathAuxB() const;
};


#endif //PATHFINDING_ASTAR_H
