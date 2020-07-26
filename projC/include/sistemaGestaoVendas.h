#ifndef SISTEMAGESTAOVENDAS_H
#define SISTEMAGESTAOVENDAS_H

#include "../include/catalogoClientes.h"
#include "../include/catalogoProdutos.h"
#include "../include/faturacaoGlobal.h"
#include "../include/sistemaGestaoVendas.h"
#include "../include/gestaoFilial.h"

typedef struct queryAux* QueryAux;
typedef struct query3* Query3;
typedef struct query7s* Query7;
typedef struct query6* Query6;
typedef struct query8* Query8;
typedef struct query9* Query9;
typedef struct sgv* SGV;
typedef struct query5* Query5;
typedef struct query10* Query10;
typedef struct query11* Query11;
typedef struct query12* Query12;


Query3 createQuery3 ();
QueryAux createQueryAux (int x, int filia);
void printQueryAux(QueryAux qAux);
void freeQueryAux (QueryAux qAux);
void query2Aux (gpointer data,QueryAux qAux);
void query2 (SGV sgv, char b);
void query3(SGV sgv, char* produto, int month);
gboolean query4Aux (gpointer key, gpointer value, QueryAux qAux);
void query4 (SGV sgv, int filial);
gboolean query8Aux (gpointer key, gpointer value, Query8 q8);
void query5Aux (gpointer data,Query5 q5);
void query5 (SGV sgv);
Query5 createQuery5 (int n, GestaoFilial g1 ,GestaoFilial g2, GestaoFilial g3);
gboolean query7Aux (gpointer key, gpointer value, Query7 q7);
void query7 (SGV sgv, char* cliente);
gboolean query6Aux1 (gpointer key, gpointer value, Query6 q6);
void query6(SGV sgv);
Query12 createQuery12 (int limit);
Query10 createQuery10 (int m);
void query8 (SGV sgv, int minMonth, int maxMonth);
Query9 createQuery9 (int size);
gboolean query9Aux (gpointer key, gpointer value, Query9 q9);
void query9(SGV sgv,char* produto, int filial);

void query10Aux1 (gpointer data,Query10 q10);
gboolean query10Aux2 (gpointer key, gpointer value, Query10 q10);
gboolean query10Aux3 (gpointer key, gpointer value, Query10 q10);
gboolean query10Aux4 (gpointer key, gpointer value, Query10 q10);
void query10 (SGV sgv,char* cliente, int mes);

void query12Aux1 (gpointer data,Query12 q12);
gboolean query12Aux2 (gpointer key, gpointer value, Query12 q12);
gboolean query12Aux3 (gpointer key, gpointer value, Query12 q12);
gboolean query12Aux4 (gpointer key, gpointer value, Query12 q12);
void query12 (SGV sgv,char* cliente, int limit);

SGV initSGV();
void loadFiles (char* produtosPath, char* clientesPath, char* vendasPath, SGV sgv);
CatalogoProdutos getProdutos (SGV sgv);
CatalogoClientes getClientes (SGV sgv);
FaturacaoGlobal getFaturacao (SGV sgv);
GestaoFilial getGestaoFilial1 (SGV sgv);
GestaoFilial getGestaoFilial2 (SGV sgv);
GestaoFilial getGestaoFilial3 (SGV sgv);
void freeSGV (SGV sgv);

#endif
