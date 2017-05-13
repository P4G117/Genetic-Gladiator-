package server.geneticGladiator;

/**
 * Clase para calcular el fitness de los individuos
 * @author Nosotros
 *
 */
public class Individuo {
	private int[] bufferDeIndividuos;
	private int fitness;
	private int fitnessTotal;
	private static final int tamanoDeCromosoma = 18;
	
	/**
	 * COnstructor de la clase.
	 * @param bufferDeIndividuos
	 */
	public Individuo(int[] bufferDeIndividuos){
		this.bufferDeIndividuos = bufferDeIndividuos;		
	}
	
	/**
	 * Método para calcular fitness.
	 * @return int Fitness obtenido
	 */
	public int calcularFitness(){
		
		for(int j = 0; j < 9; j++ ){
			if(getBufferDeIndividuos()[j] == 1){
				setFitness(getFitness() + 33);
			}
		}		
		setFitnessTotal((getFitness()*100)/300);			
		return getFitnessTotal();
	}
	
	public int[] getBufferDeIndividuos() {
		return bufferDeIndividuos;
	}

	public void setBufferDeIndividuos(int[] bufferDeIndividuos) {
		this.bufferDeIndividuos = bufferDeIndividuos;
	}

	public int getFitness() {
		return fitness;
	}

	public void setFitness(int fitness) {
		this.fitness = fitness;
	}

	public static int getTamanodecromosoma() {
		return tamanoDeCromosoma;
	}
	
	public int getFitnessTotal() {
		return fitnessTotal;
	}

	public void setFitnessTotal(int fitnessTotal) {
		this.fitnessTotal = fitnessTotal;
	}
}