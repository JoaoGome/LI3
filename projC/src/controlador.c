#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/catalogoProdutos.h"
#include "../include/catalogoClientes.h"
#include "../include/faturacaoGlobal.h"
#include "../include/sistemaGestaoVendas.h"
#include "../include/reader.h"
#include "../include/gestaoFilial.h"
#include "../include/interface.h"


/* ----------------------QUERY1------------------------*/

void loadSGVFromFiles(SGV sgv, char* clientesFilePath, char* productsFilePath, char* salesFilePath)
{
    loadFiles(productsFilePath,clientesFilePath,salesFilePath,sgv);
}

/* ----------------------QUERY2 ------------------------*/

void getProductsStartedByLetter(SGV sgv, char letter)
{
    query2(sgv,letter);
}

/* -----------------------QUERY3-----------------------*/

void getProductSalesAndProfit(SGV sgv, char* productID, int month)
{
    query3(sgv,productID,month);
}

/* -----------------------QUERY4------------------------*/


void getProductsNeverBought(SGV sgv, int branchID)
{
    query4(sgv,branchID);
}

/* ----------------------QUERY5------------------------*/
void getClientesOfAllBranches(SGV sgv)
{
    query5(sgv);
}

/* ----------------------QUERY6--------------------------*/

void getClientesAndProductsNeverBoughtCount(SGV sgv)
{
    query6(sgv);
}

/* ----------------------QUERY7--------------------------*/

void getProductsBoughtByClient (SGV sgv, char* clientID)
{
    query7(sgv,clientID);
}

/* -------------------------QUERY8------------------*/
void getSalesAndProfit(SGV sgv,int minMonth,int maxMonth)
{
    query8(sgv,minMonth,maxMonth);
}

/*-----------------------------QUERY9----------------*/
void getProductBuyers (SGV sgv, char* productID, int branch)
{
    query9(sgv,productID,branch);
}

/*------------------------------QUERY10----------------*/

void getClientFavoriteProducts (SGV sgv, char* clientID, int month)
{
    query10(sgv,clientID,month);
}

/* -----------------------------QUERY11---------------*/

void getTopSelledProducts (SGV sgv, int limit)
{
    query11(sgv,limit);
}

/*------------------------------QUERY12----------------*/

void getClientTopProfitProducts (SGV sgv, char* clientID, int limit)
{
    query12(sgv,clientID,limit);
}