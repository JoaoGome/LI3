package Auxiliar;

import java.util.ArrayList;

public class Query4 {
	
	private ArrayList <Integer> quantidadeVendas;
	private ArrayList <Float> faturado;
	private ArrayList <Integer> quantidadeClientes;
	
	public void init (ArrayList <Integer> q1, ArrayList <Float> q2, ArrayList <Integer> q3)
	{
		this.quantidadeClientes = q3;
		this.faturado = q2;
		this.quantidadeVendas = q1;
	}
	
	@SuppressWarnings("unchecked")
	public ArrayList <Integer> getVendas ()
	{
		return (ArrayList<Integer>) this.quantidadeVendas.clone();
	}
	
	@SuppressWarnings("unchecked")
	public ArrayList <Integer> getClientes ()
	{
		return (ArrayList<Integer>) this.quantidadeClientes.clone();
	}
	
	@SuppressWarnings("unchecked")
	public ArrayList <Float> getFaturado ()
	{
		return (ArrayList<Float>) this.faturado.clone();
	}
}
