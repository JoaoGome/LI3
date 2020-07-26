#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/faturacaoGlobal.h"
#include "../include/gestaoFilial.h"
#include <gmodule.h>

/*estrutura principal*/
typedef struct vendas
{
    int* vendasN;/* nr total de vendas em N e P*/
    int* vendasP;

    double* revenueN;/* valor total obtido com as vendas em N e P*/
    double* revenueP;

}*Vendas;

/*estrutura que da wrap a estrutura de cima ( 1 elemento para cada cliente que comprou o dado produto)*/
typedef struct dadosClientes
{
    GTree* dadosClientes_tree;
}*DadosClientes;

/*estrutura que da wrap a estrutura de cima ( 1 elemento para cada cliente que comprou o dado produto)*/
typedef struct dadosProdutos
{
    GTree* dadosProdutos_tree;
}*DadosProdutos;

/*estrutura que vai dar wrap ao array das estruturas de cima*/
typedef struct gestaoFilial
{
    GTree* gestaoFilialC_tree;/* tree dos produtos -> clientes*/
    GTree* gestaoFilialP_tree;/* tree dos clientes -> prodtuos*/

}*GestaoFilial;

/*funcao de comparaçao para inicializar a tree */
int compareFunc (gconstpointer a, gconstpointer b)
{
    char* cast_a_pointer = (char*) a;
    char* cast_b_pointer = (char*) b;
    
    return strcmp(cast_a_pointer,cast_b_pointer);
}

/*devolve toda a revenue feita num ano em ambos os modos*/
int getRevenueTotal (Vendas v)
{
    int x = 0;
    int i;
    for (i = 0; i < 12; i++)
        x += v -> revenueN[i] + v->revenueP[i];
    
    return x;  
}

/*devolve a quantidade de produtos comprados num dado mes em ambos os modos*/
int getQuantidadeMes(Vendas v, int mes)
{
    int x =0;
    int i;
    x += v -> vendasN[mes] + v-> vendasP[mes]; 
    return x;
}


/* inicializar a struct do global com ambas as trees  */
GestaoFilial createGestaoFilial ()
{
    GestaoFilial gestaoFilial = malloc (sizeof(struct gestaoFilial));
    gestaoFilial -> gestaoFilialP_tree = g_tree_new (compareFunc);
    gestaoFilial -> gestaoFilialC_tree = g_tree_new (compareFunc);
    return gestaoFilial;
}

GTree* getTreeProdutos (GestaoFilial gF)
{
    return gF -> gestaoFilialP_tree;
}

GTree* getTreeClientes (GestaoFilial gF)
{
    return gF -> gestaoFilialC_tree;
}

GTree* getDadosClientesTree (DadosClientes dC)
{
    return dC -> dadosClientes_tree;
}

GTree* getDadosProdutosTree (DadosProdutos dP)
{
    return dP -> dadosProdutos_tree;
}

int getNumeroVendasGF(Vendas v, int mes)
{
    return (v -> vendasN[mes] + v -> vendasP[mes]); 
}

/*devolve o nr de compras feitas pelo cliente 
 >0 -> fez compras  // ==0 -> nao fez compras
 */
int fezCompras(char* cliente, GestaoFilial gf)
{
    GTree* treeC = gf -> gestaoFilialC_tree; /* pega na struct e da a tree*/
    DadosProdutos sProdutos = g_tree_lookup(treeC,cliente); /* pega na tree dos clientes e da a struct*/
    GTree* treeP =sProdutos -> dadosProdutos_tree; /* Pega na struct dos produtos e da a tree*/
    int h = g_tree_height(treeP); /* height da tree*/
    return h;
}

/* inicializar a struct relatva a cada cliente com a tree */
DadosClientes createDadosClientes ()
{
    DadosClientes dadosClientes = malloc(sizeof(struct dadosClientes));
    dadosClientes -> dadosClientes_tree = g_tree_new (compareFunc);
    return dadosClientes;
}

/* inicializar a struct relatva a cada produto com a tree */
DadosProdutos createDadosProdutos ()
{
    DadosProdutos dadosProdutos = malloc(sizeof(struct dadosProdutos));
    dadosProdutos -> dadosProdutos_tree = g_tree_new (compareFunc);
    return dadosProdutos;
}

/* inicializa a estrutuda de vendas*/
Vendas createVendas ()
{
    Vendas vendas = malloc (sizeof(struct vendas));
    
    vendas -> vendasN = calloc(12,sizeof(int));
    vendas -> vendasP = calloc(12,sizeof(int));
    vendas -> revenueN = calloc(12,sizeof(double));
    vendas -> revenueP = calloc(12,sizeof(double));
    return vendas;
}

/*adiciona um cliente a tree dos produtos*/
void addProdutoGestaoFilial (GestaoFilial gFilial, DadosClientes dadosClientes , char* produto)
{
    g_tree_insert(gFilial -> gestaoFilialP_tree , produto , dadosClientes);
}

/*addiciona uma venda a tree do cliente*/
void addClienteinPGF (DadosClientes dadosClientes , char* cliente, Vendas venda)
{
    g_tree_insert(dadosClientes -> dadosClientes_tree , cliente , venda);
}

/*adiciona um cliente a tree dos produtos*/
void addClienteGestaoFilial (GestaoFilial gFilial, DadosProdutos dadosProdutos , char* cliente)
{
    g_tree_insert(gFilial -> gestaoFilialC_tree , cliente , dadosProdutos);
}

/*addiciona uma venda a tree do cliente*/
void addProdutoinCGF (DadosProdutos dadosProdutos , char* produto, Vendas venda)
{
    g_tree_insert(dadosProdutos-> dadosProdutos_tree , produto, venda);
}

/* funcao que atualiza os dados de uma venda*/
void addVendaFilial (GestaoFilial gestaoFilial, char* produto , double preco ,int quantidade , char modo , char* cliente, int mes)
{
    
    
    /*p é a tree do produto*/
    DadosProdutos dp = (g_tree_lookup(gestaoFilial -> gestaoFilialC_tree , cliente));
    DadosClientes dc = (g_tree_lookup(gestaoFilial -> gestaoFilialP_tree , produto));

    /* v é estrutura (vendas) od cliente em questao*/
    Vendas v = g_tree_lookup(dc -> dadosClientes_tree , cliente);
    
    if (v==NULL)
        {
            v = createVendas();

            addClienteinPGF(dc , cliente, v );
            addProdutoinCGF(dp , produto, v );
            v = g_tree_lookup(dc -> dadosClientes_tree , cliente);
        }
    
    
    if (modo == 'N')
    {
        
        v -> vendasN[mes-1]+= quantidade;
        v -> revenueN[mes-1] += quantidade*preco;
    }
    else
    {
        v -> vendasP[mes-1] += quantidade;
        v -> revenueP[mes-1] += quantidade*preco;
    }
}

/*funcao auxiliar para dar free à memoria */
gboolean freeAuxF(gpointer key, gpointer value, gpointer data)
{
    Vendas x = (Vendas) value;
    free(x -> vendasN);
    free(x -> vendasP);
    free(x -> revenueN);
    free(x -> revenueP);
    free(x);
    return FALSE;
}

/*funcao que dá free a toda a memoria alocada pela estrutura */
void freeDadosClientes (DadosClientes dc)
{
    g_tree_foreach(dc -> dadosClientes_tree,(GTraverseFunc)freeAuxF,NULL);
    g_tree_destroy(dc -> dadosClientes_tree);
    free(dc);
}

/*funcao que dá free a toda a memoria alocada pela estrutura */
void freeDadosProdutos (DadosClientes dc)
{
    g_tree_destroy(dc -> dadosClientes_tree);
    free(dc);
}

/*funcao que dá free a toda a memoria alocada pela estrutura */
void freeGestaoFilial (GestaoFilial gf)
{
    g_tree_foreach(gf -> gestaoFilialC_tree,(GTraverseFunc)freeDadosClientes,NULL);
    g_tree_foreach(gf -> gestaoFilialC_tree,(GTraverseFunc)freeDadosProdutos,NULL);
    g_tree_destroy(gf -> gestaoFilialC_tree);
    free(gf);
}

/*funcao auxiliar para dar print aos clientes na estrutura*/
gboolean printAuxF2(gpointer key, gpointer value, gpointer data)
{
    printf("%s\n",key);
    return FALSE;
}

/*funcao auxiliar para dar print aos produtos na estrutura*/
gboolean printAuxF(gpointer key, gpointer value, gpointer data)
{
    printf("o Produto: %s\n foi comprado pelos seguintes clientes:",key);
    DadosClientes cast_value = (DadosClientes) value;
    g_tree_foreach(cast_value -> dadosClientes_tree,(GTraverseFunc)printAuxF2,NULL);
    return FALSE;
}


/*funcao auxiliar para dar print aos produtos na estrutura*/
void printFilial(GestaoFilial gf)
{
    g_tree_foreach(gf -> gestaoFilialC_tree, (GTraverseFunc)printAuxF ,NULL);
}

/*funcao que devolve o numero de produtos na filial*/
int numeroProdutosFilial (GestaoFilial gf)
{
    return (int) g_tree_nnodes(gf -> gestaoFilialC_tree);
}

/*funcao que devolve o numero de clientres na tree dos produtos*/
int numeroClientesinP(GestaoFilial gf, char* produto)
{
    DadosClientes vendas = g_tree_lookup(gf -> gestaoFilialC_tree,produto);
    return g_tree_nnodes(vendas -> dadosClientes_tree);
}

/*funcao que devolve o numero de produtos na tree dos clientes*/
int numeroProdutosinC(GestaoFilial gf, char* cliente)
{
    DadosClientes vendas = g_tree_lookup(gf -> gestaoFilialP_tree,cliente);
    return g_tree_nnodes(vendas -> dadosClientes_tree);
}
