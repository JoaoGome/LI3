import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

import Auxiliar.*;
import Modelo.*;
import View.*;

public class Controlador implements ControladorInterface{
	
	private ViewInterface view;
	private GestVendasInterface gestVendas;
	private int control; // se estiver a 0 estamos menu inicial. se estiver a 1, estamos menu das queries estatisticas, se estiver a 2, estamos menu das queries interativas
	private boolean running;
	
	public void init ()
	{
		this.view = new View ();
		this.gestVendas = new GestVendas();
		this.gestVendas.init(3);
		this.control = 0;
		this.running = true;
		
	}
	
	public void saveToFile (String file) throws IOException
    {
    	FileOutputStream f = new FileOutputStream(new File(file));
		ObjectOutputStream o = new ObjectOutputStream(f);

		// Write objects to file
		o.writeObject(this.gestVendas);
		f.close();
		o.close();
    }
	
	public void loadFromFile (String file) throws IOException, ClassNotFoundException
	{
		FileInputStream fi = new FileInputStream(new File(file));
		ObjectInputStream oi = new ObjectInputStream(fi);

		this.gestVendas = (GestVendasInterface) oi.readObject();
		oi.close();
		fi.close();
	}
	
	public void start () throws IOException, ClassNotFoundException
	{
		while(this.running)
		{
			switch (this.control)
			{
				case 0:
				{
					int input = this.view.mainMenu();
					switch (input)
					{
						case 0:
						{
							String lista [] = this.view.askFicheiros();
							this.gestVendas.loadFiles(lista[0], lista[1], lista[2]);
							break;
						}
						
						case 1:
						{
							this.control++;
							break;
						}
						
						case 2:
						{
							this.control += 2;
							break;
						}
						
						case 3: running = false;
								break;
								
						case 4: System.out.println("Introduza Path do ficheiro");
								String path = Input.lerString();
								saveToFile(path);
								break;
						
						case 5: System.out.println("Introduza path para o ficheiro");
								String path2 = Input.lerString();
								loadFromFile (path2);
								break;
						
						
					}
				} break;
				
				case 1:
				{
					int input = this.view.menuEstasticas();
					switch(input)
					{
						case 0: this.view.showQueryE1(this.gestVendas.infoUltimaVendas());
								break;
								
						case 1: this.view.showQueryE21(this.gestVendas.totalCompras());
								break;
								
						case 2: this.view.showQueryE22(this.gestVendas.faturacaoPorMes());
								break;
								
						case 3: this.view.showQueryE23(this.gestVendas.clientesPorMes());
								break;
						
						case 4: this.control--;
								break;
					}
				}break;
				
				case 2: 
				{
					int input = this.view.menuInterativas();
					switch(input)
					{
						case 1: this.view.showQueryI1(this.gestVendas.query1());
								break;
								
						case 2: System.out.println("Introduza um mês válido");
								int mes = Input.lerInt();
								this.view.showQueryI2(this.gestVendas.query2(mes));
								break;
								
						case 3: System.out.println("Introduza um código de um cliente válido");
								String codigo = Input.lerString();
								this.view.showQueryI3(this.gestVendas.query3(codigo));
								break;
								
						case 4: System.out.println("Introduza um codigo de um produto existente");
								String produto = Input.lerString();
								this.view.showQueryI4(this.gestVendas.query4(produto));
								break;
								
						case 5: System.out.println("Introduza um código de um cliente existente");
								String cliente = Input.lerString();
								System.out.println("Introduza valor de X");
								int top = Input.lerInt();
								this.view.showQueryI5(this.gestVendas.query5(cliente, top));
								break;
								
						case 6: System.out.println("Introduza valor de X");
								int top2 = Input.lerInt();
								this.view.showQueryI6(this.gestVendas.query6(top2));
								break;
								
						case 7: this.view.showQueryI7(this.gestVendas.query7());
								break;
								
						case 8: System.out.println("Introduza o valor de X");
								int top3 = Input.lerInt();
								this.view.showQueryI8(this.gestVendas.query8(top3));
								break;
						
						case 9: System.out.println("Introduza código de um produto");
								String produto2 = Input.lerString();
								System.out.println("Introduza o valor de X");
								int top4 = Input.lerInt();
								this.view.showQueryI9(this.gestVendas.query9(produto2, top4));
								break;
								
						case 10: this.view.showQueryI10(this.gestVendas.query10());
									break;
									
						case 11: this.control -= 2;
									break;
					}
				} break;
				
				
				
			}
		}
		
	}
	
}
