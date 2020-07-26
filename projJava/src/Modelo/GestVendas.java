package Modelo;
import java.io.FileNotFoundException;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.TreeSet;
import Reader.*;
import Auxiliar.*;

public class GestVendas implements GestVendasInterface, Serializable
{
	private static final long serialVersionUID = 1L;
	private CatalogoInterface catalogoProdutos;
    private CatalogoInterface catalogoClientes;
    private FaturacaoGlobalInterface faturacaoGlobal;
    private GestaoFilialInterface gFilial [];
    private GestaoVendasData gvData;
    
    public void init(int size)
    {
        this.catalogoClientes = new Catalogo();
        this.catalogoProdutos = new Catalogo();
        this.faturacaoGlobal = new FaturacaoGlobal();
        this.gFilial = new GestaoFilialInterface[3];
        this.gvData = new GestaoVendasData();
        
        this.catalogoClientes.init();
        this.catalogoProdutos.init();
        this.faturacaoGlobal.init();
        this.gvData.init();
        
        for(int i = 0; i < size; i++)
        {
        	this.gFilial[i] = new GestaoFilial();
        	this.gFilial[i].init();
        }
        	
    } 

    
    
    public TreeSet <String> getCatalogoClientes ()
    {
    	return this.catalogoClientes.getCatalogo();
    }
    
    public TreeSet <String> getCatalogoProdutos ()
    {
    	return this.catalogoProdutos.getCatalogo();
    }
    
    //------------------------------ Query de dar load aos ficheiros --------------------
    
    public void loadFiles (String clientes, String produtos, String vendas) throws FileNotFoundException
    {
    	ReaderInterface reader = new Reader ();
    	reader.setFiles(clientes, produtos, vendas);
		
		reader.init(this.catalogoClientes, this.catalogoProdutos, this.faturacaoGlobal, this.gFilial, this.gvData);
		reader.close();
    	
    }
    
    public void loadFiles2 (String clientes,String produtos,String vendas) throws FileNotFoundException
    {
    	ReaderInterface reader = new Reader ();
    	reader.setFiles(clientes,produtos,vendas);
		reader.init(this.catalogoClientes, this.catalogoProdutos, this.faturacaoGlobal, this.gFilial, this.gvData);
		reader.close();
    }
    
    public void loadVendas (String vendas) throws FileNotFoundException
    {
    	ReaderInterface reader = new Reader ();
    	reader.setFiles(vendas);
		reader.initVendas(this.catalogoClientes, this.catalogoProdutos, this.faturacaoGlobal, this.gFilial, this.gvData);
		reader.close();
    }
    
    
    //-----------------------------Queries estatisticas---------------------------
  

	public GestaoVendasData infoUltimaVendas ()
    {
		
		Crono.start();
		
    	HashMap <String,VendasInterface> copy = this.faturacaoGlobal.getLista();
    	int produtosComprados=0;
    	for(Map.Entry<String, VendasInterface> entry : copy.entrySet())//calcula o n de produtos comprados
    	{
    		if(entry.getValue().checkVendas())
    		{
    			produtosComprados++;
    		}
    	}
    	
    	this.gvData.setPfc(produtosComprados);//quantidade de produtos comprados
    	float ft =0;
    	
    	for(Map.Entry<String, VendasInterface> entry : copy.entrySet())//calcula a faturacao global
    	{
    		for(int i=0; i<12;i++)
    		{
    			for(int k=0 ; k<3 ; k++)
    			{
    				ft +=entry.getValue().getRevenue(i,k);
    			}
    		}
    	}
    	
    	this.gvData.setFt(ft);
    	
    	HashSet<String> clientes = new HashSet<String>();
    	for(int i = 0; i < this.gFilial.length; i++) //itera filiais ;;calcula o numero de clientes que compraram coisas
    	{
    		HashMap <String,HashMap<String,VendasInterface>> listaByClient = this.gFilial[i].getClientes();
    		clientes.addAll(listaByClient.keySet());
      	}
    	this.gvData.setCfc(clientes.size());

    	System.out.println(Crono.getTImeString());
    	return this.gvData;
    	
    }
    
    public int[] totalCompras()
    {
    	Crono.start();
    	HashMap <String,VendasInterface> copy = this.faturacaoGlobal.getLista();
    	int compras[] = new int[12];
    	for(Map.Entry<String, VendasInterface> entry : copy.entrySet())
    	{
    		VendasInterface vi = entry.getValue();
    		for(int i=0; i<12;i++)
    		{
    			compras[i]+=vi.getVendasG(i);
    		}
    	}
    	System.out.println(Crono.getTImeString());
    	return compras;
    }
    
    
    public float[][] faturacaoPorMes()
    {
    	Crono.start();
    	float[][] totalVendas = new float[3][12];// organizado por filial e depois por mes
    	
    	for(int i = 0; i < this.gFilial.length; i++) //itera filiais
    	{
    		HashMap <String,HashMap<String,VendasInterface>> listaByClient = this.gFilial[i].getClientes();
    		for(int mes = 0; mes < 12; mes++)//itera meses
    		{        		
    			
        		for(HashMap<String,VendasInterface> hm: listaByClient.values())
        		{
        			for(VendasInterface v: hm.values())
        			{
        				totalVendas[i][mes] += v.getRevenueG(mes);
        			}
        		}
    		}
    	}
    	
    	System.out.println(Crono.getTImeString());
    	return totalVendas;
    }
    
    public int[][] clientesPorMes()
    {
    	Crono.start();
    	int[][] clientes = new int[3][12];// organizado por filial e depois por mes
    	
    	for(int i = 0; i < this.gFilial.length; i++) //itera filiais
    	{
    		HashMap <String,HashMap<String,VendasInterface>> listaByClient = this.gFilial[i].getClientes();
    		
    		for(HashMap<String,VendasInterface> hm: listaByClient.values()) //itera nos clientes
    		{
    			int[] comprou = new int[12];
    			for(VendasInterface vi: hm.values()) //itera nos produtos
        		{
    				for(int mes = 0 ; mes<12 ; mes++) //itera nos meses
    				{
    					if(vi.getVendas(mes, 0)>0)
    					{
    						comprou[mes] = 1;
    					}
    				}
    				
    				for(int mes = 0 ; mes<12 ; mes++) //itera nos meses
    				{    					
    					clientes[i][mes]+=comprou[mes];
    				}
        		}// for(VendasInterface vi: hm.values()) //itera nos produtos
    		}
      	}
    	System.out.println(Crono.getTImeString());
    	return clientes;
    }
    
    
    
    
    //-----------------------------Queries interativas----------------------------
    
    //-------- Query 1 ----------------
    
    public TreeSet <String> query1 ()
    {
    	Crono.start();
    	TreeSet <String> result = new TreeSet <> ();
    	HashMap <String,VendasInterface> copy = this.faturacaoGlobal.getLista();
    	
    	for (Map.Entry<String, VendasInterface> entry : copy.entrySet()) {
    	    String key = entry.getKey();
    	    VendasInterface value = entry.getValue();
    	    if(!value.checkVendas())
    	    	result.add(key);
    	}
    	
    	System.out.println(Crono.getTImeString());
    	return result;
    }
    
    //-------- Query 2 --------------
    
    public ArrayList<Integer> query2 (int month)
    {
    	Crono.start();
    	ArrayList<Integer> result = new ArrayList <>();
    	
    	for(int i = 0; i < this.gFilial.length; i++)
    	{
    		HashMap <String,HashMap<String,VendasInterface>> listaByClient = this.gFilial[i].getClientes();
    		int previousVendas = 0;
    		int totalVendas = 0;
    		int numeroClientes = 0;
    		
    		for(HashMap<String,VendasInterface> hm: listaByClient.values())
    		{
    			for(VendasInterface v: hm.values())
    			{
    				totalVendas += v.getVendasG(month);
    			}
    			
    			if (totalVendas > previousVendas) numeroClientes++;
    		}
    		
    		result.add(totalVendas);
    		result.add(numeroClientes);
    		
    		
    	}
    		
    	System.out.println(Crono.getTImeString());
    	return result;
    	
    }
    
    //-------- Query 3 -------------
    public ArrayList <Float> query3 (String codigo)
    {
    	Crono.start();
    	ArrayList<Float> result = new ArrayList <>();
    	
    	for (int i = 0; i < 12; i++)
    	{
    		float previousCompras = 0;
    		float totalCompras = 0;
    		float numeroProdutos = 0;
    		float previousGasto = 0;
    		float valorGasto = 0;
    		
    		for (int j = 0; j< this.gFilial.length; j++)
    		{
    			HashMap <String,HashMap<String,VendasInterface>> listaByClient = this.gFilial[j].getClientes();
    			HashMap <String, VendasInterface> hm = listaByClient.get(codigo);
    			
        		for(VendasInterface v: hm.values())
        		{
       				totalCompras += v.getVendasG(i);
       				valorGasto += v.getRevenueG(i);
        				
       				if (totalCompras > previousCompras && valorGasto > previousGasto)
       				{
       					numeroProdutos++;
       					previousCompras = totalCompras;
       					previousGasto = valorGasto;
       				}
        				
        		}
        	
        			
        	}
    		
    		result.add(totalCompras);
    		result.add(numeroProdutos);	
    		result.add(valorGasto);
    			
    	}
    	System.out.println(Crono.getTImeString());
   		
    	return result;
    }
    
    //-------- Query 4 --------------
    public Query4 query4 (String codigo)
    {
    	Crono.start();
    	ArrayList <Integer> quantidade = new ArrayList <>();
    	ArrayList <Float> faturado = new ArrayList <>();
    	ArrayList <Integer> numeroClientes = new ArrayList <>();
    	


        HashMap <String,VendasInterface> lista = this.faturacaoGlobal.getLista();
    	VendasInterface vendas = lista.get(codigo);
    	

        for (int mes = 0; mes < 12; mes++)
        {
    		int quantity = vendas.getVendas(mes,0) + vendas.getVendas(mes,1) + vendas.getVendas(mes,2);
    		float dinheiros = vendas.getRevenue(mes,0) + vendas.getRevenue(mes,1) + vendas.getRevenue(mes,2);

    		quantidade.add(quantity);
    		faturado.add(dinheiros);

    	}
        
        for (int mes = 0; mes < 12; mes++)
        {
        	TreeSet <String> listaClientes = new TreeSet<>();
        	for (int i = 0; i < this.gFilial.length; i++)
        	{
        		HashMap <String, HashMap <String, VendasInterface>> byCliente = this.gFilial[i].getClientes();
        		for (Map.Entry<String, HashMap <String, VendasInterface>> entry: byCliente.entrySet())
        		{
        			
        			for (Map.Entry <String,VendasInterface> entry2: entry.getValue().entrySet())
        			{
        				if (entry2.getKey().equals(codigo))
        				{
        					if (entry2.getValue().getVendasG(mes) > 0) listaClientes.add(entry.getKey());
        				}
        			}
        		}
        	}
        	
        	numeroClientes.add(listaClientes.size());
        }

        Query4 query4 = new Query4 ();
        query4.init(quantidade, faturado, numeroClientes);
        
        System.out.println(Crono.getTImeString());
        return query4;
    	
    }
    
    //-------- Query 5----------
    
    public CodigoNumeroPar query5 (String codigo, int top)
    {
    	Crono.start();
    	HashMap <String, Integer> result = new HashMap <>();
    	
    	for (int i = 0; i < this.gFilial.length; i++)
    	{
    		HashMap <String,HashMap<String,VendasInterface>> listaByCliente = this.gFilial[i].getClientes();
    		
			HashMap <String, VendasInterface> cliente = listaByCliente.get(codigo);
			
			for (Map.Entry<String, VendasInterface> entry : cliente.entrySet()) {
			    VendasInterface v = entry.getValue();
			    String produto = entry.getKey();
			    int quantidade = 0;
			    
			    for (int j = 0; j < 12; j++)
			    {
			    	quantidade += v.getVendasG(j);
			    }
			    
			    if(result.containsKey(produto))
			    {
			    	int atual = result.get(produto);
			    	atual += quantidade;
			    	result.replace(produto, atual);
			    } 
			    	else 
			    	{
			    		result.put(produto, quantidade);
			    	}
			}
			
		}
    	
    	TreeSet <Integer> ordenado = new TreeSet <>();
    	for (Integer i: result.values())
    		ordenado.add(i);
    	
    	
    	TreeSet<Integer> ordenadoReverse = (TreeSet<Integer>)ordenado.descendingSet();
    	
    	
    	HashMap <Integer,String> results = new HashMap <>();
    	
    	for (Map.Entry<String, Integer> entry : result.entrySet())
    		results.put(entry.getValue(), entry.getKey());
    	
    	
    	ArrayList <String> produtos = new ArrayList <>();
    	int k = 0;
    	for (Integer i: ordenadoReverse)
    	{
    		if (k < top)
    		{
    			produtos.add(results.get(i));
    			k++;
    		}
    		
    		else break;
    		
    	}
    	
    	CodigoNumeroPar query5 = new CodigoNumeroPar();
    	query5.initQuery5(ordenadoReverse, produtos);
    	System.out.println(Crono.getTImeString());
    	return query5;
    }
    
    //-------- Query 6----------
    
    public CodigoNumeroPar query6 (int top)
    {
    	Crono.start();
    	ArrayList <Integer> resultNumeros = new ArrayList <>();
    	ArrayList <String> resultCodigos= new ArrayList <>();
    	
    	HashMap <String, Integer> aux = new HashMap<>();
    	
    	for (int filial = 0; filial < this.gFilial.length; filial++)
    	{
    		HashMap <String, HashMap <String,VendasInterface>> byClient = this.gFilial[filial].getClientes();
    		
    		for (Map.Entry<String, HashMap<String,VendasInterface>> entry: byClient.entrySet())
    		{
    			for (Map.Entry <String,VendasInterface> entry2: entry.getValue().entrySet())
    			{
    				String produto = entry2.getKey();
    				int quantidade = 0;
    				for (int mes = 0; mes < 12; mes++)
    				{
    					quantidade += entry2.getValue().getVendasG(mes);
    				}
    				
    				if (aux.containsKey(produto))
    				{
    					quantidade += aux.get(produto);
    					aux.replace(produto, quantidade);
    				} 
    				
    				else
    				{
    					aux.put(produto, quantidade);
    				}
    			}
    		}
    	}
    	
    	HashMap <Integer,String> auxReverse = new HashMap <>();
    	TreeSet <Integer> ordenado = new TreeSet <>();
    	
    	for (Map.Entry<String, Integer> entry: aux.entrySet())
    	{
    		auxReverse.put(entry.getValue(), entry.getKey());
    		ordenado.add(entry.getValue());
    	}
    
    	
    	TreeSet <Integer> reversedOrdenado = (TreeSet<Integer>)ordenado.descendingSet();
    	int k = 0;
    	for (int j: reversedOrdenado)
    	{
    		if (k < top)
    		{
    			String produto = auxReverse.get(j);
    			
        		TreeSet <String> clientes = new TreeSet <>();
        		
        		for (int i = 0; i < this.gFilial.length; i++)
            	{
            		HashMap <String, HashMap <String, VendasInterface>> byCliente = this.gFilial[i].getClientes();
            		for (Map.Entry<String, HashMap <String, VendasInterface>> entry: byCliente.entrySet())
            		{
            			
            			for (Map.Entry <String,VendasInterface> entry2: entry.getValue().entrySet())
            			{
            				if (entry2.getKey().equals(produto))
            				{
            					clientes.add(entry.getKey());
            					
            				}
            					
            				
            			}
            		}
            	}
        		k++;
        		resultNumeros.add(clientes.size());
        		resultCodigos.add(produto);
        		
        		
    		} else break;
    		
    		
    	}
    	
    	
    	CodigoNumeroPar result = new CodigoNumeroPar();
    	result.initQuery6(resultCodigos, resultNumeros);
    	System.out.println(Crono.getTImeString());
    	return result;
    }
  //-------- Query 7----------
    
    public ArrayList <String> query7 ()
    {
    	Crono.start();
    	ArrayList <String> result = new ArrayList <>();
    	
    	for (int i = 0; i < this.gFilial.length; i++)
    	{
    		HashMap <String, Float> faturadoByClient = new HashMap <>();
    		
    		HashMap <String, HashMap <String,VendasInterface>> byClient = this.gFilial[i].getClientes();
    		
    		for (Map.Entry<String, HashMap <String,VendasInterface>> entry: byClient.entrySet())
    		{
    			String cliente = entry.getKey();
    			
    			float faturado = 0.0f;
    			
    			for (VendasInterface v: entry.getValue().values())
    			{
    				for (int j = 0; j < 12; j++)
    					faturado += v.getRevenueG(j);
    			}
    			
    			faturadoByClient.put(cliente, faturado);
    		}
    		
    		HashMap <Float,String> reverse = new HashMap <>();
    		TreeSet <Float> lista = new TreeSet<>();
    		
    		for (Map.Entry<String, Float> entry: faturadoByClient.entrySet())
    		{
    			reverse.put(entry.getValue(), entry.getKey());
    			lista.add(entry.getValue());
    		}
    		
    		TreeSet <Float> reversedLista = (TreeSet<Float>)lista.descendingSet();
    		int k = 0;
    		for(float d: reversedLista)
    		{
    			if (k < 3)
    			{
    				result.add(reverse.get(d));
    				k++;
    			}
    				
    			else break;
    		}
    			
    	}
    	System.out.println(Crono.getTImeString());
    	return result;
    }
  //-------- Query 8----------
    
    public CodigoNumeroPar query8 (int top)
    {
    	Crono.start();
    	HashMap <String, TreeSet <String>> listaByCliente = new HashMap<>();
    	
    	for (int i = 0; i < this.gFilial.length; i++)
    	{
    		HashMap <String, HashMap <String,VendasInterface>> byCliente = this.gFilial[i].getClientes();
    		
    		for (Map.Entry<String, HashMap<String,VendasInterface>> entry: byCliente.entrySet())
    		{
    			
    			String cliente = entry.getKey();
    			
    			for (String s: entry.getValue().keySet())
    			{
    				if (listaByCliente.containsKey(cliente))
    				{
    					TreeSet <String> lista = listaByCliente.get(cliente);
    					lista.add(s);
    					listaByCliente.replace(cliente, lista);
    				}
    				
    				else
    				{
    					TreeSet <String> lista = new TreeSet <>();
    					lista.add(s);
    					listaByCliente.put(cliente, lista);
    				}
    			}
    			
    		}
    		
    	}
    	
    	HashMap <String,Integer> numberByClient = new HashMap <>();
    	
    	for (Map.Entry<String, TreeSet <String>> entry: listaByCliente.entrySet())
    		numberByClient.put(entry.getKey(), entry.getValue().size());
    	
    	HashMap <Integer,String> reverse = new HashMap<>();
    	
    	TreeSet <Integer> numeros = new TreeSet <>();
    	
    	for (Map.Entry<String, Integer> entry: numberByClient.entrySet())
    	{
    		reverse.put(entry.getValue(), entry.getKey());
    		numeros.add(entry.getValue());
    	}
    	
    	TreeSet <Integer> reversedLista = (TreeSet<Integer>)numeros.descendingSet();
    	
    	ArrayList <String> clientCodigos = new ArrayList <>();
    	ArrayList <Integer> clientQuantidades = new ArrayList <>();
    	
    	int k = 0;
    	
    	for (int i: reversedLista)
    	{
    		if (k < top)
    		{
    			clientQuantidades.add(i);
        		clientCodigos.add(reverse.get(i));
        		k++;
    		} else break;
    		
    	}
    		
    	CodigoNumeroPar query8 = new CodigoNumeroPar();
    	query8.initQuery6(clientCodigos, clientQuantidades);
    	System.out.println(Crono.getTImeString());
    	return query8;
    	
    	
    }
    
    
  //-------- Query 9----------
    public Query9 query9 (String produto, int top)
    {
    	Crono.start();
    	HashMap <String, Integer> aux = new HashMap <>();
    	
    	for (int filial = 0; filial < this.gFilial.length; filial++)
    	{
    		HashMap <String,HashMap<String,VendasInterface>> byClient = this.gFilial[filial].getClientes();
    		for (Map.Entry<String, HashMap <String,VendasInterface>> entry: byClient.entrySet())
    		{
    			for (Map.Entry<String, VendasInterface> entry2: entry.getValue().entrySet())
    			{
    				if (entry2.getKey().equals(produto))
    				{
    					int quantidade = 0;
    					for (int mes = 0; mes < 12; mes++)
    						quantidade += entry2.getValue().getVendasG(mes);
    					
    					if (aux.containsKey(entry.getKey()))
    					{
    						quantidade += aux.get(entry.getKey());
    						aux.replace(entry.getKey(), quantidade);
    					}
    					
    					else aux.put(entry.getKey(), quantidade);
    						
    				}
    			}
    		}
    	}
    	
    	HashMap <Integer,String> aux2 = new HashMap <>();
    	TreeSet <Integer> ordenado = new TreeSet <>();
    	for (Map.Entry<String, Integer> entry: aux.entrySet())
    	{
    		aux2.put(entry.getValue(), entry.getKey());
    		ordenado.add(entry.getValue());
    	}
    	
    	ArrayList <String> clientes = new ArrayList <>();
    	ArrayList <Float> faturado = new ArrayList <>();
    	
    	TreeSet <Integer> reversedLista = (TreeSet<Integer>)ordenado.descendingSet();
    	int k = 0;
    	
    	for (int i: reversedLista)
    	{
    		if (k < top)
    		{
    			String cliente = aux2.get(i);
    			float valor = 0.0f;
    			for (int filial = 0; filial < this.gFilial.length; filial++)
    			{
    				HashMap <String, VendasInterface> hm = this.gFilial[filial].getClientes().get(cliente);
    				VendasInterface vendas = hm.get(produto);
    				if (vendas != null)
    				{
    					for (int mes = 0; mes < 12; mes++)
        					valor += vendas.getRevenueG(mes);
    				}
    				
    			}
    			
    			clientes.add(cliente); faturado.add(valor);
    			k++;
    		} else break;
    	}
    	
    	Query9 query9 = new Query9();
    	query9.init(clientes, faturado);
    	System.out.println(Crono.getTImeString());
    	return query9;
    	
    	
    }
    //-------- Query 10----------
	public ArrayList<ArrayList<HashMap<String,Float>>> query10()
    {
    	Crono.start();
    	ArrayList<ArrayList<HashMap<String,Float>>> lista = new ArrayList<ArrayList<HashMap<String, Float>>>();//12 entrada, uma para cada mes
    	for(int i = 0; i<12 ; i++)
    	{
    		lista.add(new ArrayList<HashMap<String,Float>>() );
    		
    		for(int k = 0; k< this.gFilial.length ; k++)//3 entradas, uma para cada filial
        	{
        		lista.get(i).add(new HashMap<String,Float>());//3 mapas /mes um para cada filial
        	}
    	}
    	
    	HashMap <String,VendasInterface> copy = this.faturacaoGlobal.getLista();
    	for(Map.Entry<String, VendasInterface> entry : copy.entrySet())//itera nos produtos
    	{
    		for(int f=0;f<this.gFilial.length;f++)
    		{
    			for(int mes=0; mes<12;mes++)
    			{
    				//poe <codigo produto,faturacao nesse mes nessa filial no mapa correspondete a esse mes e filial
    				if(entry.getValue().getVendas(mes,f)!=0)
    				lista.get(mes).get(f).put(entry.getKey(),entry.getValue().getRevenue(mes,f));
    			}
    		}
    	} 
    	System.out.println(Crono.getTImeString());
    	return lista;
    }
    
}









