package Modelo;

import java.util.HashMap;

public interface FaturacaoGlobalInterface {
	
	public void init ();
	public void addEntry (String key, VendasInterface value);
	public boolean checkExists (String codigo);
	public void updateVendas (String codigo, int mes, int filial, int quantidade, float price, char mode);
	public HashMap <String,VendasInterface> getLista ();
}
