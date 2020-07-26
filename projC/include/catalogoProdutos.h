#ifndef CATALOGOPRODUTOS_H
#define CATALOGOPRODUTOS_H
#include <gmodule.h>
typedef struct catalogoProdutos* CatalogoProdutos;


CatalogoProdutos initCatalogoProdutos ();
void freeAu(char* nome);
void sortArrayProdutos (CatalogoProdutos l);
GSequence* getSequenceProdutos (CatalogoProdutos l);
void addProduto (CatalogoProdutos l, char* produto);
void freeCatalogoProdutos (CatalogoProdutos l);
int checkExisteProduto (CatalogoProdutos l, char* produto);
void printCatalogoProdutos (CatalogoProdutos l);
int numeroProdutos (CatalogoProdutos l);
void printAu (char* produto);

#endif
