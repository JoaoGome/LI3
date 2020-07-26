package Modelo;

import java.io.Serializable;
import java.util.HashMap;

public class GestaoFilial implements GestaoFilialInterface, Serializable {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private HashMap <String,HashMap<String,VendasInterface>> byCliente;
	
	public void init ()
	{
		this.byCliente = new HashMap <> ();
	}
	
	@SuppressWarnings("unchecked")
	public HashMap <String,HashMap<String,VendasInterface>> getClientes ()
	{
		return (HashMap<String, HashMap<String, VendasInterface>>) this.byCliente.clone();
	}
	
	
	public void addVendaCliente (String produto, String cliente, int mes,int quantidade, float price, char mode)
	{
		if (this.byCliente.containsKey(cliente))
		{
			HashMap <String,VendasInterface> client = this.byCliente.get(cliente);
			
			if (cliente.contains(produto))
			{
				client.get(produto).addVendaG(mes, quantidade, price);
			}
			
			else 
			{
				VendasInterface vendas = new Vendas ();
				vendas.init();
				vendas.addVendaG(mes, quantidade, price);
				client.put(produto, vendas);
			}
		}
		
		else 
		{
			VendasInterface vendas = new Vendas ();
			vendas.init();
			vendas.addVendaG(mes, quantidade, price);
			HashMap <String,VendasInterface> hm = new HashMap <>();
			hm.put(produto, vendas);
			this.byCliente.put(cliente, hm);
		}
		
		
		
	}
	
}
