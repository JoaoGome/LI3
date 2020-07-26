#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/parser.h"

/*
 ----------------------- Funções para validar codigos de clientes, produtos e vendas-----------------
 */

/*funcao que testa se uma sequencia de char de tamanho size sao letras */
int isLetra (char* line, int size)
{
    int answer = 1;
    
    int i;
    for (i = 0; i < size; i++)
    {
        if (!(line[i] >= 'A' && line[i] <= 'Z')) {
            return 0;
        }
    }
    
    return answer;
}

/*funcao que testa se uma sequencia de char de tamanho size sao numeros */
int isNumero (char* line, int size)
{
    int answer = 1;
    
    int i;
    for (i = 0; i < size; i++)
    {
        if (!(line[i] >= '0' && line[i] <= '9')) {
            return 0;

        }
    }
    
    return answer;
}

/*funcao que testa se um codigo de produto é valido */
int testaP (char* line)
{
    return ((isLetra(line,2)) && (isNumero((line + 2*sizeof(char)),4)) && strlen(line) == 6);
}

/*funcao que testa se um codigo de client é valido */
int testaC (char* line)
{
    return ((isLetra(line,1)) && (isNumero((line + 1*sizeof(char)),4)) && strlen(line) == 5);
}


/*funcao que testa se um codigo de vendas é valido */
int testaV (char* line)
{
    int testa = 1;
    int place = 0;
    char *token;
    char* line2 = strdup(line);
    
    token = strtok(line2," ");
    while (token != NULL)
    {
        switch (place)
        {
            case 0:/*produto */
            {
                if (!testaP(token))
                    testa = 0;
                
            } break;
                
            case 1:/*preco*/
            {
                float price = strtof(token,NULL);
                if (price > 999.99f || price < 0.0f)
                    testa = 0;
                
            } break;
                
            case 2:/*quantidade*/
            {
                int numberBought = atoi(token);
                if (numberBought > 200 || numberBought < 1)
                    testa = 0;
                
            } break;

            case 3:/*modo*/
            {
                if (!(token[0] == 'P' || token[0] == 'N'))
                    testa = 0;
                
            } break;
                
            case 4:/*codigo cliente*/
            {
                if (!testaC(token))
                    testa = 0;
                
            } break;
            
            case 5:/*mes*/
            {
                int month = atoi(token);
                if (month > 12 || month < 1)
                    testa = 0;
                
            } break;
                
            case 6:/*filial*/
            {
                int filial = atoi (token);
                if (filial > 3 || filial < 1)
                    testa = 0;
                
            } break;
                
                
        }
        
        token = strtok(NULL, " ");
        place++;
    }
    
    return testa;
}


/*
 ----------------------------- Funções de parsing para os codigos de vendas, que retiram informaçao necessaria--------------------------------
 */

/*
 Example : KR1583 77.72 128 P L4891 2 1
 0 -> KR1583 codigo de produto
 1 -> 77.72 preço
 2 -> 128 quantidade
 3 -> P com promoçao
 4 -> L4891 codigo do cliente
 5 -> 2  mes da compra
 6 -> filial
 */
char* parseVendas (char* line, int position)
{
    
    char* line2 = strdup(line);
    char* token = strtok(line2," ");
    
    
    if (position == 0) return token;
    
    else
    {
        int i;
        for (i = 0; i < (position); i++)
        {
            token = strtok(NULL," ");
        }
        
        return token;
    }
    
    
    
}
