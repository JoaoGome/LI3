#include <stdio.h>
#include <string.h>
#include "../include/reader.h"
#include "../include/parser.h"
#include "../include/catalogoClientes.h"
#include "../include/catalogoProdutos.h"
#include "../include/faturacaoGlobal.h"
#include "../include/sistemaGestaoVendas.h"
#include "../include/gestaoFilial.h"

void readFiles (char* pathProdutos, char* pathClientes, char* pathVendas, SGV sgv)
{
    
    CatalogoProdutos produtosList = getProdutos(sgv);
    CatalogoClientes clientesList = getClientes(sgv);
    FaturacaoGlobal fGlobal = getFaturacao(sgv);
    GestaoFilial gFilial1 = getGestaoFilial1(sgv);
    GestaoFilial gFilial2 = getGestaoFilial2(sgv);
    GestaoFilial gFilial3 = getGestaoFilial3(sgv);
    
    int produtosL = 0;
    int produtosV = 0;
    int clientesL = 0;
    int clientesV = 0;
    int vendasL = 0;
    int vendasV = 0;
    
    /* parte dos produtos */
    FILE* fp;
    char lineProdutos[7];
    fp = fopen(pathProdutos,"r");
    
    while (fgets(lineProdutos, sizeof(lineProdutos),fp))
    {
        produtosL++;
        if (testaP(lineProdutos))
        {
            produtosV++;
            char* nome = strdup(lineProdutos);
            addProduto(produtosList, nome);
            char* name = strdup(lineProdutos);
            Faturacao f = createFaturacao();
            addProdutoFaturacao(fGlobal,f,name);
            char* nomeF = strdup(lineProdutos);
            DadosClientes d1 = createDadosClientes();
            DadosClientes d2 = createDadosClientes(); 
            DadosClientes d3 = createDadosClientes();  
            addProdutoGestaoFilial(gFilial1 ,d1,nomeF);
            addProdutoGestaoFilial(gFilial2 ,d2,nomeF);
            addProdutoGestaoFilial(gFilial3 ,d3,nomeF);
        }
    }
    fclose(fp);
    
    /* parte dos clientes */
    char lineClientes[6];
    fp = fopen(pathClientes,"r");
    
    while (fgets(lineClientes, sizeof(lineClientes),fp))
    {
        clientesL++;
        if (testaC(lineClientes))
        {
            clientesV++;
            char* nome = strdup(lineClientes);
            addClient(clientesList, nome);
            DadosProdutos dp1 = createDadosProdutos();
            DadosProdutos dp2 = createDadosProdutos();
            DadosProdutos dp3 = createDadosProdutos();
            addClienteGestaoFilial(gFilial1 ,dp1,nome);
            addClienteGestaoFilial(gFilial2 ,dp2,nome);
            addClienteGestaoFilial(gFilial3 ,dp3,nome);
            
        }
    }
    
    fclose(fp);
    
    sortArrayClientes(clientesList);
    sortArrayProdutos(produtosList);
    
    /* parte das vendas */
    
    char lineVendas[33];
    fp = fopen(pathVendas,"r");
    int vendas = 0;
    while (fgets(lineVendas,sizeof(lineVendas),fp))
    {
        vendasL++;
        
        char* produto = parseVendas(lineVendas,0);
        char* cliente = parseVendas(lineVendas,4);
        
        
        if(checkExisteProduto(produtosList,produto) && checkExisteCliente(clientesList,cliente))
        {
            vendasV++;
            char* mode = parseVendas(lineVendas,3);
            char* price = parseVendas(lineVendas,1);
            char* quantidade = parseVendas(lineVendas,2);
            char* month = parseVendas(lineVendas,5);
            char* filial = parseVendas(lineVendas,6);
            
            int mes = atoi(month);
            int filialI = atoi(filial);
            int quantidadeI = atoi(quantidade);
            double preco = atof(price);
            addVendaFaturacao(fGlobal,mes,filialI,mode,produto,preco,quantidadeI);
            if (filialI == 1)
            {
                addVendaFilial(gFilial1,produto,preco,quantidadeI,mode,cliente,mes);
            }
            else if (filialI == 2)
            {
                addVendaFilial(gFilial2,produto,preco,quantidadeI,mode,cliente,mes);
            }
            else
            {
                addVendaFilial(gFilial3,produto,preco,quantidadeI,mode,cliente,mes);
            }
        }
    }
    
    fclose(fp);
    printf("\n");
    printf("Ficheiro %s lido\n",pathProdutos);
    printf("Foram lidas %d linhas, mas apenas %d são validas\n",produtosL,produtosV);
    printf("\n");
    printf("Ficheiro %s lido\n",pathClientes);
    printf("Foram lidas %d linhas, mas apenas %d são validas\n",clientesL,clientesV);
    printf("\n");
    printf("Ficheiro %s lido\n",pathVendas);
    printf("Foram lidas %d linhas, mas apenas %d são validas\n",vendasL,vendasV);
}
