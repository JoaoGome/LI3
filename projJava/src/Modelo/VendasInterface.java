package Modelo;

public interface VendasInterface
{
    public void init ();
    public void initGFilial ();
    public void addVenda(int mes, int filial, int quantidade, float price);
    
    public void addVendaG(int mes, int quantidade, float price);
    public int getVendas(int mes, int filial);
    public int getVendasG(int mes);
    public float getRevenue(int mes, int filial);
    public float getRevenueG(int mes);
    public boolean checkVendas();
}
