package geneticGladiator;

public class Individuo {
	
	private int[] bufferDeIndividuos;
	private int fitness;
	private int fitnessTotal;
	private static final int tamanoDeCromosoma = 18;
	
	//Constructor
	public Individuo(int[] bufferDeIndividuos){

		this.bufferDeIndividuos = bufferDeIndividuos;		
	}

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