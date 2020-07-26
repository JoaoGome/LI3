package Modelo;

import java.util.HashMap;

public interface GestaoFilialInterface {
	
	public void init ();
	public void addVendaCliente (String produto, String cliente, int mes, int quantidade, float price, char mode);
	public HashMap <String,HashMap<String,VendasInterface>> getClientes ();
}
