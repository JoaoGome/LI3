package Reader;


public class Parser implements ParserInterface
{
	
	public boolean testClient (String codigo)
	{
		boolean result = false;
		
		if(codigo.length() == 5 && Character.isUpperCase(codigo.charAt(0)) && Character.isDigit(codigo.charAt(1)) && Character.isDigit(codigo.charAt(2))&& Character.isDigit(codigo.charAt(3))&& Character.isDigit(codigo.charAt(4)))
		{
			result = true;
		}
		
		return result;
	}
	
	public boolean testProduct (String codigo)
	{
		boolean result = false;
		if(codigo.length() == 6 && Character.isUpperCase(codigo.charAt(0)) && Character.isUpperCase(codigo.charAt(1)) && Character.isDigit(codigo.charAt(2)) && Character.isDigit(codigo.charAt(3))&& Character.isDigit(codigo.charAt(4))&& Character.isDigit(codigo.charAt(5)))
		{
			result = true;
		}
		
		return result;
	}
	
	public boolean testSales (String codigo)
	{
		boolean result = true;
		String parser [] = codigo.split(" ");
		float price = Float.parseFloat(parser[1]);
		int quantidade = Integer.parseInt(parser[2]);
		int month = Integer.parseInt(parser[5]);
		int filial = Integer.parseInt(parser[6]);
		char mode = parser[3].charAt(0);
		
		for (int i = 0; i < parser.length; i++)
		{
			switch(i)
			{
				case 0: 
				{
					if(this.testProduct(parser[i]) == false) result = false;
					break;
				}
				
				case 1:
				{
					if (price > 999.99 || price < 0.0) result = false;
					break;
				}
				
				case 2:
				{
					if (quantidade > 200 || quantidade < 0) result = false;
					break;
				}
				
				case 3:
				{
					if(mode != 'P' && mode != 'N') result = false;
					break;
				}
				
				case 4:
				{
					if(this.testClient(parser[i]) == false) result = false;
					break;
				}
				
				case 5:
				{
					if (month > 12 || month < 1) result = false;
					break;
				}
				
				case 6:
				{
					if (filial > 3 || filial < 1) result = false;
					break;
				}
			}
		}
		return result;
    }
}

