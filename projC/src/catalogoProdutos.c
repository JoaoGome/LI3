#include "../include/catalogoProdutos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmodule.h>

/*
 ------------------------- STRUCT CATALOGO ------------------------
 */

typedef struct catalogoProdutos
{
    GSequence* produtosList;
    int numberElements;
}*CatalogoProdutos;

void freeAuxProdutos(char* nome)
{
    free(nome);
}

/*funcao que cria uma struct e devolve apontador para ela*/
CatalogoProdutos initCatalogoProdutos ()
{
    CatalogoProdutos l = malloc (sizeof(struct catalogoProdutos));
    l -> produtosList = g_sequence_new(freeAuxProdutos);
    l -> numberElements = 0;
    return l;
}
/*funcao recebe um catalogo de produtos e devolve a sequenceia a que este esta a dar wrap*/
GSequence* getSequenceProdutos (CatalogoProdutos l)
{
    return l -> produtosList;
}

/*funao de compare usada para ordenar o array e para fazer binary search*/
int compareProdutos (gconstpointer a, gconstpointer b)
{
    char* cast_a_pointer = (char*) a;
    char* cast_b_pointer = (char*) b;
    
    return strcmp(cast_a_pointer,cast_b_pointer);
}

/* funcao que ordena o array alfabeticamente*/
void sortArrayProdutos (CatalogoProdutos l)
{
    g_sequence_sort(l -> produtosList,compareProdutos,NULL);
}

/* funcao que adiciona um produto ao array*/
void addProduto (CatalogoProdutos l, char* produto)
{
    g_sequence_append(l->produtosList,(gpointer) produto);
    l -> numberElements++;
}

/* funcao que liberta a estrutura no final do programa*/
void freeCatalogoProdutos (CatalogoProdutos l)
{
    g_sequence_free(l ->produtosList);
    free(l);
}

/*verifica que se um produto ja existe no catalogo*/
int checkExisteProduto (CatalogoProdutos l, char* produto)
{
    if(g_sequence_lookup(l -> produtosList,produto,compareProdutos,NULL) == NULL) return 0;
    else return 1;
}

void printAuxProdutos (char* produto)
{
    printf("%s\n",produto);
}

/*print aos produto*/
void printCatalogoProdutos (CatalogoProdutos l)
{
    g_sequence_foreach(l -> produtosList,printAuxProdutos,NULL);
    
}

/*posiçao que devolve numero de elementos*/
int numeroProdutos (CatalogoProdutos l)
{
    return (l -> numberElements);
}




