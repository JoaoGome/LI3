package Auxiliar;

import java.io.Serializable;

public class GestaoVendasData implements Serializable{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	int vll; //vendas linhas lidas
	int vlv; //vendas linhas valida
	int vvt0; //vendas com valor total 0
	float ft;
	
	int clv;
	int cfc; //cliences fizeram compras
	
	int plv;
	int pfc;
	
	String lfr;//last file read name
	
	public void init()
	{
		vll=0; //vendas linhas lidas
		vlv=0; //vendas linhas valida
		vvt0=0;
		ft=0;
		
		clv=0;
		cfc=0;// clientes que fizeram compras
		
		plv=0;
		pfc=0;
		lfr ="";
	}
	
	public void setVll(int vll)
	{
		this.vll =vll;
	}
	
	public void setVlv(int vlv)
	{
		this.vlv =vlv;
	}
	
	public void incVvt0()
	{
		this.vvt0+=1;
	}
	
	public void setFt(float ft2)
	{
		this.ft=ft2;
	}
	
	public void setClv(int clv)
	{
		this.clv =clv;
	}
	
	public void setCfc(int cfc)
	{
		this.cfc =cfc;
	}
	
	public void setPlv(int plv)
	{
		this.plv =plv;
	}
	
	public void setPfc(int pfc)
	{
		this.pfc =pfc;
	}
	
	public void setLfr(String lfr)
	{
		this.lfr=lfr;
	}
	
	public int getVll()
	{
		return this.vll;
	}

	public int getVlv()
	{
		return this.vlv;
	}
	
	public int getVvt0()
	{
		return this.vvt0;
	}

	public float getft()
	{
		return this.ft;
	}

	public int getClv()
	{
		return this.clv;
	}
	
	public int getCfc()
	{
		return this.cfc;
	}

	public int getPlv()
	{
		return this.plv;
	}
	
	public String getLfr()
	{
		return this.lfr;
	}
	
	public String toString()
	{

		return "nome do ficheiro: " +  this.lfr+ "\n"+
				"vendas erradas: " + (this.vll-this.vlv)+"\n"+
				"produtos: " + plv + "\n"+
				"produtos comprados: " + pfc +"\n"+
				"produtos nao comprados: " +(plv-pfc) +"\n"+
				"clientes: " + clv + "\n"+
				"clientes fizeram compras: " + cfc +"\n"+
				"clientes nao fizeram compras: " +(clv-cfc) +"\n"+
				"Compras de valor 0: " + vvt0 + "\n"+
				"faturacao total: " + ft +"\n";
	}

}
