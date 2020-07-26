
import java.io.IOException;

public interface ControladorInterface {
	
	public void init ();
	public void start () throws IOException, ClassNotFoundException;
	public void saveToFile (String file) throws IOException;
	public void loadFromFile (String file) throws IOException, ClassNotFoundException;

}
