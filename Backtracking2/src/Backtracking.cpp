//
// Created by estadm on 09/05/2017.
//
#include <iostream>
#include "Backtracking.h"

using namespace std;
/**
 * Constructor de la clase
 */
Backtracking::Backtracking() {
    tab = new Tablero();
    tab->create();
    tab->show(0);
    fila = 0;
    colum = 0;
    queens = 1;
    soluciones = 0;

}

/**
 * Clase encargada de añadir las reinas al tablero
 */
void Backtracking::addQueen() {
    int validarvueltas = 0;
    while (colum < 8) {
        while (fila<8) {
            //cout << "Validacion: Columnas:" << colum << "y Reinas: " << queens-1 << endl;
            if((colum+1) > queens){
                colum = colum - 2;
                //cout << "Se eliminará una reina" << endl;
                tab->show(2);
                fila = tab->buscar(colum)+1;
                validarvueltas = fila;
                queens--;
                //cout << "Reina eliminada" << endl;
                tab->show(3);
                //sleep(3);
            }else if(tab->addQueen(fila,colum) == 1){
                queens++;
                //cout << "Nueva reina" << endl;
                //cout << "Pos: (" << fila << "," << colum << ")" << endl;
                //cout << "reinas: " << queens-1 << endl;
                colum++;
                //cout << "Columna: " << colum-1 << endl;
                fila = 0;
                tab->show(4);
                //sleep(2);
            }else{
                //cout << "else: fila ->" << fila + 1 << endl;
                fila++;
            }
            //cout << "para validar: " << (colum +1) << " " << queens << " "  << fila << " " << validarvueltas<< endl;
            if(validarvueltas > 7 || (((colum+1) == 8 && queens<9)&& fila >= 7)){
                //cout << "Validar vueltas: " << validarvueltas << endl;
                colum--;
                fila = tab->buscar(colum)+1;
                validarvueltas = fila;
                queens--;
                //cout << "Reina eliminada" << endl;
                tab->show(3);
                //sleep(3);
            }
            if(queens == 9){
            	tab->show(1);
                //cout << "//////////////////////////////// Solucion econtrada!!!!!!!!" << endl;
                soluciones++;
                //cout << soluciones << endl;
                if(soluciones == 88){
                    fila = 8;
                    colum = 8;
                }else {
                    colum--;
                    tab->show(2);
                    fila = tab->buscar(colum) + 1;
                    validarvueltas = fila;
                    queens--;
                    //cout << "Reina eliminada" << endl;
                    tab->show(3);
                }
            }
        }
        colum++;
        fila=0;
    }
    cout << "Proceso finalizado" << endl;
    tab->~Tablero();
}

/**
 * Destructor de la clase
 */
Backtracking::~Backtracking() {}
