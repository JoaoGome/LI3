package View;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.TreeSet;

import Auxiliar.*;

public class View implements ViewInterface{

	public int mainMenu ()
	{
		System.out.println("				Sistema de Gestão de Vendas");
		System.out.println("\n");
		System.out.println("Insira um número de acordo com a funcionalidade que quiser utilizar!");
		System.out.println("0: Dar load aos ficheiros");
		System.out.println("1: Queries Estatisticas ");
		System.out.println("2: Queries Interativas");
		System.out.println("3: Terminar programa");
		System.out.println("4: Guardar dados em ficheiro");
		System.out.println("5: Dar load aos dados a partir de um .dat file");
		
		int input = Input.lerInt();
		return input;
	}
	
	public String [] askFicheiros ()
	{
		System.out.println("Introduza ficheiro de clientes");
		String clientes = Input.lerString();
		System.out.println("Introduza ficheiro de produtos");
		String produtos = Input.lerString();
		System.out.println("Introduza ficheiro de vendas");
		String vendas = Input.lerString();
		
		String lista [] = {clientes,produtos,vendas};
		return lista;
	}
	
	public int menuEstasticas ()
	{
		System.out.println("\n");
		System.out.println("				Menu de Queries Estatisticas");
		System.out.println("\n");
		System.out.println("Insira um número de acordo com a query que quiser consultar!");
		System.out.println("0: Informações referentes ao último ficheiros de vendas lido");
		System.out.println("1: Número total de compras por mês");
		System.out.println("2: Faturação total por mês");
		System.out.println("3: Número de clientes distintos que compraram");
		System.out.println("4: Voltar ao Menu Inicial");
		
		
		int input = Input.lerInt();
		return input;
	}
	
	public int menuInterativas ()
	{
		System.out.println("\n");
		System.out.println("				Menu de Queries Interativas");
		System.out.println("\n");
		System.out.println("Insira um número de acordo com a query que quiser consultar!");
		System.out.println("Query 1: Lista de Produtos que nunca foram comprados.");
		System.out.println("Query 2: Dado um mês, e dividido por filial, número total de vendas realizadas e número de clientes que as fizeram.");
		System.out.println("Query 3: Para um cliente, determinar quantas compras fez, quantos produtos diferentes comprou e quanto gastou, separado por mês");
		System.out.println("Query 4: Para um produto, determinar quantas vezes foi comprado, por quantos clientes faturados e o valor total, separado por mês");
		System.out.println("Query 5: Para um cliente, determina a lista de produtos que mais comprou");
		System.out.println("Query 6: Conjunto dos X produtos mais vendidos, indicando o número de clientes distintos que cada um teve");
		System.out.println("Query 7: Determinar para cada filial, a lista dos 3 maiores compradores a nivel de faturação");
		System.out.println("Query 8: Determinar o conjunto de X clientes que compraram mais produtos diferentes");
		System.out.println("Query 9: Dado um produto, determinar os X clientes que mais o compraram");
		System.out.println("Query 10: Determinar mês a mês, e para cada filial, a faturação total para cada produto");
		System.out.println("11: Voltar ao menu inicial");
		
		int input = Input.lerInt();
		return input;
	}
	
	// Queries Estatisticas
	
	public void showQueryE1 (GestaoVendasData lista)
	{
		System.out.println(lista.toString());
	}
	
	public void showQueryE21 (int [] lista)
	{
		
		
		for (int i = 0; i < lista.length; i++)
		{
			System.out.println("Informação referente ao mês " + (i+1));
			System.out.println("Numero de compras: " + lista[i]);
		}
	}
	
	public void showQueryE22 (float [][] lista)
	{
		int filialNumber = 0;
		boolean running = true;
		
		while (running)
		{
			System.out.println("Showing Filial " + (filialNumber + 1) + " out of " + lista.length);
			
			for (int mes = 0; mes < 12; mes++)
			{
				System.out.println("Informação do mês: " + (mes+1) + " Faturação: " + lista[filialNumber][mes]);
			}
				
				
				
			
			System.out.println("Pressione D para avançar para a filial seguinte, A para a filial anterior, Q para sair da query");
			String input = Input.lerString();
			
			switch (input)
			{
				case "D": 
					filialNumber++;
					break;
					
				case "A":
					filialNumber--;
					break;
					
				case "Q": 
					running = false;
					break;
					
				
			}
		}
		
	}

	public void showQueryE23 (int [][] lista)
	{
		int filialNumber = 0;
		boolean running = true;
		
		while (running)
		{
			System.out.println("Showing Filial " + (filialNumber + 1) + " out of " + lista.length);
			
			for (int mes = 0; mes < 12; mes++)
			{
				System.out.println("Informação do mês: " + (mes+1) + " Clientes: " + lista[filialNumber][mes]);
			}
				
				
				
			
			System.out.println("Pressione D para avançar para a filial seguinte, A para a filial anterior, Q para sair da query");
			String input = Input.lerString();
			
			switch (input)
			{
				case "D": 
					filialNumber++;
					break;
					
				case "A":
					filialNumber--;
					break;
					
				case "Q": 
					running = false;
					break;
					
				
			}
		}
	}
	
	
	// Query Interativas
	
	public void showQueryI1 (TreeSet <String> lista)
	{	
		
		ArrayList <String> listaAux = new ArrayList <>();
		for (String s: lista)
			listaAux.add(s);
		
		int pageSize = 10;
		int page = 0;
		boolean running = true;
		
		while (running)
		{
			System.out.println("Showing page " + page + " out of " + (listaAux.size() / pageSize));
			int i = page * pageSize;
			int control = 0;
			
			while (control < pageSize && i < listaAux.size())
			{
				System.out.println("Produto: " + listaAux.get(i++));
				control++;
			}
				
				
				
			
			System.out.println("Pressione D para avançar para a página seguinte, A para a página anterior, Q para sair da query, ou introduza o codigo de um produto para saber se se encontra na lista.");
			String input = Input.lerString();
			
			switch (input)
			{
				case "D": 
					page++;
					break;
					
				case "A":
					page--;
					break;
					
				case "Q": 
					running = false;
					break;
					
				default: 
				{
					if (listaAux.contains(input)) System.out.println("Produto encontra-se na lista!");
					else System.out.println("Produto não se encontra na lista!");
					
				}
				
			}
		}
		
	}
	
	public void showQueryI2 (ArrayList <Integer> lista)

	{
		int pageSize = 2;
		int page = 0;
		
		boolean running = true;
		
		while (running)
		{
			System.out.println("Showing filial: " + (page + 1) + " out of " + (lista.size() / 2) + " filiais");
			int i = page*pageSize;
			int control = 0;
			
			while (control < pageSize)
			{
				System.out.println("Total de Vendas: " + lista.get(i++));
				control++;
			}
			
			System.out.println("D para avançar para a filial seguinte, A para a filial anterior ou Q para sair da query.");
			String input = Input.lerString();
			
			switch (input)
			{
				case "D":
					page++;
					break;
					
				case "A":
					page--;
					break;
				
				case "Q":
					running = false;
					break;
				
			}
			
		}
	}
	
	public void showQueryI3 (ArrayList <Float> lista)
	{
		int pageSize = 3;
		int page = 0;
		
		boolean running = true;
		
		while (running)
		{
			int i = page*pageSize;
			
			
			
			
			System.out.println("Informação referente ao mês " + (page + 1));
			System.out.println("Total de Compras: " + lista.get(i));
			System.out.println("Numero de Produtos distintos: " + lista.get(i + 1));
			System.out.println("Valor gasto no total: " + lista.get(i + 2));
			
			
			System.out.println("D para avançar para o mês seguinte, A para o mês anterior ou Q para sair da query.");
			String input = Input.lerString();
			
			switch (input)
			{
				case "D":
					page++;
					break;
					
				case "A":
					page--;
					break;
				
				case "Q":
					running = false;
					break;
				
			}
			
		}
	}
	
	public void showQueryI4 (Query4 lista)
	{
		
		ArrayList <Integer> vendas = lista.getVendas();
		ArrayList <Integer> clientes = lista.getClientes();
		ArrayList <Float> faturado = lista.getFaturado();
		
		int page = 0;
		
		boolean running = true;
		
		while (running)
		{
			int i = page;
			
			
			
			
			System.out.println("Informação referente ao mês " + (page + 1));
			System.out.println("Total de Vendas: " + vendas.get(i));
			System.out.println("Numero de Clientes distintos: " + clientes.get(i));
			System.out.println("Valor gasto no total: " + faturado.get(i));
			
			
			System.out.println("D para avançar para o mês seguinte, A para o mês anterior ou Q para sair da query.");
			String input = Input.lerString();
			
			switch (input)
			{
				case "D":
					page++;
					break;
					
				case "A":
					page--;
					break;
				
				case "Q":
					running = false;
					break;
				
			}
			
		}
	}
	
	public void showQueryI5 (CodigoNumeroPar lista)
	{
		TreeSet <Integer> numeros = lista.getValores();
		ArrayList <String> codigos = lista.getCodigos();
		
		ArrayList <Integer> auxiliar = new ArrayList <>();
		for (int i: numeros)
			auxiliar.add(i);
		
		int page = 0;
		int pageSize = 10;
		boolean running = true;
		
		while (running)
		{
			System.out.println("Showing page number " + (page + 1) + " out of " + (codigos.size() / 2 + 1));
			int control = 0;
			int i = page * pageSize;
			
			while (control < pageSize && i < codigos.size())
			{
				System.out.println("Produto " + codigos.get(i) + "     Quantidade " + auxiliar.get(i++));
				control++;
			}
			
			System.out.println("Pressione D para ir para a pagina seguinte, A para a pagina anterior, Q para sair desta query, ou insira o codigo de um Produto para ver se faz parte da lista");
			String input = Input.lerString();
			
			switch (input)
			{
				case "D":
					page++;
					break;
					
				case "A":
					page--;
					break;
				
				case "Q":
					running = false;
					break;
					
				default:
				{
					if (codigos.contains(input))
					{
						int index = codigos.indexOf(input);
						System.out.println("Produto existe na lista e teve " + auxiliar.get(index));
					}
					
					else System.out.println("Produto não faz parte da lista");
					break;
				}
				
			}
		}
		}
	
	
	public void showQueryI6 (CodigoNumeroPar lista)
	{ 
		ArrayList <String> codigos = lista.getCodigos();
		ArrayList <Integer> numeros = lista.getValoresArray();
		
		
		
		boolean running = true;
		int page = 0;
		int pageSize = 2;
		
		while (running)
		{
			System.out.println("Pagina " + (page + 1) + " out of " + (codigos.size() / 2 + 1));
			int control = 0;
			int i = page * pageSize;
			
			while (control < pageSize && i < codigos.size())
			{
				System.out.println("Produto " + codigos.get(i) + "     Numero de Clientes " + numeros.get(i++));
				control++;
			}
			
			System.out.println("Pressione D para ir para a pagina seguinte, A para a pagina anterior, Q para sair desta query, ou insira o codigo de um Produto para ver se faz parte da lista");
			String input = Input.lerString();
			
			switch (input)
			{
				case "D":
					page++;
					break;
					
				case "A":
					page--;
					break;
				
				case "Q":
					running = false;
					break;
					
				default:
				{
					if (codigos.contains(input))
					{
						int index = codigos.indexOf(input);
						System.out.println("Produto existe na lista e teve " + numeros.get(index) + " clientes distintos");
					}
					
					else System.out.println("Produto não faz parte da lista");
					break;
				}
				
			}
		}
	}
		
	public void showQueryI7 (ArrayList <String> lista)
	{
		int pageSize = 3;
		int page = 0;
		boolean running = true;
		
		while (running)
		{
			System.out.println("Filial " + (page + 1) + " out of " + (lista.size() / pageSize));
			int i = page * pageSize;
			int counter = 0;
			
			while (counter < pageSize)
			{
				System.out.println("Cliente " + lista.get(i++));
				counter++;
			}
			
			System.out.println("D para avançar para a filial seguinte, A para a filial anterior ou Q para sair da query.");
			String input = Input.lerString();
			
			switch (input)
			{
				case "D":
					page++;
					break;
					
				case "A":
					page--;
					break;
				
				case "Q":
					running = false;
					break;
				
			}
		}
		
	}
	
	public void showQueryI8 (CodigoNumeroPar lista)
	{
		ArrayList <String> codigos = lista.getCodigos();
		ArrayList <Integer> numeros = lista.getValoresArray();
		
		boolean running = true;
		int page = 0;
		int pageSize = 2;
		
		while (running)
		{
			System.out.println("Pagina " + (page + 1) + " out of " + (codigos.size() / 2 + 1));
			int control = 0;
			int i = page * pageSize;
			
			while (control < pageSize && i < codigos.size())
			{
				System.out.println("Cliente " + codigos.get(i) + "     Numero de Produtos " + numeros.get(i++));
				control++;
			}
			
			System.out.println("Pressione D para ir para a pagina seguinte, A para a pagina anterior, Q para sair desta query, ou insira o codigo de um Cliente para ver se faz parte da lista");
			String input = Input.lerString();
			
			switch (input)
			{
				case "D":
					page++;
					break;
					
				case "A":
					page--;
					break;
				
				case "Q":
					running = false;
					break;
					
				default:
				{
					if (codigos.contains(input))
					{
						int index = codigos.indexOf(input);
						System.out.println("Cliente existe na lista e comprou " + numeros.get(index) + " Produtos distintos");
					}
					
					else System.out.println("Cliente não faz parte da lista");
					break;
				}
				
			}
		}
	}
	
	public void showQueryI9 (Query9 lista)
	{
		ArrayList <String> clientes = lista.getClientes();
		ArrayList <Float> faturado = lista.getFaturado();
		
		boolean running = true;
		int page = 0;
		int pageSize = 2;
		
		while (running)
		{
			System.out.println("Pagina " + (page + 1) + " out of " + (clientes.size() / 2 + 1));
			int control = 0;
			int i = page * pageSize;
			
			while (control < pageSize && i < clientes.size())
			{
				System.out.println("Cliente " + clientes.get(i) + "     Faturação " + faturado.get(i++));
				control++;
			}
			
			System.out.println("Pressione D para ir para a pagina seguinte, A para a pagina anterior, Q para sair desta query, ou insira o codigo de um Cliente para ver se faz parte da lista");
			String input = Input.lerString();
			
			switch (input)
			{
				case "D":
					page++;
					break;
					
				case "A":
					page--;
					break;
				
				case "Q":
					running = false;
					break;
					
				default:
				{
					if (clientes.contains(input))
					{
						int index = clientes.indexOf(input);
						System.out.println("Cliente existe na lista e faturou  " + faturado.get(index));
					}
					
					else System.out.println("Cliente não faz parte da lista");
					break;
				}
				
			}
		}
		
	}

	public void showQueryI10 (ArrayList<ArrayList<HashMap<String,Float>>> lista)
	{
		boolean running = true;
		int filialNumber = 0;
		int month = 0;
		int produtosPage = 0;
		int pageSize = 10;
		
		while (running)
		{
			System.out.println("Informação referente ao mês " + (month + 1) + " out of " + lista.size());
			System.out.println("Informação referente à Filial " + (filialNumber + 1) + " out of 3");
			
			ArrayList <HashMap <String,Float>> byMonth = lista.get(month);
			HashMap <String,Float> byFilial = byMonth.get(filialNumber);
			ArrayList <String> produtos = new ArrayList<>();
			ArrayList <Float> faturacao = new ArrayList<>();
			for (Map.Entry<String, Float> entry: byFilial.entrySet())
			{
				produtos.add(entry.getKey());
				faturacao.add(entry.getValue());
			}
			
			int counter = 0;
			int i = produtosPage * pageSize;
			while (counter < pageSize)
			{
				System.out.println("Produto: " + produtos.get(i) + " Faturado associado: " + faturacao.get(i++));
				counter++;
			}
				
			
			System.out.println("Pressione D para ir para a pagina seguinte de produtos, A para a pagina anterior de produtos, Q para sair desta query, ou insira o codigo de um Produto para ver se faz parte da lista");
			System.out.println("Pressione H para avançar para o mês seguinte, G para o mês anterior");
			System.out.println("Pressione K para avançar para a filial seguinte, J para a filial anterior");
			
			String input = Input.lerString();
			
			switch (input)
			{
				case "D":
					produtosPage++;
					break;
					
				case "A":
					produtosPage--;
					break;
				
				case "Q":
					running = false;
					break;
					
				case "H":
					month++; produtosPage = 0; filialNumber = 0;
					break;
					
				case "G":
					month--; produtosPage = 0; filialNumber = 0;
					break;
					
				case "K":
					filialNumber++; month = 0; produtosPage = 0;
					break;
					
				case "J":
					filialNumber--; month = 0; produtosPage = 0;
					break;
					
				default:
				{
					if (produtos.contains(input))
					{
						int index = produtos.indexOf(input);
						System.out.println("Produto existe na lista e faturou  " + faturacao.get(index));
					}
					
					else System.out.println("Produto não faz parte da lista");
					break;
				}
				
			}
		}
	}
	
}
