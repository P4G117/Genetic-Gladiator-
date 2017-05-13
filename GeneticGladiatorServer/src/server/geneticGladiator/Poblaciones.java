package server.geneticGladiator;

import java.util.Random;

import javax.xml.bind.annotation.XmlRootElement;

import server.geneticGladiator.Individuo;

/**
 * Clase para crear las poblaciones.
 * @author Nosotros
 *
 */
@XmlRootElement
public class Poblaciones {

	private int[][][] bufferPoblacion;
	private int[] bufferFitness;
	private int tamanoDePoblacion = 90;
	private static final int tamanoDeCromosoma = 18;
	private int gen;
	private int individuo; 
	private static final int mutacion = 50;
	private static Random aleatoriedad = new Random();
	private int numeroDeGeneracion = 0;
	private int individuosAMutar = 0;
	private int individuosConInversion = 0;	

	private int resisManos,resisPies,resisCuerpo;
	private int fuerzaManos,fuerzaPies,fuerzaCuerpo;


	public int getResisManos() {
		return resisManos;
	}

	public void setResisManos(int resisManos) {
		this.resisManos = resisManos;
	}

	public int getResisPies() {
		return resisPies;
	}

	public void setResisPies(int resisPies) {
		this.resisPies = resisPies;
	}

	public int getResisCuerpo() {
		return resisCuerpo;
	}

	public void setResisCuerpo(int resisCuerpo) {
		this.resisCuerpo = resisCuerpo;
	}

	public int getFuerzaManos() {
		return fuerzaManos;
	}

	public void setFuerzaManos(int fuerzaManos) {
		this.fuerzaManos = fuerzaManos;
	}

	public int getFuerzaPies() {
		return fuerzaPies;
	}

	public void setFuerzaPies(int fuerzaPies) {
		this.fuerzaPies = fuerzaPies;
	}

	public int getFuerzaCuerpo() {
		return fuerzaCuerpo;
	}

	public void setFuerzaCuerpo(int fuerzaCuerpo) {
		this.fuerzaCuerpo = fuerzaCuerpo;
	}

	/**
	 * Constructor de la clase.
	 */
	public Poblaciones(){
		this.bufferFitness = new int[getTamanodepoblacion()];
		this.bufferPoblacion = new int[1][getTamanodepoblacion()][getTamanodecromosoma()];

		// Creando la Poblacion Inicial Y Guardandolos en Memoria
		for(individuo = 0; individuo < tamanoDePoblacion; individuo++){
			for(gen = 0; gen < getTamanodecromosoma(); gen++){
				if(gen<9){
					if(((int)(aleatoriedad.nextDouble()*100+0))<80){

						bufferPoblacion[0][individuo][gen]=0;
					}else{
						bufferPoblacion[0][individuo][gen]=1;
					}
				}else{
					if(((int)(aleatoriedad.nextDouble()*100+0))<60){

						bufferPoblacion[0][individuo][gen]=0;
					}else{
						bufferPoblacion[0][individuo][gen]=1;
					}
				}
			}
		}
	}
	
	/**
	 * Método para verificar fitness.
	 */
	public void verificarFitness(){

		setNumeroDeGeneracion(getNumeroDeGeneracion() + 1); //Control del #Generaciones
		for(int i = 0; i < getTamanodepoblacion(); i++ ){
			Individuo Leonidas = new Individuo(bufferPoblacion[0][i]); 
			getBufferFitness()[i] = Leonidas.calcularFitness();
		}
	}	
	
	/**
	 * Método para ordenar los fitness de los gladiadores
	 * de menor a mayor.
	 */
	public void SelectionSort(){
		int[] arr = getBufferFitness(); 
		for (int i = 0; i < arr.length - 1; i++){
			int index = i;
			for (int j = i + 1; j < arr.length; j++){
				if (arr[j] < arr[index])
					index = j;
			}
			int smallerNumber = arr[index];  // Ordena la memoria de Fitness
			arr[index] = arr[i];
			arr[i] = smallerNumber;

			int []aux = getBufferPoblacion()[0][index];      // Simultaneamente ordena los individuos 
			getBufferPoblacion()[0][index] = getBufferPoblacion()[0][i]; // de la Poblacion segun su Fitness
			getBufferPoblacion()[0][i] = aux;
		}         
	}	
	
	/**
	 * Método para hacer el cruce entre los nuevos individuos.
	 */
	public void crossover(){

		int padre = (getTamanodepoblacion()-21);
		int madre = (getTamanodepoblacion()-1);//Ultima Posicion de la Poblacion


		int[][][] bufferPoblacionesAux = new int[1][tamanoDePoblacion + 10][18];

		for(individuo = 0; individuo < getTamanodepoblacion(); individuo++){
			for(gen = 0; gen < getTamanodecromosoma(); gen++){
				bufferPoblacionesAux[0][individuo][gen] = getBufferPoblacion()[0][individuo][gen];
			}
		}

		setBufferPoblacion(bufferPoblacionesAux); // set
		setTamanoDePoblacion((getTamanodepoblacion() + 10));//Aumentamos el tamaño de la Poblacion		

		int j = 0;
		for (int i = getTamanodepoblacion()-10; i < getTamanodepoblacion(); i++){
			while(j < 6){
				getBufferPoblacion()[0][i][j] = getBufferPoblacion()[0][madre][j];            		
				j++;
			}
			madre--;
			j=6;
			while(j < 18){
				getBufferPoblacion()[0][i][j] = getBufferPoblacion()[0][padre][j];            		
				j++;
			}
			padre++;
			j=0;
		}
		// Si hay mutacion mutacion, entonces
		if((int)(aleatoriedad.nextDouble()*100 + 1) < getMutacion()){  
			if((int)(aleatoriedad.nextDouble()*2 + 0) == 1){ // Se elige entro los 2 tipos   
				mutacionGenetica();                         // de mutaciones
			}else{
				inversion();
			}	 
		}

		int[] bufferFitnessAux = new int[getTamanodepoblacion()];
		for(int i = 0; i < getTamanodepoblacion()-10; i++ ){
			bufferFitnessAux[i] = getBufferFitness()[i];
		}
		setBufferFitness(bufferFitnessAux);

		for(int i = (getTamanodepoblacion()-10); i < getTamanodepoblacion(); i++ ){
			Individuo Leonidas = new Individuo(bufferPoblacion[0][i]); 
			getBufferFitness()[i] = Leonidas.calcularFitness();
		}		
		SelectionSort();
	}
	
	/**
	 * Método para realizar las mutaciones.
	 */
	public void mutacionGenetica(){

		setIndividuosAMutar((int)(aleatoriedad.nextDouble()*10 + 0));
		for(int i = (getTamanodepoblacion()-10); i < getTamanodepoblacion()-getIndividuosAMutar(); i++){
			for(int j = 0; j < 18; j++ ){
				if(getBufferPoblacion()[0][i][j] == 1){
					getBufferPoblacion()[0][i][j] = 0;
				}else{
					getBufferPoblacion()[0][i][j] = 0;
				}
			}
		}		
	}
	
	/**
	 * Método para hacer mutación del tipo inversión.
	 */
	public void inversion(){

		setIndividuosConInversion((int)(aleatoriedad.nextDouble()*10 + 0));
		for(int i = (getTamanodepoblacion()-10); i < getTamanodepoblacion()-getIndividuosConInversion(); i++){
			int index = 8;			
			for(int j = 1; j <= 5; j++ ){					
				int auxiliar = getBufferPoblacion()[0][i][j]; // Swap Inversor
				getBufferPoblacion()[0][i][j] = getBufferPoblacion()[0][i][index];
				getBufferPoblacion()[0][i][index] = auxiliar;
				index--;
			}
		}		
	}
	
	/**
	 * Método para generar datos a partir del material genético de
	 * los gladiadores.
	 */
	public void generarDatos(){ //Para el XML
		//Traduccion del Material Genetico
		int cont = 0;
		for(int k = 0; k < 18; k++ ){				 
			cont += getBufferPoblacion()[0][(getTamanodepoblacion()-1)][k];
			if(k==2){ 
				cont *=33;
				setResisManos(cont);
				cont = 0;
			}
			if(k==5){
				cont *=33;
				setResisPies(cont);
				cont = 0;
			}
			if(k==8){
				cont *=33;
				setResisCuerpo(cont);
				cont = 0;
			}
			if(k==11){
				cont *=33;
				setFuerzaManos(cont);
				cont = 0;
			}
			if(k==14){
				cont *=33;
				setFuerzaPies(cont);
				cont = 0;
			}
			if(k==17){
				cont *=33;
				setFuerzaCuerpo(cont);
				cont = 0;
			}
		}
		
		//Fitness Promedio
		int Prom = 0;
		for(int p = 0; p < getTamanodepoblacion(); p++){
			Prom += getBufferFitness()[p];
		}
		System.out.print("Promedio del Fitness de la Poblacion:" + (Prom/getTamanodepoblacion()));
	}

	public int[][][] getBufferPoblacion() {
		return bufferPoblacion;
	}

	public void setBufferPoblacion(int[][][] bufferPoblacion) {
		this.bufferPoblacion = bufferPoblacion;
	}

	public int[] getBufferFitness() {
		return bufferFitness;
	}

	public void setBufferFitness(int[] bufferFitness) {
		this.bufferFitness = bufferFitness;
	}

	public int[] mejorGladiador(){
		return bufferPoblacion[0][getTamanodepoblacion()-1];
	}

	public int getTamanodepoblacion() {
		return tamanoDePoblacion;
	}

	public void setTamanoDePoblacion(int tamanoDePoblacion) {
		this.tamanoDePoblacion = tamanoDePoblacion;
	}

	public static int getTamanodecromosoma() {
		return tamanoDeCromosoma;
	}


	public int getNumeroDeGeneracion() {
		return numeroDeGeneracion;
	}


	public void setNumeroDeGeneracion(int numeroDeGeneracion) {
		this.numeroDeGeneracion = numeroDeGeneracion;
	}

	public static int getMutacion() {
		return mutacion;
	}

	public int getIndividuosAMutar() {
		return individuosAMutar;
	}

	public void setIndividuosAMutar(int individuosAMutar) {
		this.individuosAMutar = individuosAMutar;
	}

	public int getIndividuosConInversion() {
		return individuosConInversion;
	}

	public void setIndividuosConInversion(int individuosConInversion) {
		this.individuosConInversion = individuosConInversion;
	}
}