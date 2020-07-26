#include "../include/catalogoClientes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmodule.h>

/*
 ------------------------- STRUCT CATALOGO ------------------------
 */


typedef struct catalogoClientes
{
    GSequence* clientList;
    int numberElements;
}*CatalogoClientes;

void freeAuxClientes(char* nome)
{
    free(nome);
}

/*funcao que cria uma struct e devolve apontador para ela*/
CatalogoClientes initCatalogoClientes ()
{
    CatalogoClientes l = malloc (sizeof(struct catalogoClientes));
    l -> clientList = g_sequence_new(freeAuxClientes);
    l -> numberElements = 0;
    return l;
}
/*funcao que devolve a Sequence recebendo a estrutura que a envolve*/
GSequence* getSequenceClientes (CatalogoClientes l)
{
    return l -> clientList;
}

/*funao de compare usada para ordenar o array e para fazer binary search*/
int compareClientes (gconstpointer a, gconstpointer b)
{
    char* cast_a_pointer = (char*) a;
    char* cast_b_pointer = (char*) b;
    
    return strcmp(cast_a_pointer,cast_b_pointer);
}

/* funcao que ordena o array alfabeticamente*/
void sortArrayClientes (CatalogoClientes l)
{
    g_sequence_sort(l -> clientList,compareClientes,NULL);
}

/* funcao que adiciona um produto ao array*/
void addClient (CatalogoClientes l, char* client)
{
    g_sequence_append(l->clientList,(gpointer) client);
    l -> numberElements++;
}

/* funcao que liberta a estrutura no final do programa*/
void freeCatalogoClientes (CatalogoClientes l)
{
    g_sequence_free(l ->clientList);
    free(l);
        
}

/*verifica que se um produto ja existe no catalogo*/
int checkExisteCliente (CatalogoClientes l, char* client)
{
    if(g_sequence_lookup(l -> clientList,client,compareClientes,NULL) == NULL) return 0;
    else return 1;
}


void printAuxClientes (char* cliente)
{
    printf("%s\n",cliente);
}

/*print aos produto na posiçao i*/
void printCatalogoClientes (CatalogoClientes l)
{
    g_sequence_foreach(l -> clientList,printAuxClientes,NULL);
}


/*posiçao que devolve numero de elementos*/
int numeroClientes (CatalogoClientes l)
{
    return (l -> numberElements);
}


