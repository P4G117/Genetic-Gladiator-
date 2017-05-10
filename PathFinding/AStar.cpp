//
// Created by victork on 07/05/17.
//

#include "AStar.h"



string AStar::pathFind(const Location &locStart, const Location &locFinish) {

	/*
    //int zonaDeIntimidacionAux[IDIM][JDIM];
   // zonaDeIntimidacionAux = zonaDeIntimidacion;

   //vector<int> posOcupadas;
    //int matriz[1][50][2];
   // while (centinela) {
     //   int numTorres = 3;
    //    for(int i = numTorres; i > 0 ; i--){

       // }
	 */
	//zonaDeIntimidacion[0][2] = 1;
	//zonaDeIntimidacion[9][2] = 1;

	///Copia de Respaldo de la Cuadricula Original en caso de que se bloqueen todos los caminos
	int zonaDeIntimidacionAux[IDIM][JDIM];


	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 5; j++){
			zonaDeIntimidacionAux[i][j] = zonaDeIntimidacion[i][j];
		}
	}
	int p = 0;

	while(p != 100){

		int torre = 0;
		while(torre < getNumeroTorres()){
			bool disponible = false;
			srand(time(0));
			int num = 0;
			while(disponible == false){ //&& num < 30){

				int fila = rand()%9;
				int columna = rand()%4;

				if(zonaDeIntimidacion[fila][columna] != 1 && zonaDeIntimidacion[fila][columna] != 2
						&& zonaDeIntimidacion[fila][columna] != 4){ /// Si NO es 1,2,4 esta disponible
					zonaDeIntimidacion[fila][columna] = 1;

					disponible = true;
				}
				num++;
			}
			torre++;
		}



		// list of open (not-yet-checked-out) nodes
		static priority_queue<Node> q[2];

		// q index
		static int qi;

		static Node *pNode1;
		static Node *pNode2;
		static int i, j, row, col, iNext, jNext;
		static char c;
		qi = 0;

		// reset the Node lists (0 = ".")
		for (j = 0; j < JDIM; j++) {
			for (i = 0; i < IDIM; i++) {
				listaCerrada[i][j] = 0;
				listaAbierta[i][j] = 0;
			}
		}

		// create the start node and push into list of open nodes
		pNode1 = new Node(locStart, 0, 0);
		pNode1->calculateFValue(locFinish);
		q[qi].push(*pNode1);

		// A* search
		while (!q[qi].empty()) {
			// get the current node w/ the lowest FValue
			// from the list of open nodes
			pNode1 = new Node(q[qi].top().getLocation(), q[qi].top().getGValue(), q[qi].top().getFValue());

			row = (pNode1->getLocation()).row;
			col = pNode1->getLocation().col;
			//cout << "(row, col)= " <<  "("<<row << ", "<<col << ")"<< endl;

			// remove the node from the open list
			q[qi].pop();
			listaAbierta[row][col] = 0;

			// mark it on the closed nodes list
			listaCerrada[row][col] = 1;

			// stop searching when the goal state is reached
			if (row == locFinish.row && col == locFinish.col) {
				// drawing direction map
				/*
                cout << endl;

                for(j = JDIM - 1; j >= 0; j--) {
                    for(i = 0; i < IDIM; i++) {
                        cout << mapaDeDirecciones[i][j];
                    }
                    cout << endl;
                }*/
				cout << endl;

				// generate the path from finish to start from mapaDeDirecciones
				string path = "";
				while (!(row == locStart.row && col == locStart.col)) {
					j = mapaDeDirecciones[row][col];
					c = '0' + (j + NDIR / 2) % NDIR;
					path = c + path;
					row += iDir[j];
					col += jDir[j];
				}

				// garbage collection
				delete pNode1;

				// empty the leftover nodes
				while (!q[qi].empty()) q[qi].pop();

				//PARA EL CONTROLADOR DE CAMINO DEL PATHFINDING
				p=0;
				//HASTA AQUI LLEGA EL CONTROLADOR DE CAMINO
				setPathAux(path);
				//pathAux = path;
				return path;
			}

			// generate moves in all possible directions
			for (i = 0; i < NDIR; i++) {
				iNext = row + iDir[i];
				jNext = col + jDir[i];

				// if not wall (obstacle) nor in the closed list
				if (!(iNext < 0 || iNext > IDIM - 1 || jNext < 0 || jNext > JDIM - 1 ||
						zonaDeIntimidacion[iNext][jNext] == 1 || listaCerrada[iNext][jNext] == 1)) {

					// generate a child node
					pNode2 = new Node(Location(iNext, jNext), pNode1->getGValue(), pNode1->getFValue());
					pNode2->updateGValue(i);
					pNode2->calculateFValue(locFinish);

					// if it is not in the open list then add into that
					if (listaAbierta[iNext][jNext] == 0) {
						listaAbierta[iNext][jNext] = pNode2->getFValue();
						q[qi].push(*pNode2);
						// mark its parent node direction
						mapaDeDirecciones[iNext][jNext] = (i + NDIR / 2) % NDIR;
					}

					// already in the open list
					else if (listaAbierta[iNext][jNext] > pNode2->getFValue()) {
						// update the FValue info
						listaAbierta[iNext][jNext] = pNode2->getFValue();

						// update the parent direction info,  mark its parent node direction
						mapaDeDirecciones[iNext][jNext] = (i + NDIR / 2) % NDIR;

						// replace the node by emptying one q to the other one
						// except the node to be replaced will be ignored
						// and the new node will be pushed in instead
						while (!(q[qi].top().getLocation().row == iNext &&
								q[qi].top().getLocation().col == jNext)) {
							q[1 - qi].push(q[qi].top());
							q[qi].pop();
						}

						// remove the wanted node
						q[qi].pop();

						// empty the larger size q to the smaller one
						if (q[qi].size() > q[1 - qi].size()) qi = 1 - qi;
						while (!q[qi].empty()) {
							q[1 - qi].push(q[qi].top());
							q[qi].pop();
						}
						qi = 1 - qi;

						// add the better node instead
						q[qi].push(*pNode2);
					} else delete pNode2;
				}
			}
			delete pNode1;
		}



		// no path found
		//return "";
		p++;
		for(int i = 0; i < 10; i++){
			for(int j = 0; j < 5; j++){
				zonaDeIntimidacion[i][j] = zonaDeIntimidacionAux[i][j];
			}
		}




	}
	return getPathAux();
}














string AStar::pathFindB(const Location &locStart, const Location &locFinish) {

	/*
    //int zonaDeIntimidacionAux[IDIM][JDIM];
   // zonaDeIntimidacionAux = zonaDeIntimidacion;

   //vector<int> posOcupadas;
    //int matriz[1][50][2];
   // while (centinela) {
     //   int numTorres = 3;
    //    for(int i = numTorres; i > 0 ; i--){

       // }
	 */
	//zonaDeIntimidacion[0][2] = 1;
	//zonaDeIntimidacion[9][2] = 1;

	///Copia de Respaldo de la Cuadricula Original en caso de que se bloqueen todos los caminos
	int zonaDeIntimidacionAuxB[IDIM][JDIM];


	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 5; j++){
			zonaDeIntimidacionAuxB[i][j] = zonaDeIntimidacionB[i][j];
		}
	}
	int p = 0;

	while(p != 100){

		int torre = 0;
		while(torre < getNumeroTorres()){
			bool disponible = false;
			srand(time(0));
			int num = 0;
			while(disponible == false){ //&& num < 30){

				int filaB = rand()%9;
				int columnaB = rand()%4;

				if(zonaDeIntimidacionB[filaB][columnaB] != 1 && zonaDeIntimidacionB[filaB][columnaB] != 2
						&& zonaDeIntimidacionB[filaB][columnaB] != 4){ /// Si NO es 1,2,4 esta disponible
					zonaDeIntimidacionB[filaB][columnaB] = 1;

					disponible = true;
				}
				num++;
			}
			torre++;
		}



		// list of open (not-yet-checked-out) nodes
		static priority_queue<Node> q[2];

		// q index
		static int qi;

		static Node *pNode1;
		static Node *pNode2;
		static int i, j, row, col, iNext, jNext;
		static char c;
		qi = 0;

		// reset the Node lists (0 = ".")
		for (j = 0; j < JDIM; j++) {
			for (i = 0; i < IDIM; i++) {
				listaCerrada[i][j] = 0;
				listaAbierta[i][j] = 0;
			}
		}

		// create the start node and push into list of open nodes
		pNode1 = new Node(locStart, 0, 0);
		pNode1->calculateFValue(locFinish);
		q[qi].push(*pNode1);

		// A* search
		while (!q[qi].empty()) {
			// get the current node w/ the lowest FValue
			// from the list of open nodes
			pNode1 = new Node(q[qi].top().getLocation(), q[qi].top().getGValue(), q[qi].top().getFValue());

			row = (pNode1->getLocation()).row;
			col = pNode1->getLocation().col;
			//cout << "(row, col)= " <<  "("<<row << ", "<<col << ")"<< endl;

			// remove the node from the open list
			q[qi].pop();
			listaAbiertaB[row][col] = 0;

			// mark it on the closed nodes list
			listaCerradaB[row][col] = 1;

			// stop searching when the goal state is reached
			if (row == locFinish.row && col == locFinish.col) {
				// drawing direction map
				/*
                cout << endl;

                for(j = JDIM - 1; j >= 0; j--) {
                    for(i = 0; i < IDIM; i++) {
                        cout << mapaDeDirecciones[i][j];
                    }
                    cout << endl;
                }*/
				cout << endl;

				// generate the path from finish to start from mapaDeDirecciones
				string path = "";
				while (!(row == locStart.row && col == locStart.col)) {
					j = mapaDeDireccionesB[row][col];
					c = '0' + (j + NDIR / 2) % NDIR;
					path = c + path;
					row += iDir[j];
					col += jDir[j];
				}

				// garbage collection
				delete pNode1;

				// empty the leftover nodes
				while (!q[qi].empty()) q[qi].pop();

				//PARA EL CONTROLADOR DE CAMINO DEL PATHFINDING
				p=0;
				//HASTA AQUI LLEGA EL CONTROLADOR DE CAMINO
				setPathAux(path);
				//pathAux = path;
				return path;
			}

			// generate moves in all possible directions
			for (i = 0; i < NDIR; i++) {
				iNext = row + iDir[i];
				jNext = col + jDir[i];

				// if not wall (obstacle) nor in the closed list
				if (!(iNext < 0 || iNext > IDIM - 1 || jNext < 0 || jNext > JDIM - 1 ||
						zonaDeIntimidacion[iNext][jNext] == 1 || listaCerradaB[iNext][jNext] == 1)) {

					// generate a child node
					pNode2 = new Node(Location(iNext, jNext), pNode1->getGValue(), pNode1->getFValue());
					pNode2->updateGValue(i);
					pNode2->calculateFValue(locFinish);

					// if it is not in the open list then add into that
					if (listaAbiertaB[iNext][jNext] == 0) {
						listaAbiertaB[iNext][jNext] = pNode2->getFValue();
						q[qi].push(*pNode2);
						// mark its parent node direction
						mapaDeDireccionesB[iNext][jNext] = (i + NDIR / 2) % NDIR;
					}

					// already in the open list
					else if (listaAbiertaB[iNext][jNext] > pNode2->getFValue()) {
						// update the FValue info
						listaAbiertaB[iNext][jNext] = pNode2->getFValue();

						// update the parent direction info,  mark its parent node direction
						mapaDeDireccionesB[iNext][jNext] = (i + NDIR / 2) % NDIR;

						// replace the node by emptying one q to the other one
						// except the node to be replaced will be ignored
						// and the new node will be pushed in instead
						while (!(q[qi].top().getLocation().row == iNext &&
								q[qi].top().getLocation().col == jNext)) {
							q[1 - qi].push(q[qi].top());
							q[qi].pop();
						}

						// remove the wanted node
						q[qi].pop();

						// empty the larger size q to the smaller one
						if (q[qi].size() > q[1 - qi].size()) qi = 1 - qi;
						while (!q[qi].empty()) {
							q[1 - qi].push(q[qi].top());
							q[qi].pop();
						}
						qi = 1 - qi;

						// add the better node instead
						q[qi].push(*pNode2);
					} else delete pNode2;
				}
			}
			delete pNode1;
		}



		// no path found
		//return "";
		p++;
		for(int i = 0; i < 10; i++){
			for(int j = 0; j < 5; j++){
				zonaDeIntimidacionB[i][j] = zonaDeIntimidacionAuxB[i][j];
			}
		}




	}
	return getPathAux();
}














int AStar::getNumeroTorres() const {
	return numeroTorres;
}

const string& AStar::getPathAux() const {
	return pathAux;
}

void AStar::setNumeroTorres(int numeroTorres) {
	this->numeroTorres = numeroTorres;
}


