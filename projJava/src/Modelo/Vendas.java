package Modelo;

import java.io.Serializable;

public class Vendas implements VendasInterface, Serializable{
    
    /**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private int vendas [];
    private boolean usado;
    private float revenue [];


    public void init ()
    {
    	this.usado = false;
        this.vendas = new int [36];
        this.revenue = new float[36];
    }
    
    public void initGFilial ()
    {
    	this.usado = false;
    	this.vendas = new int [12];
        this.revenue = new float[12];
    	
    }

    public void addVenda(int mes, int filial, int quantidade, float price)
    {
    	this.usado = true;
        this.vendas[filial*12 + mes] += quantidade;
        this.revenue[filial*12 + mes] += (float) quantidade *  price;
    }
    
    public void addVendaG (int mes, int quantidade, float price)
    {
    	this.usado = true;
    	this.vendas[mes] += quantidade;
    	this.revenue[mes] += (double) quantidade * price;
    }
    
    
    //funcao que busca as vendas num determinado mes para uma determinada filial
    public int getVendas(int mes, int filial)
    {
        return this.vendas[filial*12 + mes];
    }
    
    
    public int getVendasG (int mes)
    {
    	return this.vendas[mes];
    }

    public float getRevenue(int mes, int filial)
    {
        return this.revenue[filial*12 + mes];
    }
    
    public float getRevenueG(int mes)
    {
        return this.revenue[mes];
    }
    
    public boolean checkVendas()
    {
    	return this.usado;
    }
}

