package Reader;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

import Auxiliar.GestaoVendasData;
import Modelo.*;

public class Reader implements ReaderInterface {

	private Scanner scClientes;
    private Scanner scProdutos;
    private Scanner scVendas;
	private File fileClientes;
    private File fileProdutos;
    private File fileVendas;
    private ParserInterface parser;
    
    public void setFiles (String clientPath, String productPath, String salesPath)
    {
    	this.fileClientes = new File (clientPath);
		this.fileProdutos = new File (productPath);
		this.fileVendas = new File (salesPath);
    }
    
  
	public void setFiles(String salesPath) {
		this.fileVendas = new File (salesPath);	
	}
    
    
    
    public void init (CatalogoInterface clientes, CatalogoInterface produtos, FaturacaoGlobalInterface fGlobal, GestaoFilialInterface gFilial [], GestaoVendasData gvData) throws FileNotFoundException
    {
    	this.scClientes = new Scanner(this.fileClientes);
    	this.scProdutos = new Scanner(this.fileProdutos);
    	this.scVendas = new Scanner(this.fileVendas);
    	
    	this.parser = new Parser();
    	
    	this.readClientes(clientes, gvData);
    	this.readProdutos(produtos,fGlobal, gvData);
    	this.readSales(clientes, produtos, fGlobal, gFilial, gvData);
    }
    
    public void initVendas (CatalogoInterface clientes, CatalogoInterface produtos, FaturacaoGlobalInterface fGlobal, GestaoFilialInterface gFilial [], GestaoVendasData gvData) throws FileNotFoundException
    {
    	this.scVendas = new Scanner(this.fileVendas);    	
    	this.parser = new Parser();

    	this.readSales(clientes, produtos, fGlobal, gFilial, gvData);
    }
    
	public void readClientes (CatalogoInterface clientes , GestaoVendasData gvData)
	{
		int linhasLidas = 0;
		int linhasValidas = 0;
		while (this.scClientes.hasNextLine())
		{
			linhasLidas++;
	        String data = this.scClientes.nextLine();
	        
	        if (this.parser.testClient(data))
	        {
	        	clientes.addElemento(data);
	        	linhasValidas++;
	        	
	        }
	        
	        data = null;
	        	
	      }
		gvData.setClv(linhasValidas);
		System.out.println("Linhas lidas " + linhasLidas);
		System.out.println("Linhas validas " + linhasValidas);
	} 
    
    public void readProdutos (CatalogoInterface produtos, FaturacaoGlobalInterface fGlobal, GestaoVendasData gvData)
    {
    	
    	int linhasLidas = 0;
    	int linhasValidas = 0;
    	
        while (this.scProdutos.hasNextLine())
        {
            String data = this.scProdutos.nextLine();
            linhasLidas++;
            
            if(this.parser.testProduct(data))
            {
            	linhasValidas++;
            	produtos.addElemento(data);
            	VendasInterface vendas = new Vendas();
            	vendas.init();
            	fGlobal.addEntry(data, vendas);
            }
            
            data = null;
        }
		gvData.setPlv(linhasValidas);
        System.out.println("Linhas lidas " + linhasLidas);
		System.out.println("Linhas validas " + linhasValidas);
    }
    
    public void readSales (CatalogoInterface clientes, CatalogoInterface produtos, FaturacaoGlobalInterface fGlobal, GestaoFilialInterface [] gFilial, GestaoVendasData gvData)
    {
    	int linhasLidas = 0;
    	int linhasValidas = 0;
    	
    	while(this.scVendas.hasNextLine())
    	{
    		
    		linhasLidas++;
    		String data = this.scVendas.nextLine();
    		String parser [] = data.split(" ");
    		
    		if(produtos.checkExiste(parser[0]) && clientes.checkExiste(parser[4]))
    		{
    			linhasValidas++;
    			float price = Float.parseFloat(parser[1]);
        		int quantidade = Integer.parseInt(parser[2]);
        		int month = Integer.parseInt(parser[5]);
        		int filial = Integer.parseInt(parser[6]);
        		char mode = parser[3].charAt(0);
        		fGlobal.updateVendas(parser[0], (month - 1), (filial - 1), quantidade, price, mode);
        		gFilial[filial - 1].addVendaCliente(parser[0], parser[4], (month - 1), quantidade, price, mode);
        		if(price==0) {gvData.incVvt0();}
        		
    		}
    		
    		data = null;
    		parser = null;
    		
    		
    	}
    	gvData.setLfr(this.fileVendas.getName());
    	gvData.setVll(linhasLidas);
		gvData.setVlv(linhasValidas);
    	System.out.println("Linhas lidas " + linhasLidas);
		System.out.println("Linhas validas " + linhasValidas);
    }
    
    public void close()
    {
        this.scClientes.close();
        this.scProdutos.close();
        this.scVendas.close();
    }

}
