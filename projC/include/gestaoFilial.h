#ifndef GESTAOFILIAL_H
#define GESTAOFILIAL_H

typedef struct vendas* Vendas;
typedef struct gestaoFilial* GestaoFilial;
typedef struct dadosClientes* DadosClientes;
typedef struct dadosProdutos* DadosProdutos;

GestaoFilial createGestaoFilial ();
DadosClientes createDadosClientes ();
DadosProdutos createDadosProdutos ();
Vendas createVendas ();
GTree* getTreeProdutos (GestaoFilial gF);
GTree* getDadosClientesTree (DadosClientes dC);
GTree* getTreeClientes (GestaoFilial gF);
GTree* getDadosProdutosTree (DadosProdutos dP);
int getRevenueTotal (Vendas v);
int getNumeroVendasGF(Vendas v, int mes);
int fezCompras(char* cliente, GestaoFilial gt);

void addProdutoGestaoFilial (GestaoFilial gFilial , DadosClientes dadosClientes , char* produto);
void addClienteinPGF (DadosClientes dadosClientes , char* cliente, Vendas venda);
void addClienteGestaoFilial (GestaoFilial gFilial, DadosProdutos dadosProdutos , char* cliente);
GTree* getDadosprodutosTree (DadosProdutos dP);
void addProdutoinCGF (DadosProdutos dadosProdutos , char* produto, Vendas venda);
void addVendaFilial (GestaoFilial gestaoFilial, char* produto , double preco ,int quantidade , char modo , char* cliente, int mes);
void freeGestaoFilial (GestaoFilial gf);
void printFilial(GestaoFilial gf);
GTree* getTreeClientes (GestaoFilial gF);
int numeroClientesinP(GestaoFilial gf, char* produto);

#endif
