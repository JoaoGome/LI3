package Modelo;

import java.io.Serializable;
import java.util.TreeSet;


public class Catalogo implements CatalogoInterface, Serializable {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private TreeSet <String> lista;
	
	//funcao que inicia o TreeSet
	public void init () 
	{
		this.lista = new TreeSet <> ();
	}
	
	//funcao que recebe um codigo e adiciona à lista
	public void addElemento (String codigo)
	{
		this.lista.add(codigo);
	}
	
	//funcao que dá check se um codigo existe na nossa lista de codigos
	public boolean checkExiste (String codigo)
	{
		boolean result = this.lista.contains(codigo);
		return result;
	}
	
	@SuppressWarnings("unchecked")
	public TreeSet <String> getCatalogo ()
	{
		TreeSet <String> listaCopia = new TreeSet <>();

		listaCopia = (TreeSet <String>)this.lista.clone();
		return listaCopia;
		
	}
	
	public int getSize ()
	{
		return this.lista.size();
	}

}
