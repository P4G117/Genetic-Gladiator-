/*
 * InithPathfinding.h
 *
 *  Created on: 9 may. 2017
 *      Author: victork
 */

#ifndef INITHPATHFINDING_H_
#define INITHPATHFINDING_H_

#include "Globales.h"
#include "AStar.h"
extern int zonaDeIntimidacion[IDIM][JDIM];
extern int zonaDeIntimidacionB[IDIM][JDIM];

class InithPathfinding {
private:
	const int iStart = 0;
	const int jStart = 2;
	const int iEnd = 9;
	const int jEnd = 2;
	int resistenciaGLadiador;
	int resistenciaGLadiadorB;
public:
	InithPathfinding();
	void ejecutarPathFinding(int,int );
};

#endif /* INITHPATHFINDING_H_ */
