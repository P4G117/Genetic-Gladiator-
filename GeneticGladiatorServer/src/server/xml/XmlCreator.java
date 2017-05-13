package server.xml;

import java.io.FileWriter;
import java.io.IOException;

import server.geneticGladiator.Poblaciones;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Text;
import org.xml.sax.SAXException;

import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

/**
* Clase para leer y escribir XML.
 * @author Nosotros
 *
 */
public class XmlCreator {
	private String inicioNombre;
	public XmlCreator(){
		
	}
	
	/**
	 * Método para leer XML.
	 * @param pNumPobla
	 * @param pNumGen
	 * @return Document Documento XML con datos solicitados
	 * @throws ParserConfigurationException
	 * @throws SAXException
	 * @throws IOException
	 */
	public Document leerXML(int pNumPobla,int pNumGen) throws ParserConfigurationException, SAXException, IOException{
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		DocumentBuilder builder;
		Document doc; 
		builder = factory.newDocumentBuilder();
		doc = builder.parse("/home/dead/workspace/GeneticGladiatorServer/poblacion"+String.valueOf(pNumPobla)+"/Gladiadorgeneracion"+String.valueOf(pNumGen)+".xml");
		return doc;
	}
	
	/**
	 * Método para escribir los XML.
	 * @param pPobla
	 * @param numPobla
	 * @param pNumGen
	 * @throws ParserConfigurationException
	 * @throws IOException
	 * @throws TransformerException
	 */
	public void crearXML(Poblaciones pPobla,int numPobla,int pNumGen) throws ParserConfigurationException, IOException, TransformerException{
		if(numPobla == 1){
			inicioNombre = "a";
		}else{
			inicioNombre = "b";
		}
		Poblaciones poblacion1 = pPobla;
		poblacion1.verificarFitness();
		poblacion1.SelectionSort();
		poblacion1.crossover();
		poblacion1.generarDatos();

		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		DocumentBuilder builder = factory.newDocumentBuilder();
		Document doc = builder.newDocument();
		

		Element inicio = doc.createElement("Poblacion-"+String.valueOf(numPobla));
		doc.appendChild(inicio);

		Element numeroGen = doc.createElement("NumeroGeneracion");
		inicio.appendChild(numeroGen);
		Text numeroGentxt = doc.createTextNode(String.valueOf(poblacion1.getNumeroDeGeneracion()));
		numeroGen.appendChild(numeroGentxt);
		
		Element generacion = doc.createElement("Generacion"+String.valueOf(poblacion1.getNumeroDeGeneracion()));
		inicio.appendChild(generacion);
		for(int i=0;i<poblacion1.getTamanodepoblacion();i++){
			Element IndiNombre = doc.createElement("Nombre");
			generacion.appendChild(IndiNombre);
			Text IndiNombretxt = doc.createTextNode(inicioNombre+String.valueOf(i));
			IndiNombre.appendChild(IndiNombretxt);
			Element individuo = doc.createElement("Individuo");
			generacion.appendChild(individuo);
			int[] cromosomaInd = poblacion1.getBufferPoblacion()[0][i];
			String genes = "";
			for(int j=0;j<poblacion1.getTamanodecromosoma();j++){
				int gen = cromosomaInd[j];
				genes += String.valueOf(gen);
			}
			Text individuos = doc.createTextNode(genes);
			individuo.appendChild(individuos);
			
			Element fitness = doc.createElement("Fitness");
			Text fit = doc.createTextNode(String.valueOf(poblacion1.getBufferFitness()[i]));
			fitness.appendChild(fit);
			generacion.appendChild(fitness);
		}

		Element muta = doc.createElement("Mutaciones");
		inicio.appendChild(muta);
		Text mutaxtx = doc.createTextNode(String.valueOf(String.valueOf(poblacion1.getIndividuosAMutar())));
		muta.appendChild(mutaxtx);

		Element inver = doc.createElement("Inversiones");
		inicio.appendChild(inver);
		Text invertxt = doc.createTextNode(String.valueOf(poblacion1.getIndividuosConInversion()));
		inver.appendChild(invertxt);

		Element result = doc.createElement("ResultadoFinal");
		inicio.appendChild(result);
		Text resultxt = doc.createTextNode("aún no se sabe");
		result.appendChild(resultxt);
		


		TransformerFactory transformerFactory = TransformerFactory.newInstance();
		Transformer transformer  = transformerFactory.newTransformer();
		transformer.setOutputProperty(OutputKeys.INDENT, "yes");
		transformer.setOutputProperty(OutputKeys.OMIT_XML_DECLARATION, "no");
		DOMSource source = new DOMSource(doc);

		StreamResult stream = new StreamResult(new FileWriter("/home/dead/workspace/GeneticGladiatorServer/poblacion"+String.valueOf(numPobla)+"/generacion"+String.valueOf(pNumGen)+".xml"));
		transformer.transform(source, stream);
		
		DocumentBuilderFactory factory2 = DocumentBuilderFactory.newInstance();
		DocumentBuilder builder2 = factory2.newDocumentBuilder();
		Document docGlad = builder2.newDocument();
		
/////////
		Element gladiador = docGlad.createElement("Gladiador");
		docGlad.appendChild(gladiador);
		
		Element nombreGlad = docGlad.createElement("Nombre");
		gladiador.appendChild(nombreGlad);
		Text nombreGladtxt = docGlad.createTextNode(inicioNombre+String.valueOf(poblacion1.getTamanodepoblacion()-1));
		nombreGlad.appendChild(nombreGladtxt);
		
		Element genesGlad = docGlad.createElement("Genes");
		gladiador.appendChild(genesGlad);
		String genesGladiator = "";
		for(int j=0;j<poblacion1.getTamanodecromosoma();j++){
			int genG = poblacion1.getBufferPoblacion()[0][poblacion1.getTamanodepoblacion()-1][j];
			genesGladiator += String.valueOf(genG);
		}
		Text genesGladtxt = docGlad.createTextNode(String.valueOf(genesGladiator));
		genesGlad.appendChild(genesGladtxt);
		
		Element fitnessGlad = docGlad.createElement("Fitness");
		gladiador.appendChild(fitnessGlad);
		Text fitnessGladtxt = docGlad.createTextNode(String.valueOf(poblacion1.getBufferFitness()[poblacion1.getTamanodepoblacion()-1]));
		fitnessGlad.appendChild(fitnessGladtxt);
		
		Element resisManos = docGlad.createElement("Resistencia-Manos");
		gladiador.appendChild(resisManos);
		Text resisManostxt = docGlad.createTextNode(String.valueOf(poblacion1.getResisManos()));
		resisManos.appendChild(resisManostxt);
		
		Element resisPies = docGlad.createElement("Resistencia-Pies");
		gladiador.appendChild(resisPies);
		Text resisPiestxt = docGlad.createTextNode(String.valueOf(poblacion1.getResisPies()));
		resisPies.appendChild(resisPiestxt);
		
		Element resisCuerpo = docGlad.createElement("Resistencia-Cuerpo");
		gladiador.appendChild(resisCuerpo);
		Text resisCuerpotxt = docGlad.createTextNode(String.valueOf(poblacion1.getResisCuerpo()));
		resisCuerpo.appendChild(resisCuerpotxt);
		
		Element resisTotal = docGlad.createElement("Resistencia-Total");
		gladiador.appendChild(resisTotal);
		Text resisTotaltxt = docGlad.createTextNode(String.valueOf(poblacion1.getBufferFitness()[(poblacion1.getTamanodepoblacion()-1)]));
		resisTotal.appendChild(resisTotaltxt);
		
		Element fuerzaManos = docGlad.createElement("Fuerza-Manos");
		gladiador.appendChild(fuerzaManos);
		Text fuerzaManostxt = docGlad.createTextNode(String.valueOf(poblacion1.getFuerzaManos()));
		fuerzaManos.appendChild(fuerzaManostxt);
		
		Element fuerzaPies = docGlad.createElement("Fuerza-Pies");
		gladiador.appendChild(fuerzaPies);
		Text fuerzaPiestxt = docGlad.createTextNode(String.valueOf(poblacion1.getFuerzaPies()));
		fuerzaPies.appendChild(fuerzaPiestxt);
		
		Element fuerzaCuerpo = docGlad.createElement("Fuerza-Cuerpo");
		gladiador.appendChild(fuerzaCuerpo);
		Text fuerzaCuerpotxt = docGlad.createTextNode(String.valueOf(poblacion1.getFuerzaCuerpo()));
		fuerzaCuerpo.appendChild(fuerzaCuerpotxt);
//////////

		TransformerFactory transformerFactory2 = TransformerFactory.newInstance();
		Transformer transformer2  = transformerFactory2.newTransformer();
		transformer2.setOutputProperty(OutputKeys.INDENT, "yes");
		transformer2.setOutputProperty(OutputKeys.OMIT_XML_DECLARATION, "no");
		DOMSource source2 = new DOMSource(docGlad);

		StreamResult stream2 = new StreamResult(new FileWriter("/home/dead/workspace/GeneticGladiatorServer/poblacion"+String.valueOf(numPobla)+"/Gladiadorgeneracion"+String.valueOf(pNumGen)+".xml"));
		transformer.transform(source2, stream2);
	}
	
	/**
	 * Método para escribir en XML cual generación ganó
	 * @param pNumPobla
	 * @param pNumGen
	 */
	public void editGanador(int pNumPobla, int pNumGen){
		
	}

}
