package Modelo;

import java.io.Serializable;
import java.util.HashMap;

public class FaturacaoGlobal implements FaturacaoGlobalInterface, Serializable{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private HashMap <String,VendasInterface> lista;
	
	public void init ()
	{
		this.lista = new HashMap <>();
	}
	
	//usar para inicializar todos os produtos com uma classe vendas vazia
	public void addEntry (String key, VendasInterface value)
	{
		this.lista.put(key, value);
	}
	
	public boolean checkExists (String codigo)
	{
		return this.lista.containsKey(codigo);
	}
	  
	public void updateVendas (String codigo, int mes, int filial, int quantidade, float price, char mode)
	{
		VendasInterface vendas = this.lista.get(codigo);
		if (mode == 'N') 
		{
			vendas.addVenda(mes, filial, quantidade, price);
		} 
		
		else vendas.addVenda(mes, filial, quantidade, price);
		
			
	}
	
	//funcao usada para aceder aos dados na resoluçao das queries
	@SuppressWarnings("unchecked")
	public HashMap <String,VendasInterface> getLista ()
	{
		return (HashMap<String, VendasInterface>) this.lista.clone();
	}
	
}
