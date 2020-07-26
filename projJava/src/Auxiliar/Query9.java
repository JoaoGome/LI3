package Auxiliar;

import java.util.ArrayList;

public class Query9 {

	private ArrayList <String> clientes;
	private ArrayList <Float> faturado;
	
	public void init (ArrayList <String> q1, ArrayList <Float> q2)
	{
		this.clientes = q1;
		this.faturado = q2;
	}
	
	@SuppressWarnings("unchecked")
	public ArrayList <String> getClientes()
	{
		return (ArrayList<String>) this.clientes.clone();
	}

	
	@SuppressWarnings("unchecked")
	public ArrayList <Float> getFaturado ()
	{
		return (ArrayList<Float>) this.faturado.clone();
	}
}
