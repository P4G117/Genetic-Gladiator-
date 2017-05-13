package server.restful;

import java.io.IOException;

import javax.ws.rs.Consumes;
import javax.ws.rs.GET;
import javax.ws.rs.POST;
import javax.ws.rs.Path; 
import javax.ws.rs.Produces; 
import javax.ws.rs.core.MediaType;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;

import org.w3c.dom.Document;
import org.xml.sax.SAXException;

import server.geneticGladiator.Poblaciones;
import server.xml.XmlCreator;

/**
 * Clase para hacer la conexión con el servidor.
 * @author Nosotros
 *
 */
@Path("conx")
public class Conexion {
	private XmlCreator creator;
	int numPobla;
	public Conexion() {
		creator = new XmlCreator();
	}
	
	/**
	 * 
	 * @return String Mensaje de verificación
	 * @throws ParserConfigurationException
	 * @throws IOException
	 * @throws TransformerException
	 */
	@GET
	@Produces(MediaType.TEXT_PLAIN)
	@Path("cargar")
	public String cargar() throws ParserConfigurationException, IOException, TransformerException{
		Poblaciones pobla1 = new Poblaciones();
		Poblaciones pobla2 = new Poblaciones();
		for(int cont1=0;cont1 <= 100;cont1++){
			creator.crearXML(pobla1,1,cont1);
			creator.crearXML(pobla2,2,cont1);
		}
		return "Servidor en linea";
	}
	
	/**
	 * Método para enviar datos de los gladiadores.
	 * @param pDato
	 * @return Document Datos del gladiador que se pidió.
	 * @throws ParserConfigurationException
	 * @throws IOException
	 * @throws TransformerException
	 * @throws SAXException
	 */
	@POST
	@Consumes(MediaType.TEXT_PLAIN)
	@Produces(MediaType.TEXT_XML)
	@Path("glad1")
	public Document enviarGladiador1(String pDato) throws ParserConfigurationException, IOException, TransformerException, SAXException{
		int numero = Integer.parseInt(pDato);
		Document doc = creator.leerXML(1,numero);
		return doc;
	}
	
	/**
	 * Método para enviar datos de los gladiadores.
	 * @param pDato
	 * @return Document Datos del gladiador que se pidió.
	 * @throws ParserConfigurationException
	 * @throws IOException
	 * @throws TransformerException
	 * @throws SAXException
	 */
	@POST
	@Consumes(MediaType.TEXT_PLAIN)
	@Produces(MediaType.TEXT_XML)
	@Path("glad2")
	public Document enviarGladiador2(String pDato) throws ParserConfigurationException, IOException, TransformerException, SAXException{
		int numero = Integer.parseInt(pDato);
		Document doc = creator.leerXML(2,numero);
		return doc;
	}
	
	/**
	 * Método para guardar cual generación ganó.
	 * @param pNumGen
	 * @return
	 * @throws ParserConfigurationException
	 * @throws IOException
	 * @throws TransformerException
	 */
	@GET
	@Produces(MediaType.TEXT_PLAIN)
	@Path("ganador")
	public String guardarGanador(String pNumGen) throws ParserConfigurationException, IOException, TransformerException{
		int numero = Integer.parseInt(pNumGen);
		creator.editGanador(numPobla, numero);
		return "Listo";
	}
	
}
