
import java.io.IOException;

public class GestVendasAPPMVC {
		
	public static void main (String args[]) throws IOException, ClassNotFoundException
	{
		ControladorInterface controlador = new Controlador();
		controlador.init();
		controlador.start();
	}
}
