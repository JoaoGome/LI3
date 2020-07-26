package Auxiliar;
import java.util.ArrayList;
import java.util.TreeSet;

public class CodigoNumeroPar {

	private TreeSet <Integer> valores;
	private ArrayList <String> codigos;
	private ArrayList <Integer> valoresArray;
		
	public void initQuery5 (TreeSet <Integer> numeros, ArrayList <String> codigos)
	{
		this.valores = numeros;
		this.codigos = codigos;
	}
	
	public void initQuery6 (ArrayList <String> codigos, ArrayList <Integer> numeros)
	{
		this.codigos = codigos;
		this.valoresArray = numeros;
	}
		
	@SuppressWarnings("unchecked")
	public TreeSet<Integer> getValores ()
	{
		return (TreeSet<Integer>) this.valores.clone();
	}
		
	@SuppressWarnings("unchecked")
	public ArrayList<String> getCodigos()
	{
		return (ArrayList<String>) this.codigos.clone();
	}	
	
	@SuppressWarnings("unchecked")
	public ArrayList <Integer> getValoresArray ()
	{
		return (ArrayList<Integer>) this.valoresArray.clone();
	}
}