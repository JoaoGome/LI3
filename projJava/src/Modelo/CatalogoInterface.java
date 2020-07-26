package Modelo;

import java.util.TreeSet;

public interface CatalogoInterface
{
	
	public void init ();
    public void addElemento(String codigo);
    public boolean checkExiste (String codigo);
    public TreeSet <String> getCatalogo ();
    public int getSize ();
}

