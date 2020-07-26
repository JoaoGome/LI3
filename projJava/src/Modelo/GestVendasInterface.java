package Modelo;

import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.TreeSet;

import Auxiliar.*;

public interface GestVendasInterface {
	
	public void init(int size);
	public TreeSet <String> getCatalogoProdutos ();
	public TreeSet <String> getCatalogoClientes ();
	public GestaoVendasData infoUltimaVendas ();
	public int[] totalCompras();
	public float[][] faturacaoPorMes();
	public int[][] clientesPorMes();
	public TreeSet <String> query1 ();
	public ArrayList<Integer> query2 (int month);
	public ArrayList <Float> query3 (String codigo);
	public Query4 query4 (String codigo);
	public CodigoNumeroPar query6 (int top);
	public CodigoNumeroPar query5 (String codigo, int top);
	public ArrayList <String> query7 ();
	public CodigoNumeroPar query8 (int top);
	public Query9 query9 (String produto, int top);
	public ArrayList<ArrayList<HashMap<String,Float>>> query10();
	public void loadFiles (String clientes, String produtos, String vendas) throws FileNotFoundException;
}
