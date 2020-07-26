#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/catalogoProdutos.h"
#include "../include/catalogoClientes.h"
#include "../include/faturacaoGlobal.h"
#include "../include/sistemaGestaoVendas.h"
#include "../include/reader.h"
#include "../include/gestaoFilial.h"

/* estrutura auxiliar que vai guardar a informaçao responsavel por responder às queries, para depois o controlador dar print*/
typedef struct queryAux
{
    char** lista; /*lista de codigos ou produtos a dar print */
    int size;     /* numero de codigods*/
    char letra;   /* char a usar na query 2*/
    int tab;      /* auxiliar para formatação*/
    int filial;
}*QueryAux;

typedef struct query3
{
    int vendasN;
    int vendasP;
    float faturadoN;
    float faturadoP;
}*Query3;

typedef struct query5
{
    char** lista;/* de produtos*/
    int size;/* tamanha atual da lista*/
    GestaoFilial gf1; 
    GestaoFilial gf2;
    GestaoFilial gf3;
}*Query5;

typedef struct query7s
{
    int* qVendida;/* array 12 posicoe uma para cada mes*/ 
}*Query7;

typedef struct query6
{
    int size1;
    int size2;
    int size3;
    int ocup;
    char** lista1;
    char** lista2;
    char** lista3;
}*Query6;


typedef struct query8
{
    int minMonth;
    int maxMonth;
    long int totalVendas;
    float totalFaturado;
}*Query8;

typedef struct query9
{
    char** lista;
    int size;
}*Query9;

typedef struct query10
{
    GTree* lista;
    GTree* organizada;
    int limit;
    int mes;
    
}*Query10;

typedef struct query11
{
    GTree* lista;
    char** list;
    int* quantidades;
    int* numeroClientes;
    int size;
    int limit;
    int ocup;
}*Query11;

typedef struct query12
{
    GTree* lista;
    GTree* organizada;
    int limit;
    
}*Query12;



/* funçao que cria a estrutura auxiliar QueryAux*/
QueryAux createQueryAux (int x, int filia)
{
    QueryAux qAux = malloc (sizeof(struct queryAux));
    qAux -> size = 0;
    qAux -> tab = 1;
    qAux -> lista = malloc(x*sizeof(char*));
    qAux -> filial = filia;
    int i;
    for (i = 0; i < x; i++)
        qAux -> lista[i] = malloc(7*sizeof(char));
    return qAux;
}

Query3 createQuery3 ()
{
    Query3 q3 = malloc(sizeof(struct query3));
    q3 -> vendasN = 0;
    q3 -> vendasP = 0;
    q3 -> faturadoN = 0;
    q3 -> faturadoP = 0;
    
    
    return q3;
}

Query5 createQuery5 (int n, GestaoFilial g1 ,GestaoFilial g2, GestaoFilial g3)
{
    Query5 q5 = malloc(sizeof(struct query5));
    q5 -> lista = calloc(n,sizeof(char*));
    int i;
    for (i = 0; i < q5 -> size; i++)
        q5 -> lista[i] = malloc(6*sizeof(char));
    q5 -> size = 0;
    q5 -> gf1 = g1;
    q5 -> gf2 = g2; 
    q5 -> gf3 = g3;
}

Query7 createQuery7 (){
    Query7 q7 = malloc(sizeof(struct query7s));
    q7 -> qVendida = calloc(12,sizeof(int));

    return q7;
}

void freequery7 (Query7 q7){
    free(q7 -> qVendida);
    free(q7);
}

Query6 createQuery6 (int size)
{
    Query6 q6 = malloc(sizeof(struct query6));
    q6 -> size1 = 0;
    q6 -> size2 = 0;
    q6 -> size3 = 0;
    q6 -> ocup = size;
    q6 -> lista1 = malloc(q6 -> ocup*sizeof(char*));
    q6 -> lista3 = malloc(q6 -> ocup*sizeof(char*));
    q6 -> lista2 = malloc(q6 -> ocup*sizeof(char*));
    int i;
    for (i = 0; i < q6 -> ocup; i++)
    {
        q6 -> lista1[i] = malloc(6*sizeof(char));
        q6 -> lista2[i] = malloc(6*sizeof(char));
        q6 -> lista3[i] = malloc(6*sizeof(char));
    }
    
    return q6;
}

void freeQ6 (Query6 q6)
{
    for (int i = 0; i < q6 -> ocup; ++i)
    {
        free(q6->lista1[i]);
        free(q6->lista2[i]);
        free(q6->lista3[i]);
    }

    free(q6->lista1);
    free(q6->lista2);
    free(q6->lista3);
    free(q6);
}

Query8 createQuery8 (int minMonth, int maxMonth)
{
    Query8 q8 = malloc(sizeof(struct query8));
    q8 -> minMonth = minMonth;
    q8 -> maxMonth = maxMonth;
    q8 -> totalVendas = 0;
    q8 -> totalFaturado = 0;
    
    return q8;
}

Query9 createQuery9 (int size)
{
    Query9 q9 = malloc(sizeof(struct query9));
    q9 -> lista = malloc(size*sizeof(char*));
    int i;
    for (i = 0; i < size; i++)
        q9 -> lista[i] = malloc(6*sizeof(char));
    q9 -> size = 0;
    
    return q9;
}

int query12Compare (gconstpointer a, gconstpointer b)
{
    char* cast_a_pointer = (char*) a;
    char* cast_b_pointer = (char*) b;
    
    return strcmp(cast_a_pointer,cast_b_pointer);
}

int query11Compare (gconstpointer a, gconstpointer b)
{
    int cast_a_pointer = (int) a;
    int cast_b_pointer = (int) b;
    
    return cast_b_pointer - cast_a_pointer;
}

Query10 createQuery10 (int m)
{
    Query10 q12 = malloc(sizeof(struct query12));
    q12 -> lista = g_tree_new (query12Compare);
    q12 -> organizada = g_tree_new (query11Compare);
    q12 -> mes = m;
    
    return q12;
}



Query11 createQuery11 (int size,int limit)
{
    Query11 q11 = malloc(sizeof(struct query11));
    q11 -> lista = g_tree_new(query11Compare);
    q11 -> size = 0;
    q11 -> limit = limit;
    q11 -> ocup = size;
    q11 -> list = malloc(size*sizeof(char*));
    q11 -> quantidades = calloc(size,sizeof(int));
    q11 -> numeroClientes = calloc(size,sizeof(int));
    int i;
    for(i = 0; i < size; i++)
    {
        q11 -> list[i] = malloc(sizeof(7*sizeof(char)));
    }
        
    return q11;
}



Query12 createQuery12 (int limit)
{
    Query12 q12 = malloc(sizeof(struct query12));
    q12 -> lista = g_tree_new (query12Compare);
    q12 -> organizada = g_tree_new (query11Compare);
    q12 -> limit = limit;
    
    
    return q12;
}


/* funcao auxiliar a passar para o foreach, para responder à Query2*/
void query2Aux (gpointer data,QueryAux qAux)
{
    char* produto = (char*) data;
    if(produto[0] == qAux -> letra)
        qAux -> lista[qAux -> size++] = strdup(produto);
}

/* Query 2 resposta,dado um char, devolve na estrutura QueryAux o codigo dos produtos que começam por esse char e o seu numero*/
void query2 (SGV sgv, char b)
{
    CatalogoProdutos cP = getProdutos(sgv);
    
    GSequence* name = getSequenceProdutos(cP);
    
    int x = g_sequence_get_length(name);
    
    QueryAux qAux = createQueryAux(x,0);
    qAux -> letra = b;
    
    g_sequence_foreach(name,query2Aux,qAux);
    
    int i;
       for (i = 0; i < qAux -> size; i++)
       {
           if((qAux -> tab % 3) != 0)
           {
               printf("Produto %d: %s     ",i,qAux -> lista[i]);
               qAux -> tab++;
           }
           else
           {
               printf("Produto %d: %s\n",i,qAux -> lista[i]);
               qAux -> tab++;
           }
       }
           
       printf("\n");
       printf("Numero de entradas: %d\n",qAux -> size);
    
    for (i = 0; i < qAux -> size; i++)
        free(qAux -> lista[i]);
    free(qAux -> lista);
    free(qAux);
    
}
/* -----Query 3 ----- */
void query3(SGV sgv, char* produto, int month)
{
    FaturacaoGlobal fGlobal = getFaturacao(sgv);
    GTree* name = getTree(fGlobal);
    Query3 q3 = createQuery3(month);
    Faturacao f = (Faturacao) g_tree_lookup(name,produto);
    int i;
    q3 -> vendasN = getValorVendasN(f,(month - 1)) + getValorVendasN(f,(month - 1 + 12)) + getValorVendasN(f,(month - 1 + 24));
    q3 -> vendasP = getValorVendasP(f,(month - 1)) + getValorVendasP(f,(month - 1 + 12)) + getValorVendasP(f,(month - 1 + 24));
    q3 -> faturadoN = getFaturacaoN(f,(month - 1)) + getFaturacaoN(f,(month - 1 + 12)) + getFaturacaoN(f,(month - 1 + 24));
    q3 -> faturadoP = getFaturacaoP(f,(month - 1)) + getFaturacaoP(f,(month - 1 + 12)) + getFaturacaoP(f,(month - 1 + 24));
    
    
    printf("Produto: %s\n",produto);
    printf("Numero vendas normais: %d\n",q3 -> vendasN);
    printf("Numero vendas promocao: %d\n",q3 -> vendasP);
    printf("Numero faturado normais: %f\n",q3 -> faturadoN);
    printf("Numero faturado promocao: %f\n",q3 -> faturadoP);
    
    free(q3);
}

/* -----Query 4 -----
/*funcao auxiliar a passar para o foreach, para responder à Query4*/
gboolean query4Aux (gpointer key, gpointer value, QueryAux qAux)
{
    char* produto = (char*) key;
    Faturacao x = (Faturacao) value;
    if((qAux -> filial) == 0)
    {
        if (getInit(x) == 0)
            qAux -> lista[qAux -> size++] = strdup(produto);
    }
    
    else
    {
        int filialx = qAux -> filial;
        int i;
        int numeroVendas = 0;
        for (i = 12*(filialx - 1); i < 12*filialx; i++)
        {
            numeroVendas += getValorFaturacao(x,i);
        }
        
        if(numeroVendas == 0) qAux -> lista[qAux -> size++] = strdup(produto);
    }
        
    return FALSE;
}

/*Query4
 se filial = 0 -> globalmente
 se filial entre 1 e 3, faz na respetiva filial*/
void query4 (SGV sgv, int filial)
{
    FaturacaoGlobal fGlobal = getFaturacao(sgv);
    
    int x = numeroNodes(fGlobal);
    GTree* name = getTree(fGlobal);
    QueryAux qAux = createQueryAux(x,filial);
    g_tree_foreach(name,query4Aux,qAux);
    int i;
    for (i = 0; i < qAux -> size; i++)
    {
        if((qAux -> tab % 3) != 0)
        {
            printf("Produto %d: %s     ",i,qAux -> lista[i]);
            qAux -> tab++;
        }
        else
        {
            printf("Produto %d: %s\n",i,qAux -> lista[i]);
            qAux -> tab++;
        }
    }
            
    printf("\n");
    printf("Numero de entradas: %d\n",qAux -> size);
    for (i = 0; i < qAux -> size; i++)
        free(qAux -> lista[i]);
    free(qAux -> lista);
    free(qAux);

}
/* -----Query 5 */
void query5Aux (gpointer data,Query5 q5)
{
    printf("q5a 1\n");
    char* cliente = (char*) data;
    printf("q5a 2 0\n");
    int c1 = fezCompras(q5 -> gf1,cliente);
    printf("q5a 2 1\n");
    int c2 = fezCompras(q5 -> gf2,cliente);
    int c3 = fezCompras(q5 -> gf3,cliente);
printf("q5a 3\n");
    if (c1 && c2 && c3)
    {
        strcpy (q5->lista[q5 -> size],cliente);
        q5 -> size +=1;
    }
    printf("q5a 4\n");
}

gboolean query5Aux1 (gpointer key, gpointer value, Query6 q6)
{
    char* nome = (char*) key;
    printf("%s\n",nome);
    
    DadosProdutos dp = (DadosProdutos) value;
    
    GTree* name = getDadosProdutosTree(dp);
    if(g_tree_height(name) != 0)
    {
        
        strcpy(q6 -> lista1[q6 -> size1++],key);
    }
        
    
    return FALSE;
}
void query5(SGV sgv)
{
    CatalogoClientes catalogoC = getClientes(sgv);
    GSequence* clientes = getSequenceClientes(catalogoC);
    int size = g_sequence_get_length(clientes);
    Query6 q6 = createQuery6(size);
    
    GestaoFilial gf1 = getGestaoFilial1(sgv);
    GestaoFilial gf2 = getGestaoFilial2(sgv);
    GestaoFilial gf3 = getGestaoFilial3(sgv);
    
    GTree* tree1 = getTreeClientes(gf1);
    g_tree_foreach(tree1,query5Aux1,q6);
    
    
    int i;
    GTree* tree2 = getTreeClientes(gf2);
    for (i = 0; i < q6 -> size1; i++)
    {
        DadosProdutos dp = g_tree_lookup(tree2,q6->lista1[i]);
        GTree* name = getDadosProdutosTree(dp);
        
        if(g_tree_height(name) != 0)
            strcpy(q6 -> lista2[q6 -> size2++],q6 -> lista1[i]);
    }
    
    GTree* tree3 = getTreeClientes(gf3);
    for (int i = 0; i < q6 -> size2; i++)
    {
        DadosProdutos dp = g_tree_lookup(tree3,q6->lista2[i]);
        GTree* name = getDadosProdutosTree(dp);
        
        if(g_tree_height(name) != 0)
            strcpy(q6 -> lista3[q6 -> size3++],q6 -> lista2[i]);
    }
    
    printf("Clientes que compraram em todas as filias\n");
    for(i = 0; i < q6 -> size3; i++)
        printf("%s  %d\n",q6 -> lista3[i] , i);

    freeQ6(q6);

}

/* -----Query 7 ----- */
gboolean query7Aux (gpointer key, gpointer value, Query7 q7)
{
    Vendas vendas = (Vendas) value;
    int v;
    for (int i = 0; i < 12; ++i)
    {
        v = getNumeroVendasGF( vendas , i);
        q7 -> qVendida[i] += v;
    }
    return FALSE;
}

void query7 (SGV sgv, char* cliente)
{
    
    /* ---FILIAL 1--- */
    Query7 q71 = createQuery7();
    GestaoFilial gf1 = getGestaoFilial1(sgv);
    GTree* treeC1 = getTreeClientes (gf1); 

    DadosProdutos treePinC1s = g_tree_lookup(treeC1,cliente);
    GTree* treePinC1 = getDadosProdutosTree(treePinC1s); 

    g_tree_foreach(treePinC1,query7Aux,q71);
    printf("\nvendas por mes na filial 1 : \n");
    printf("mês:");
    for (int i = 1; i < 13; ++i)
    {
        printf("\t %d",i);
    }
    printf("\n");
    printf("Total:");
    for (int i = 0; i < 12; ++i)
    {
        printf("\t %d",q71->qVendida[i]);
    }    

    /* ---FILIAL 2---*/
    Query7 q72 = createQuery7();
    GestaoFilial gf2 = getGestaoFilial2(sgv);
    GTree*  treeC2 = getTreeClientes (gf2);

    DadosProdutos treePinC2s = g_tree_lookup(treeC2,cliente);
    GTree* treePinC2 = getDadosProdutosTree(treePinC2s);

    g_tree_foreach(treePinC2,query7Aux,q72);
    printf("\nvendas por mes na filial 2 : \n");
    printf("mês:");
    for (int i = 1; i < 13; ++i)
    {
        printf("\t %d",i);
    }
    printf("\n");
    printf("Total:");
    for (int i = 0; i < 12; ++i)
    {
        printf("\t %d",q72->qVendida[i]);
    }

    /* ---FILIAL 3---*/
    Query7 q73 = createQuery7();
    GestaoFilial gf3 = getGestaoFilial3(sgv);
    GTree*  treeC3 = getTreeClientes (gf3);
   
    DadosProdutos treePinC3s = g_tree_lookup(treeC3,cliente);
    GTree* treePinC3 = getDadosProdutosTree(treePinC3s);

    g_tree_foreach(treePinC3,query7Aux,q73);
    printf("\nvendas por mes na filial 3 : \n");
    printf("mês:");
    for (int i = 1; i < 13; ++i)
    {
        printf("\t %d",i);
    }
    printf("\n");
    printf("Total:");
    for (int i = 0; i < 12; ++i)
    {
        printf("\t %d",q73->qVendida[i]);
    }
    printf("\n");

    freequery7(q71);
    freequery7(q72);
    freequery7(q73);

}




gboolean query6Aux1 (gpointer key, gpointer value, Query6 q6)
{
    char* nome = (char*) key;
    
    DadosProdutos dp = (DadosProdutos) value;
    
    GTree* name = getDadosProdutosTree(dp);
    if(g_tree_height(name) == 0)
    {
        
        strcpy(q6 -> lista1[q6 -> size1++],key);
    }
        
    
    return FALSE;
}

void query6(SGV sgv)
{
    CatalogoClientes catalogoC = getClientes(sgv);
    GSequence* clientes = getSequenceClientes(catalogoC);
    int size = g_sequence_get_length(clientes);
    Query6 q6 = createQuery6(size);
    
    GestaoFilial gf1 = getGestaoFilial1(sgv);
    GestaoFilial gf2 = getGestaoFilial2(sgv);
    GestaoFilial gf3 = getGestaoFilial3(sgv);
    
    query4(sgv,0);
    
    GTree* tree1 = getTreeClientes(gf1);
    g_tree_foreach(tree1,query6Aux1,q6);
    
    
    int i;
    GTree* tree2 = getTreeClientes(gf2);
    for (i = 0; i < q6 -> size1; i++)
    {
        DadosProdutos dp = g_tree_lookup(tree2,q6->lista1[i]);
        GTree* name = getDadosProdutosTree(dp);
        
        if(g_tree_height(name) == 0)
            strcpy(q6 -> lista2[q6 -> size2++],q6 -> lista1[i]);
    }
    
    GTree* tree3 = getTreeClientes(gf3);
    for (int i = 0; i < q6 -> size2; i++)
    {
        DadosProdutos dp = g_tree_lookup(tree3,q6->lista2[i]);
        GTree* name = getDadosProdutosTree(dp);
        
        if(g_tree_height(name) == 0)
            strcpy(q6 -> lista3[q6 -> size3++],q6 -> lista2[i]);
    }
    
    printf("Clientes nunca comprados:\n");
    for(i = 0; i < q6 -> size3; i++)
        printf("%s\n",q6 -> lista3[i]);

    free(q6);
}

gboolean query8Aux (gpointer key, gpointer value, Query8 q8)
{
    char* produto = (char*) key;
    Faturacao x = (Faturacao) value;
    if (getInit(x) == 1)
    {
        int i;
        for (i = (q8 -> minMonth - 1); i < (q8 -> maxMonth - 1);i++)
        {
            q8 -> totalVendas += getValorVendas(x,i) + getValorVendas(x,i+12) + getValorVendas(x,i+24);
            q8 -> totalFaturado += getValorFaturacao(x,i) + getValorFaturacao(x,i+12) + getValorVendas(x,i+24);
            
            
        }
    }
    
    return FALSE;
}

void query8 (SGV sgv, int minMonth, int maxMonth)
{
    Query8 q8 = createQuery8(minMonth,maxMonth);
    FaturacaoGlobal fGlobal = getFaturacao(sgv);
    GTree* name = getTree(fGlobal);
    g_tree_foreach(name,query8Aux,q8);
    
    printf("Entre os meses %d e %d\n",minMonth,maxMonth);
    printf("Houve um número total de %li vendas\n",q8 -> totalVendas);
    printf("Houve uma faturação total de %f\n",q8 -> totalFaturado);
    
    free(q8);
}
/* -----Query 9 ----- */
gboolean query9Aux (gpointer key, gpointer value, Query9 q9)
{
    char* clientes = (char*) key;
    printf("%s\n",clientes);
    strcpy(q9 -> lista[q9 -> size++],clientes);
    return FALSE;
}

void query9(SGV sgv,char* produto, int filial)
{
    GestaoFilial gF;
    
    if(filial == 1) gF = getGestaoFilial1(sgv);
    else if(filial == 2) gF = getGestaoFilial2(sgv);
    else gF = getGestaoFilial3(sgv);
    
    GTree* produtos = getTreeProdutos(gF);
    DadosClientes dc = g_tree_lookup(produtos,produto);
    GTree* clientes = getDadosClientesTree(dc);
    int size = g_tree_nnodes(clientes);
    Query9 q9 = createQuery9(size);
    g_tree_foreach(clientes,query9Aux,q9);
    
    printf("Produto: %s\n",produto);
    int i;
    for (i = 0; i < q9 -> size; i++)
        printf("Comprado pelo produto: %s\n",q9 -> lista[i]);
    
    printf("Total de clientes que compraram: %d\n",q9 -> size);
    
    for(i = 0; i < q9 -> size; i++)
        free(q9 -> lista[i]);
    free(q9 -> lista);
    free(q9);
}
/*----query10------ */

void query10Aux1 (gpointer data,Query10 q10)
{
    char* cliente = (char*) data;
    int x = 0;
    g_tree_insert(q10 -> lista,cliente,x);
}

/*
pega na tree que tem associado a um produto o valor que ja se gastou
*/
gboolean query10Aux2 (gpointer key, gpointer value, Query10 q10)
{
    char* nome = (char*) key;
    Vendas v = (Vendas) value;
    
    int x = getQuantidadeMes (v , q10 -> mes);
    int y = g_tree_lookup(q10 -> lista, nome); 
    
    int newValue = x + y;
    g_tree_insert(q10 -> lista,nome,newValue);
    
    return FALSE;
}

gboolean query10Aux3 (gpointer key, gpointer value, Query10 q10)
{
    char* nome = (char*) key;
    int x = (int) value;
    g_tree_insert(q10 -> organizada,x,nome);
    
    return FALSE;
}

gboolean query10Aux4 (gpointer key, gpointer value, Query10 q10)
{
    char* nome = (char*) value;
    
    printf("Produto: %s\n",nome);
    return FALSE;
    
}

void query10 (SGV sgv,char* cliente, int mes)
{
    GestaoFilial gf1 = getGestaoFilial1(sgv);
    GestaoFilial gf2 = getGestaoFilial2(sgv);
    GestaoFilial gf3 = getGestaoFilial3(sgv);
    
    CatalogoClientes catalogoC = getClientes(sgv);
    GSequence* listaClientes = getSequenceClientes(catalogoC);
    
    
    Query10 q10 = createQuery10(mes);
    
    g_sequence_foreach(listaClientes,query10Aux1,q10);
    /*ao fim disto, a tree q12 -> lista1 tem uma entrada para todos os clientes e a eles associados o valor 0*/
    
    GTree* tree1 = getTreeClientes(gf1);
    
    DadosProdutos dp1 = g_tree_lookup(tree1,cliente);
    
    GTree* produtos1 = getDadosProdutosTree(dp1);
    
    g_tree_foreach(produtos1,query10Aux2,q10);
    
    GTree* tree2 = getTreeClientes(gf2);
    DadosProdutos dp2 = g_tree_lookup(tree2,cliente);
    GTree* produtos2 = getDadosProdutosTree(dp2);
    g_tree_foreach(produtos2,query10Aux2,q10);
    
    
    GTree* tree3 = getTreeClientes(gf3);
    DadosProdutos dp3 = g_tree_lookup(tree3,cliente);
    GTree* produtos3 = getDadosProdutosTree(dp3);
    g_tree_foreach(produtos3,query10Aux2,q10);
    
    g_tree_foreach(q10 -> lista,query10Aux3,q10);
    g_tree_foreach(q10 -> organizada,query10Aux4,q10);
    free(q10);
    
}


/*----query11------ */
gboolean query11Aux2 (gpointer key, gpointer value, Query11 q11)
{
    int number = (int) key;
    char* produto = (char*) value;
    if(q11 -> limit > 0)
    {
        strcpy(q11 -> list[q11 -> size],produto);
        q11 -> quantidades[q11 -> size] = number;
        q11 -> size++;
        q11 -> limit--;
        return FALSE;
    }
    return TRUE;
}

gboolean query11Aux (gpointer key, gpointer value, Query11 q11)
{
    Faturacao faturacao = (Faturacao) value;
    char* produto = (char*) key;
    int vendas = 0;
    int i;
    for (i = 0; i < 36; i++)
        vendas += getValorVendas(faturacao,i);
    
    g_tree_insert(q11 -> lista,vendas,produto);
    
    return FALSE;
}

void query11(SGV sgv, int limit)
{
    int x = limit;
    int i;
    FaturacaoGlobal fGlobal = getFaturacao(sgv);
    GTree* faturacao = getTree(fGlobal);
    int tamanho = g_tree_nnodes(faturacao);
    Query11 q11 = createQuery11(tamanho,limit);
    
    g_tree_foreach(faturacao,query11Aux,q11);
    
    g_tree_foreach(q11 -> lista,query11Aux2,q11);
    
    GestaoFilial gF1 = getGestaoFilial1(sgv);
    GestaoFilial gF2 = getGestaoFilial2(sgv);
    GestaoFilial gF3 = getGestaoFilial3(sgv);
    GTree* produtos1 = getTreeProdutos(gF1);
    GTree* produtos2 = getTreeProdutos(gF2);
    GTree* produtos3 = getTreeProdutos(gF3);
    
    for(i = 0; i < q11 -> size; i++)
    {
        DadosClientes dc1 = (g_tree_lookup(produtos1,q11 -> list[i]));
        GTree* clientes1 = getDadosClientesTree(dc1);
        
        DadosClientes dc2 = (g_tree_lookup(produtos2,q11 -> list[i]));
        GTree* clientes2 = getDadosClientesTree(dc2);
        
        DadosClientes dc3 = (g_tree_lookup(produtos3,q11 -> list[i]));
        GTree* clientes3 = getDadosClientesTree(dc3);
        
        int x1 = g_tree_nnodes(clientes1);
        int x2 = g_tree_nnodes(clientes2);
        int x3 = g_tree_nnodes(clientes3);
        
        if (g_tree_height(clientes1) == 0) x1 = 0;
        if (g_tree_height(clientes2) == 0) x2 = 0;
        if (g_tree_height(clientes3) == 0) x3 = 0;
        
        q11 -> numeroClientes[i] = (x1 + x2 +x3);
        
    }
    
    for (i = 0; i < q11 -> size; i++)
    {
        printf("Produto %s     Quantidades: %d\n",q11 -> list[i],q11 -> quantidades[i]);
        printf("Numero Clientes: %d\n",q11 -> numeroClientes[i]);
        
    }
    
    for(i = 0; i < q11 -> ocup; i++)
    {
        free(q11 -> list[i]);
    }
    
    free(q11 -> list);
    free(q11 -> quantidades);
    free(q11 -> numeroClientes);
    free(q11);
}
/* -----query 12---- */
void query12Aux1 (gpointer data,Query12 q12)
{
    char* cliente = (char*) data;
    int x = 0;
    g_tree_insert(q12 -> lista,cliente,x);
}

/*
pega na tree que tem associado a um produto o valor que ja se gastou
*/
gboolean query12Aux2 (gpointer key, gpointer value, Query12 q12)
{
    char* nome = (char*) key;
    Vendas v = (Vendas) value;
    
    int x = getRevenueTotal (v);
    int y = g_tree_lookup(q12 -> lista,nome); 
    
    int newValue = x + y;
    g_tree_insert(q12 -> lista,nome,newValue);
    
    return FALSE;
}

gboolean query12Aux3 (gpointer key, gpointer value, Query12 q12)
{
    char* nome = (char*) key;
    int x = (int) value;
    g_tree_insert(q12 -> organizada,x,nome);
    
    return FALSE;
}

gboolean query12Aux4 (gpointer key, gpointer value, Query12 q12)
{
    char* nome = (char*) value;
    
    if(q12 -> limit > 0)
    {
        printf("Produto: %s\n",nome);
        q12 -> limit--;
        return FALSE;
    }
    return TRUE;
}

void query12 (SGV sgv,char* cliente, int limit)
{
    GestaoFilial gf1 = getGestaoFilial1(sgv);
    GestaoFilial gf2 = getGestaoFilial2(sgv);
    GestaoFilial gf3 = getGestaoFilial3(sgv);
    
    CatalogoClientes catalogoC = getClientes(sgv);
    GSequence* listaClientes = getSequenceClientes(catalogoC);
    
    
    Query12 q12 = createQuery12(limit);
    
    g_sequence_foreach(listaClientes,query12Aux1,q12);
    /*ao fim disto, a tree q12 -> lista1 tem uma entrada para todos os clientes e a eles associados o valor 0*/
    
    GTree* tree1 = getTreeClientes(gf1);
    
    DadosProdutos dp1 = g_tree_lookup(tree1,cliente);
    
    GTree* produtos1 = getDadosProdutosTree(dp1);
    
    g_tree_foreach(produtos1,query12Aux2,q12);
    
    GTree* tree2 = getTreeClientes(gf2);
    DadosProdutos dp2 = g_tree_lookup(tree2,cliente);
    GTree* produtos2 = getDadosProdutosTree(dp2);
    g_tree_foreach(produtos2,query12Aux2,q12);
    
    
    GTree* tree3 = getTreeClientes(gf3);
    DadosProdutos dp3 = g_tree_lookup(tree3,cliente);
    GTree* produtos3 = getDadosProdutosTree(dp3);
    g_tree_foreach(produtos3,query12Aux2,q12);
    
    g_tree_foreach(q12 -> lista,query12Aux3,q12);
    
    int x = limit;
    g_tree_foreach(q12 -> organizada,query12Aux4,q12);

    free(q12);
    
}
    
/* estrutura principal que vai guardar todas as outras estruturas*/
typedef struct sgv
{
    CatalogoProdutos produtosList;
    CatalogoClientes clientesList;
    FaturacaoGlobal fGlobal;
    GestaoFilial gFilial1;
    GestaoFilial gFilial2;
    GestaoFilial gFilial3;
}*SGV;

/* inicia a estrutura principal*/
SGV initSGV()
{
    SGV sgv = malloc(sizeof(struct sgv));
    
    sgv -> produtosList = initCatalogoProdutos();
    sgv -> clientesList = initCatalogoClientes();
    sgv -> fGlobal = createFaturacaoGlobal();
    sgv -> gFilial1 = createGestaoFilial();
    sgv -> gFilial2 = createGestaoFilial();
    sgv -> gFilial3 = createGestaoFilial();
    
    return sgv;
}

/* carregar os ficheiros para a estrutura*/
void loadFiles (char* produtosPath, char* clientesPath, char* vendasPath, SGV sgv)
{
    readFiles(produtosPath,clientesPath,vendasPath,sgv);
}

CatalogoProdutos getProdutos (SGV sgv)
{
    return sgv -> produtosList;
}

/* dado uma esturtura principal, faz get ao catalogo de clientes*/
CatalogoClientes getClientes (SGV sgv)
{
    return sgv -> clientesList;
}

/* dado uma esturtura principal, faz get à estrutura que trata da faturaçao global sem referencia a clientes*/
FaturacaoGlobal getFaturacao (SGV sgv)
{
    return sgv -> fGlobal;
}
/* dado uma esturtura principal, faz get a estrutura que lida com a egstao das filiais*/
GestaoFilial getGestaoFilial1 (SGV sgv)
{
    return sgv -> gFilial1;
}

GestaoFilial getGestaoFilial2 (SGV sgv)
{
    return sgv -> gFilial2;
}
GestaoFilial getGestaoFilial3 (SGV sgv)
{
    return sgv -> gFilial3;
}

/* funcao que liberta a estrutura*/
void freeSGV (SGV sgv)
{
    freeFaturacao(sgv -> fGlobal);
    freeCatalogoProdutos(sgv -> produtosList);
    freeCatalogoClientes(sgv -> clientesList);
    free(sgv);
}
