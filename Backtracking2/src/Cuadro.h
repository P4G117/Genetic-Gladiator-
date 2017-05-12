//
// Created by VictorF on 09/05/2017.
//

#ifndef BACKTRACKING_CUADRO_H
#define BACKTRACKING_CUADRO_H


class Cuadro {
private:
    int data;
    Cuadro *next,*prev,*down,*up;
public:
    Cuadro *getPrev() const;

    void setPrev(Cuadro *prev);

    Cuadro *getDown() const;

    void setDown(Cuadro *down);

    Cuadro *getUp() const;

    void setUp(Cuadro *up);

    Cuadro(int);

    Cuadro *get_Next() const;

    void set_Next(Cuadro *next);

    Cuadro *get_Prev() const;

    void set_Prev(Cuadro *prev);

    Cuadro *get_Down() const;

    void set_Down(Cuadro *down);

    Cuadro *get_Up() const;

    void set_Up(Cuadro *up);

    int get_Data() const;

    void set_Data(int data);

};


#endif //BACKTRACKING_CUADRO_H
