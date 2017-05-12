//
// Created by VictorF on 09/05/2017.
//

#include "Cuadro.h"
#include <iostream>

/**
 * Constructor de la clase
 */
Cuadro::Cuadro(int pDato){
    data = pDato;
    next,prev,down,up = NULL;
}

int Cuadro::get_Data() const {
    return data;
}

void Cuadro::set_Data(int data) {
    Cuadro::data = data;
}

Cuadro *Cuadro::get_Next() const {
    return next;
}

void Cuadro::set_Next(Cuadro *next) {
    Cuadro::next = next;
}

Cuadro *Cuadro::get_Prev() const {
    return prev;
}

void Cuadro::set_Prev(Cuadro *prev) {
    Cuadro::prev = prev;
}

Cuadro *Cuadro::get_Down() const {
    return down;
}

void Cuadro::set_Down(Cuadro *down) {
    Cuadro::down = down;
}

Cuadro *Cuadro::get_Up() const {
    return up;
}

void Cuadro::set_Up(Cuadro *up) {
    Cuadro::up = up;
}
