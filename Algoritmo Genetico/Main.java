package geneticGladiator;

import geneticGladiator.Poblaciones;

class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int numeroPoblaciones = 2000;
		int generacion = 1;
		
		Poblaciones poblacion1 = new Poblaciones(); //Se crea la poblacion inicial	
		Poblaciones poblacion2 = new Poblaciones();
		
		while(generacion <= numeroPoblaciones ){ //Simula peticiones del RESTFul API
			
			System.out.print("\n···········Poblacion 1··········");
			
			poblacion1.verificarFitness();
			poblacion1.SelectionSort();
			poblacion1.crossover();		
			System.out.println("·········Generacion " +generacion+ "··············\n");
			poblacion1.generarDatos();			
			System.out.println();
			
			System.out.print("\n···········Poblacion 2··········");
			
			poblacion2.verificarFitness();
			poblacion2.SelectionSort();
			poblacion2.crossover();		
			System.out.println("·········Generacion " +generacion+ "··············\n");
			poblacion2.generarDatos();			
			System.out.println();
			
			generacion++;
		}		
		System.out.println("\nTERMINADO APLICACION\n");							
	}
}
