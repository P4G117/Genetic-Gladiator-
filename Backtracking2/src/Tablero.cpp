//
// Created by VictorF on 09/05/2017.
//

#include "Tablero.h"

using namespace std;

/**
 * Construuctor de la clase
 */
Tablero:: Tablero(){
    colum = 0;
    fila = 0;
    size = 0;
    head = NULL;
    hola = "hola";
    archivo.open("Tablero.txt",ios::out);
    guardar(10000);
}

/**
 * Destructor de la clase
 */
Tablero::~Tablero(){
	archivo.close();
}

/**
 * Clase encargada de crear la matriz sobre la que se correrá el backtracking
 */
void Tablero::create() {
    colum = 0;
    fila = 0;
    head = new Cuadro(0);
    size++;
    Cuadro *tmpfila = head;
    Cuadro *tmpcolum = head;
    while(fila <8){
        while(colum < 7){
            if(fila==0){
                if(colum == 0) {
                    tmpcolum->set_Prev(NULL);
                }
                tmpcolum->set_Up(NULL);
                tmpcolum->set_Next(new Cuadro(0));
                tmpcolum->get_Next()->set_Prev(tmpcolum);
                tmpcolum = tmpcolum->get_Next();
                if(colum == 6){
                    tmpcolum->set_Next(NULL);
                }
                colum++;
            }else{
                tmpcolum->set_Next(new Cuadro(0));
                tmpcolum->get_Next()->set_Prev(tmpcolum);
                tmpcolum = tmpcolum->get_Next();
                if(colum == 6){
                    tmpcolum->set_Next(NULL);
                }
                colum++;
                Cuadro *tmpUp = tmpfila;
                tmpUp = tmpUp->get_Up();
                for(int cont=0;cont <colum;cont++){
                    tmpUp = tmpUp->get_Next();
                }
                tmpUp->set_Down(tmpcolum);
                tmpcolum->set_Up(tmpUp);

            }
            size++;
        }
        if(fila<7) {
            tmpfila->set_Down(new Cuadro(0));
            size++;
            tmpfila->get_Down()->set_Up(tmpfila);
            tmpfila = tmpfila->get_Down();
            tmpfila->set_Prev(NULL);
            tmpcolum = tmpfila;
            colum = 0;
        }
        fila++;
    }
    fila = colum = 0;

}

/**
 * Se encarga de enviar datos al método guardar para que sean almacenados en un txt
 *
 */
void Tablero::show(int validar){
	if(validar == 2){
		guardar(1002);
	}
	if(validar == 3){
		guardar(1003);
	}
	if(validar == 4){
		guardar(1004);
	}
    fila = 0;
    colum = 0;
    if(size == 0){
        cout << "No hay elementos en la lista" << endl;
    }else {
        Cuadro *tmpfila = head;
        Cuadro *tmpcolum = head;
        while (fila < 8) {
            while (colum<8) {
                //cout << tmpcolum->get_Data() << " | ";
                guardar(tmpcolum->get_Data());
                tmpcolum = tmpcolum->get_Next();
                colum++;
            }
            //cout <<" * "<< endl;
            guardar(1000);
            tmpfila = tmpfila->get_Down();
            tmpcolum = tmpfila;
            colum = 0;
            fila++;
        }
    }
    fila = 0;
    if(validar == 1){
    	guardar(1001);
    }
    guardar(10000);
}

/**
 * Muestra el tamaño de la matriz
 */
void Tablero::showsize(){
    cout << "size: " << size << endl;
};

/**
 * Aqrega la reina a la matriz
 */
int Tablero::addQueen(int posY,int posX) {
    int validar = 0;
    fila = 0;
    colum = 0;
    if(size == 0){
        cout << "No hay elementos en la lista" << endl;
    }else {
        Cuadro *tmpfila = head;
        Cuadro *tmpcolum = head;
        while (fila <= posY) {
            while (colum <= posX) {
                if(fila == posY && colum == posX){
                    if(tmpcolum->get_Data() == 0) {
                        tmpcolum->set_Data(1);
                        marcarPosiblesColisiones(tmpcolum,colum+10);
                        validar = 1;
                    }else{
                        validar = 2;
                    }
                }
                tmpcolum = tmpcolum->get_Next();
                colum++;
            }
            //cout <<" * "<< endl;
            tmpfila = tmpfila->get_Down();
            tmpcolum = tmpfila;
            colum = 0;
            fila++;
        }
    }
    return validar;
}

/**
 * Se encarga de marcar las posiciones a las que se puede mover la reina agregada
 */
void Tablero:: marcarPosiblesColisiones(Cuadro *reina,int pDato){
    Cuadro* tmpmarca = reina;
    //Arriba izquierda
    while(tmpmarca->get_Up() != NULL && tmpmarca->get_Up()->get_Prev() != NULL){
        tmpmarca->get_Up()->get_Prev()->set_Data((tmpmarca->get_Up()->get_Prev()->get_Data()+ pDato));
        tmpmarca = tmpmarca->get_Up()->get_Prev();
    }

    tmpmarca = reina;
    //Abajo derecha
    while(tmpmarca->get_Down() != NULL && tmpmarca->get_Down()->get_Next() != NULL){
        tmpmarca->get_Down()->get_Next()->set_Data(tmpmarca->get_Down()->get_Next()->get_Data()+ pDato);
        tmpmarca = tmpmarca->get_Down()->get_Next();
    }

    tmpmarca = reina;
    //Abajo izquierda
    while(tmpmarca->get_Down() != NULL && tmpmarca->get_Down()->get_Prev() != NULL){
        tmpmarca->get_Down()->get_Prev()->set_Data(tmpmarca->get_Down()->get_Prev()->get_Data()+ pDato);
        tmpmarca = tmpmarca->get_Down()->get_Prev();
    }

    tmpmarca = reina;
    //Arriba derecha
    while(tmpmarca->get_Up() != NULL && tmpmarca->get_Up()->get_Next() != NULL){
        tmpmarca->get_Up()->get_Next()->set_Data(tmpmarca->get_Up()->get_Next()->get_Data()+ pDato);
        tmpmarca = tmpmarca->get_Up()->get_Next();
    }
    tmpmarca = reina;
    //Arriba
    while(tmpmarca->get_Up() != NULL){
        tmpmarca->get_Up()->set_Data(tmpmarca->get_Up()->get_Data()+ pDato);
        tmpmarca = tmpmarca->get_Up();
    }

    tmpmarca = reina;
    //Abajo
    while(tmpmarca->get_Down() != NULL){
        tmpmarca->get_Down()->set_Data(tmpmarca->get_Down()->get_Data()+ pDato);
        tmpmarca = tmpmarca->get_Down();
    }

    tmpmarca = reina;
    //Derecha
    while(tmpmarca->get_Next() != NULL){
        tmpmarca->get_Next()->set_Data(tmpmarca->get_Next()->get_Data()+ pDato);
        tmpmarca = tmpmarca->get_Next();
    }

    tmpmarca = reina;
    //Izquierda
    while(tmpmarca->get_Prev() != NULL){
        tmpmarca->get_Prev()->set_Data(tmpmarca->get_Prev()->get_Data()+ pDato);
        tmpmarca = tmpmarca->get_Prev();
    }
}

/**
 * Se encarga de buscar reinas para que sean elimindas
 */
int Tablero:: buscar(int pColum){
    //cout << "Columna entrante: "<<pColum << endl;
    int filaEncuentro = 9;
    fila = 0;
    colum = 0;
    Cuadro *tmpcolum = head;
    while (colum < pColum) {
        //cout << "Columna: "<<colum << endl;
        tmpcolum = tmpcolum->get_Next();
        colum++;
    }
    //cout << "Columna de encuentro: " << colum << endl;
    Cuadro *tmpfila = tmpcolum;
    while(fila < 8){
        if(tmpfila->get_Data() == 1){
            borrarRastro(tmpfila,colum);
            filaEncuentro = fila;
            //cout << "Fila de encuentro: " << fila << endl;
            fila=8;
        }
        tmpfila = tmpfila->get_Down();
        fila++;
    }
    return filaEncuentro;
}

/**
 * Se encarga de borrar el rastro de la reina eliminada
 */
void Tablero:: borrarRastro(Cuadro *reina,int pColum) {
    Cuadro* tmpReina = reina;
    tmpReina->set_Data(0);
    marcarPosiblesColisiones(tmpReina,-(pColum+10));
}

/**
 * Se encarga de buscar la reina agregada antes de la reina que fue eliminada
 */
int Tablero::encontrar(int pColum) {
    //cout << "Columna entrante: "<<pColum << endl;
    int filaEncuentro = 9;
    fila = 0;
    colum = 0;
    Cuadro *tmpcolum = head;
    while (colum < pColum) {
        cout << "Columna: "<<colum << endl;
        tmpcolum = tmpcolum->get_Next();
        colum++;
    }
    //cout << "Columna de encuentro: " << colum << endl;
    Cuadro *tmpfila = tmpcolum;
    while(fila < 8){
        if(tmpfila->get_Data() == 1){
            filaEncuentro = fila;
            cout << "Fila de encuentro: " << fila << endl;
            fila=8;
        }
        tmpfila = tmpfila->get_Down();
        fila++;
    }
    return filaEncuentro;
}

/**
 * Se encarga de almacenar los datos en un archivo txt
 */
void Tablero::guardar(int pDatos) {
    //cout << "/////////////////////////////////////////////////////////////  " <<archivo.fail() << endl;
    if(pDatos == 1000){
    	archivo<<"\n";
    }else if(pDatos == 10000){
    	archivo<<"\n";
    	archivo<<"\n";
    	archivo<<"\n";
    	archivo<<"     a       b          c        d        f        g        h        i        \n";
    }else if(pDatos == 1001){
    	archivo<<"///////////////////////////  Solución encontrada   ////////////////////////";
    }else if(pDatos == 1002){
    	archivo<<"///////////////////////////  Una reina se va a eliminar  //////////////////////// \n";
    }else if(pDatos == 1003){
    	archivo<<"///////////////////////////  Reina eliminada   //////////////////////// \n";
    }else if(pDatos == 1004){
    	archivo<<"///////////////////////////  Reina Nueva   //////////////////////// \n";
    }else{
		archivo<<"    ";
		archivo<<pDatos;
		archivo<<"  | ";
    }
}

