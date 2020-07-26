#ifndef FATURACAOGLOBAL_H
#define FATURACAOGLOBAL_H
#include <gmodule.h>

typedef struct faturacao* Faturacao;
typedef struct faturacaoGlobal* FaturacaoGlobal;

FaturacaoGlobal createFaturacaoGlobal ();
Faturacao createFaturacao ();
GTree* getTree(FaturacaoGlobal fGlobal);
void addProdutoFaturacao (FaturacaoGlobal fGlobal, Faturacao f, char* produto);
void addVendaFaturacao (FaturacaoGlobal fGlobal, int month, int filial, char* mode, char* produto, float price, int quantidade);
void freeFaturacao (FaturacaoGlobal f);
float getValorFaturacao (Faturacao f, int position);
int getValorVendas (Faturacao f,int position);
int getValorVendasP (Faturacao f, int position);
int getValorVendasN (Faturacao f, int position);
float getFaturacaoP (Faturacao f, int position);
float getFaturacaoN (Faturacao f, int position);
int getInit (Faturacao f);
#endif
