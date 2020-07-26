package View;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.TreeSet;

import Auxiliar.CodigoNumeroPar;
import Auxiliar.GestaoVendasData;
import Auxiliar.Query4;
import Auxiliar.Query9;

public interface ViewInterface {

	public int mainMenu ();
	public int menuEstasticas ();
	public int menuInterativas ();
	
	public String [] askFicheiros ();
	
	
	public void showQueryE1 (GestaoVendasData lista);
	public void showQueryE21 (int [] lista);
	public void showQueryE22 (float [][] lista);
	public void showQueryE23 (int [][] lista);
	public void showQueryI1 (TreeSet <String> lista);
	public void showQueryI2 (ArrayList <Integer> lista);
	public void showQueryI3 (ArrayList <Float> lista);
	public void showQueryI4 (Query4 lista);
	public void showQueryI5 (CodigoNumeroPar lista);
	public void showQueryI6 (CodigoNumeroPar lista);
	public void showQueryI7 (ArrayList <String> lista);
	public void showQueryI8 (CodigoNumeroPar lista);
	public void showQueryI9 (Query9 lista);
	public void showQueryI10 (ArrayList<ArrayList<HashMap<String,Float>>> lista);
	
}
