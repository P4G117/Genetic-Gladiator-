/*
 * InithPathfinding.cpp
 *
 *  Created on: 9 may. 2017
 *      Author: victork
 */

#include "InithPathfinding.h"

	InithPathfinding::InithPathfinding(){

	}
	int zonaDeIntimidacionB[IDIM][JDIM];
	int zonaDeIntimidacion[IDIM][JDIM];

void InithPathfinding::ejecutarPathFinding(int resistenciaGLadiador,int resistenciaGladiadorB){
	//zonaDeIntimidacion[4][4] = 0;
	//int iStart = 0,jStart = 2;
	//int iEnd = 9,jEnd = 2;
	int numeroPartidas = 0;



	AStar ObjPathFinding;
	srand(time(0));

	while(numeroPartidas < 1) {     /// DE AQUI SE LLAMA AL RESTUFULL, SE OBTIENE EL GLADIADOR,
		/// SE HACE PASAR POR LA ZONA DE INTIMIDACION, VE SI SE LLEGA
		/// AL COLISEO Y SE REPITE

		//int resistenciaGLadiador = rand()%100;
		int disparosPorTorre = 0;


		string path = ObjPathFinding.pathFind(Location(iStart, jStart), Location(iEnd, jEnd));

		// cout << "Tamaño Matriz: "<< IDIM<< "," << JDIM << endl;
		cout << "Inicio: " << iStart << "," << jStart << endl;
		cout << "Final: " << iEnd << "," << jEnd << endl;

		// get the path
		//    string path = pathFind(Location(iStart, jStart), Location(iEnd, jEnd)); // Run bitch!

		cout << endl;
		cout << "path: " << path << "\n" << endl;


		// follow the path on the zonaDeIntimidacion and display it
		if (path.length() > 0) {
			char c;
			int m, n;
			int i = iStart;
			int j = jStart;
			zonaDeIntimidacion[i][j] = 2; ///Punto de Entrada
			for (m = 0; m < path.length(); m++) {
				c = path.at(m);
				n = atoi(&c);
				i = i + iDir[n];
				j = j + jDir[n];
				zonaDeIntimidacion[i][j] = 3;
			}
			zonaDeIntimidacion[i][j] = 4; /// Punto de salida


			for(int i = 0; i < 10; i++){
				for(int j = 0; j < 5; j++){
					if(zonaDeIntimidacion[i][j] == 3){
						//int posiciones = 0;
						//while(posiciones < 8){
						try{
							if(zonaDeIntimidacion[i-1][j] == 1){ /// Izq del Gladiador
								disparosPorTorre += 5;
							}
						}
						catch(const std::out_of_range& oor){}

						try{
							if(zonaDeIntimidacion[i+1][j] == 1){ /// Der del Gladiador
								disparosPorTorre += 5;
							}
						}
						catch(const std::out_of_range& oor){}

						try{
							if(zonaDeIntimidacion[i][j-1] == 1){ /// Debajo del Gladiador
								disparosPorTorre += 5;
							}
						}
						catch(const std::out_of_range& oor){}

						try{
							if(zonaDeIntimidacion[i][j+1] == 1){ /// Arriba del Gladiador
								disparosPorTorre += 5;
							}
						}
						catch(const std::out_of_range& oor){}

						try{
							if(zonaDeIntimidacion[i-1][j-1] == 1){ /// Diagonal Izq Inferiror del Gladiador
								disparosPorTorre += 5;
							}
						}
						catch(const std::out_of_range& oor){}

						try{
							if(zonaDeIntimidacion[i-1][j+1] == 1){ /// Diagonal Izq Superior del Gladiador
								disparosPorTorre += 5;
							}
						}
						catch(const std::out_of_range& oor){}

						try{
							if(zonaDeIntimidacion[i+1][j-1]){ /// Diagonal Der Inferiror del Gladiador
								disparosPorTorre += 5;
							}
						}
						catch(const std::out_of_range& oor){}

						try{
							if(zonaDeIntimidacion[i+1][j+1] == 1){ /// Diagonal Der Superior del Gladiador
								disparosPorTorre += 5;
							}
						}
						catch(const std::out_of_range& oor){}


						//posiciones++;
						//}

					}
				}
			}

			// display the zonaDeIntimidacion with the path
			//cout << "Mapa con Torres = 0 " << endl;

			cout<<"CAMINO: "<< numeroPartidas + 1<<endl;
			for (j = JDIM - 1; j >= 0; j--) {
				for (i = 0; i < IDIM; i++) {
					if (zonaDeIntimidacion[i][j] == 0) {
						cout << " : "; // Espacio Libre/vacio
						//resultado += ":";
					} else if (zonaDeIntimidacion[i][j] == 1) {
						cout << " O "; // Torre
					} else if (zonaDeIntimidacion[i][j] == 2) {
						cout << " I "; // Punto de entrada/inicial
					} else if (zonaDeIntimidacion[i][j] == 3) {
						cout << " * "; // Camino marcado por el PathFinding
					} else if (zonaDeIntimidacion[i][j] == 4) {
						cout << " F "; // Punto de salida/final
					}
				}
				cout << endl;
			}
			cout << "\nGladiador con resistencia de: "<< resistenciaGLadiador << " DIsparos: "<<disparosPorTorre<<endl;
			if(resistenciaGLadiador - disparosPorTorre > 0){
				cout << "GLADIADOR DIGNO DE IR AL COLISEO, Resistencia actual: " <<resistenciaGLadiador - disparosPorTorre<< endl;
			}else{
				cout << "GLadiador desaparecido en La Zona de INtimidacion, vida registrada: " <<resistenciaGLadiador - disparosPorTorre<< endl;
			}

			for(int i = 0; i < 10; i++){
				for(int j = 0; j < 5; j++){
					if(zonaDeIntimidacion[i][j] == 3){
						zonaDeIntimidacion[i][j] = 0;
					}
				}
			}

		} else {
			cout << "NO HAY CAMINO CARAJO!" << endl;
		}
		numeroPartidas++;
	}











	int numeroPartidasB = 0;



		AStar ObjPathFindingB;
		srand(time(0));

		while(numeroPartidasB < 1) {     /// DE AQUI SE LLAMA AL RESTUFULL, SE OBTIENE EL GLADIADOR,
			/// SE HACE PASAR POR LA ZONA DE INTIMIDACION, VE SI SE LLEGA
			/// AL COLISEO Y SE REPITE

			//int resistenciaGLadiador = rand()%100;
			int disparosPorTorre = 0;


			string pathB = ObjPathFindingB.pathFindB(Location(iStart, jStart), Location(iEnd, jEnd));

			// cout << "Tamaño Matriz: "<< IDIM<< "," << JDIM << endl;
			cout << "Inicio: " << iStart << "," << jStart << endl;
			cout << "Final: " << iEnd << "," << jEnd << endl;

			// get the path
			//    string path = pathFind(Location(iStart, jStart), Location(iEnd, jEnd)); // Run bitch!

			cout << endl;
			cout << "path: " << pathB << "\n" << endl;


			// follow the path on the zonaDeIntimidacion and display it
			if (pathB.length() > 0) {
				char c;
				int m, n;
				int i = iStart;
				int j = jStart;
				zonaDeIntimidacionB[i][j] = 2; ///Punto de Entrada
				for (m = 0; m < pathB.length(); m++) {
					c = pathB.at(m);
					n = atoi(&c);
					i = i + iDir[n];
					j = j + jDir[n];
					zonaDeIntimidacionB[i][j] = 3;
				}
				zonaDeIntimidacionB[i][j] = 4; /// Punto de salida


				for(int i = 0; i < 10; i++){
					for(int j = 0; j < 5; j++){
						if(zonaDeIntimidacionB[i][j] == 3){
							//int posiciones = 0;
							//while(posiciones < 8){
							try{
								if(zonaDeIntimidacionB[i-1][j] == 1){ /// Izq del Gladiador
									disparosPorTorre += 5;
								}
							}
							catch(const std::out_of_range& oor){}

							try{
								if(zonaDeIntimidacionB[i+1][j] == 1){ /// Der del Gladiador
									disparosPorTorre += 5;
								}
							}
							catch(const std::out_of_range& oor){}

							try{
								if(zonaDeIntimidacionB[i][j-1] == 1){ /// Debajo del Gladiador
									disparosPorTorre += 5;
								}
							}
							catch(const std::out_of_range& oor){}

							try{
								if(zonaDeIntimidacionB[i][j+1] == 1){ /// Arriba del Gladiador
									disparosPorTorre += 5;
								}
							}
							catch(const std::out_of_range& oor){}

							try{
								if(zonaDeIntimidacionB[i-1][j-1] == 1){ /// Diagonal Izq Inferiror del Gladiador
									disparosPorTorre += 5;
								}
							}
							catch(const std::out_of_range& oor){}

							try{
								if(zonaDeIntimidacionB[i-1][j+1] == 1){ /// Diagonal Izq Superior del Gladiador
									disparosPorTorre += 5;
								}
							}
							catch(const std::out_of_range& oor){}

							try{
								if(zonaDeIntimidacionB[i+1][j-1]){ /// Diagonal Der Inferiror del Gladiador
									disparosPorTorre += 5;
								}
							}
							catch(const std::out_of_range& oor){}

							try{
								if(zonaDeIntimidacionB[i+1][j+1] == 1){ /// Diagonal Der Superior del Gladiador
									disparosPorTorre += 5;
								}
							}
							catch(const std::out_of_range& oor){}


							//posiciones++;
							//}

						}
					}
				}

				// display the zonaDeIntimidacion with the path
				//cout << "Mapa con Torres = 0 " << endl;

				cout<<"CAMINO: "<< numeroPartidasB + 1<<endl;
				for (j = JDIM - 1; j >= 0; j--) {
					for (i = 0; i < IDIM; i++) {
						if (zonaDeIntimidacionB[i][j] == 0) {
							cout << " : "; // Espacio Libre/vacio
							//resultado += ":";
						} else if (zonaDeIntimidacionB[i][j] == 1) {
							cout << " O "; // Torre
						} else if (zonaDeIntimidacionB[i][j] == 2) {
							cout << " I "; // Punto de entrada/inicial
						} else if (zonaDeIntimidacionB[i][j] == 3) {
							cout << " * "; // Camino marcado por el PathFinding
						} else if (zonaDeIntimidacionB[i][j] == 4) {
							cout << " F "; // Punto de salida/final
						}
					}
					cout << endl;
				}
				cout << "\nGladiador con resistencia de: "<< resistenciaGLadiadorB << " DIsparos: "<<disparosPorTorre<<endl;
				if(resistenciaGLadiadorB - disparosPorTorre > 0){
					cout << "GLADIADOR DIGNO DE IR AL COLISEO, Resistencia actual: " <<resistenciaGLadiadorB - disparosPorTorre<< endl;
				}else{
					cout << "GLadiador desaparecido en La Zona de INtimidacion, vida registrada: " <<resistenciaGLadiadorB - disparosPorTorre<< endl;
				}

				for(int i = 0; i < 10; i++){
					for(int j = 0; j < 5; j++){
						if(zonaDeIntimidacionB[i][j] == 3){
							zonaDeIntimidacionB[i][j] = 0;
						}
					}
				}

			} else {
				cout << "NO HAY CAMINO CARAJO!" << endl;
			}
			numeroPartidasB++;
		}







}
