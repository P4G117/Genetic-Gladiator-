//
// Created by estadm on 09/05/2017.
//

#ifndef BACKTRACKING_BACKTRACKING_H
#define BACKTRACKING_BACKTRACKING_H

#include "Tablero.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
class Backtracking {
private:
    int fila;
    int colum;
    int queens;
    int soluciones;
    Tablero *tab;
    ofstream archivo;
public:
    Backtracking();
    ~Backtracking();
    void addQueen();
    void deleteQueen();
    void guardar(string);
    void buscar(int);
};


#endif //BACKTRACKING_BACKTRACKING_H
