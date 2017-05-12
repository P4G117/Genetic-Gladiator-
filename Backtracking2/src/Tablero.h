//
// Created by VictorF on 09/05/2017.
//

#ifndef BACKTRACKING_TABLERO_H
#define BACKTRACKING_TABLERO_H


#include "Cuadro.h"
#include <iostream>
#include <fstream>
using namespace std;

class Tablero {
private:

    int colum,fila,size;
    Cuadro* head;
    ofstream archivo;
    string hola;
public:
    Tablero();
    ~Tablero();
    void create();
    void show(int);
    void showsize();
    int buscar(int);
    int encontrar(int);
    void borrarRastro(Cuadro*,int);
    void set_dato();
    int addQueen(int,int);
    void marcarPosiblesColisiones(Cuadro*,int);
    void guardar(int);

};


#endif //BACKTRACKING_TABLERO_H
