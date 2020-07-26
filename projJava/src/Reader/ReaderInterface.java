package Reader;

import java.io.FileNotFoundException;

import Auxiliar.GestaoVendasData;
import Modelo.CatalogoInterface;
import Modelo.FaturacaoGlobalInterface;
import Modelo.GestaoFilialInterface;

public interface ReaderInterface {
	
	public void setFiles (String clientPath, String productPath, String salesPath);
	public void init (CatalogoInterface clientes, CatalogoInterface produtos, FaturacaoGlobalInterface fGlobal, GestaoFilialInterface gFilial [], GestaoVendasData gvData) throws FileNotFoundException;
	public void readClientes (CatalogoInterface clientes, GestaoVendasData gvData);
	public void readProdutos (CatalogoInterface produtos, FaturacaoGlobalInterface fGlobal, GestaoVendasData gvData);
	public void readSales (CatalogoInterface clientes, CatalogoInterface produtos, FaturacaoGlobalInterface fGlobal, GestaoFilialInterface [] gFilial, GestaoVendasData gvData);
	public void close();
	public void setFiles(String vendas);
	public void initVendas(CatalogoInterface catalogoClientes, CatalogoInterface catalogoProdutos,
			FaturacaoGlobalInterface faturacaoGlobal, GestaoFilialInterface[] gFilial,
			GestaoVendasData gvData) throws FileNotFoundException;	
}
