#ifndef CATALOGOCLIENTES_H
#define CATALOGOCLIENTES_H
#include <gmodule.h>

typedef struct catalogoClientes* CatalogoClientes;


CatalogoClientes initCatalogoClientes ();
void sortArrayClientes (CatalogoClientes l);
GSequence* getSequenceClientes (CatalogoClientes l);
void addClient (CatalogoClientes l, char* client);
void freeCatalogoClientes (CatalogoClientes l);
int checkExisteCliente (CatalogoClientes l, char* client);
void printCatalogoClientes (CatalogoClientes l);
int numeroClientes (CatalogoClientes l);
void printAuxClientes (char* cliente);
void freeAuxClientes(char* nome);

#endif
