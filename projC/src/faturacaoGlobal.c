#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/faturacaoGlobal.h"
#include <gmodule.h>

/* estrutura principal */
typedef struct faturacao
{
    
    int* vendasN;
    int* vendasP;
    
    float* totalN;
    float* totalP;
    int init;
    
}*Faturacao;


/*estrutura que apenas vai dar wrap ao array das estruturas de cima*/
typedef struct faturacaoGlobal
{
    GTree* faturacao_tree;
}*FaturacaoGlobal;


/*funcao de comparaçao para inicializar a tree */
int compareProductName (gconstpointer a, gconstpointer b)
{
    char* cast_a_pointer = (char*) a;
    char* cast_b_pointer = (char*) b;
    
    return strcmp(cast_a_pointer,cast_b_pointer);
}

/* inicializar a struct com a tree */
FaturacaoGlobal createFaturacaoGlobal ()
{
    FaturacaoGlobal faturacao = malloc (sizeof(struct faturacaoGlobal));
    faturacao -> faturacao_tree = g_tree_new (compareProductName);
    return faturacao;
}

/*devolve o valor de vendas no modo N na posicao "position"*/
int getValorVendasN (Faturacao f, int position)
{
    return (f -> vendasN[position]);
}

/*devolve o valor de vendas no modo P na posicao "position"*/
int getValorVendasP (Faturacao f, int position)
{
    return (f -> vendasP[position]);
}

/*devolve o valor da faturacao no modo N na posicao "position"*/
float getFaturacaoN (Faturacao f, int position)
{
    return (f -> totalN[position]);
}

/*devolve o valor de faturacao no modo P na posicao "position"*/
float getFaturacaoP (Faturacao f, int position)
{
    return (f -> totalP[position]);
}

/*devolve o valor total de vendas (P e N) na posicao position"*/
int getValorVendas (Faturacao f,int position)
{
    return (f -> vendasN[position] + f -> vendasP[position]);
}

/*devolve o valor total de faturacao (P e N) na posicao position"*/
float getValorFaturacao (Faturacao f, int position)
{
    return (f -> totalN[position] + f -> totalP[position]);
}



/* inicializar a struct faturaçao*/
Faturacao createFaturacao ()
{
    Faturacao faturacao = malloc (sizeof(struct faturacao));
    faturacao -> init = 0;
    faturacao -> vendasN = calloc(36,sizeof(int));
    faturacao -> vendasP = calloc(36,sizeof(int));
    faturacao -> totalN = calloc(36,sizeof(float));
    faturacao -> totalP = calloc(36,sizeof(float));
    
    return faturacao;
}

/*devolve a tree que é wraped pela faturacao global*/
GTree* getTree(FaturacaoGlobal fGlobal)
{
    return fGlobal -> faturacao_tree;
}

/*devolve o init da faturacao*/
int getInit (Faturacao f)
{
    return f-> init;
}

/*funcao que adiciona um produto à Tree*/
void addProdutoFaturacao (FaturacaoGlobal fGlobal, Faturacao f, char* produto)
{
    g_tree_insert(fGlobal -> faturacao_tree,produto,f);
}

/*funcao que atualiza os dados referentes a um produto após processar uma venda */
void addVendaFaturacao (FaturacaoGlobal fGlobal, int month, int filial, char* mode, char* produto, float price, int quantidade)
{
    Faturacao f = (Faturacao) g_tree_lookup(fGlobal -> faturacao_tree,produto);
    
    if(f != NULL)
    {
        f -> init = 1;
        float soma = price*quantidade;
        if (mode[0] == 'N')
        {
            
            f -> vendasN[12*(filial - 1) + (month - 1)] += quantidade;
            f -> totalN[12*(filial - 1) + (month - 1)] += soma;
            
        }
            
        else
        {
            f -> vendasP[12*(filial - 1) + (month - 1)] += quantidade;
            f -> totalP[12*(filial - 1) + (month - 1)] += soma;
        }
    }
    
}

/*funcao auxiliar para dar free à memoria */
gboolean freeAux(gpointer key, gpointer value, gpointer data)
{
    Faturacao x = (Faturacao) value;
    free(x -> vendasN);
    free(x -> vendasP);
    free(x -> totalN);
    free(x -> totalP);
    free(x);
    return FALSE;
}

/*funcao que dá free a toda a memoria alocada pela estrutura */
void freeFaturacao (FaturacaoGlobal f)
{
    g_tree_foreach(f -> faturacao_tree,(GTraverseFunc)freeAux,NULL);
    g_tree_destroy(f -> faturacao_tree);
    free(f);
}

/*funcao auxiliar para dar print aos produtos na estrutura*/
gboolean printAux(gpointer key, gpointer value, gpointer data)
{
    printf("%s\n",key);
    return FALSE;
}

/* funcao que da print a estrutura*/
void printFaturacao(FaturacaoGlobal f)
{
    g_tree_foreach(f -> faturacao_tree,(GTraverseFunc)printAux,NULL);
}

/*devolve o numero de nodos da tree contida em f*/
int numeroNodes (FaturacaoGlobal f)
{
    
    return (int) g_tree_nnodes(f -> faturacao_tree);
}
