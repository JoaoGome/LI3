#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/parser.h"
#include "../include/catalogoClientes.h"
#include "../include/catalogoProdutos.h"
#include "../include/faturacaoGlobal.h"
#include "../include/gestaoFilial.h"
#include "../include/reader.h"
#include "../include/sistemaGestaoVendas.h"
#include <time.h>



int main(int argc, char const* argv[])
{
    SGV sgv;
    int flag=1;
    while (flag!=0)
    {
        printf("Que query quer fazer?:\n");
        printf("1  :\t loadSGVFromFiles \n");
        printf("2  :\t getProductsStartedByLetter \n");
        printf("3  :\t getProductSalesAndProfit \n");
        printf("4  :\t getProductsNeverBought \n");
        printf("5  :\t getClientesOfAllBranches \n");
        printf("6  :\t getClientesAndProductsNeverBoughtCount \n");
        printf("7  :\t getProductsBoughtByClient \n");
        printf("8  :\t getSalesAndProfit \n");
        printf("9  :\t getProductBuyers \n");
        printf("10 :\t getClientFavoriteProducts \n");
        printf("11 :\t getTopSelledProducts \n");
        printf("12 :\t getClientTopProfitProducts \n");
        printf("0  :\t exit \n");

        int casei;
        int q = 0; // int 
        int q2 = 0; // int 
        char c; // char
        char s[128]; // string
        char s2[128];
        char s3[128];
        scanf("%d", &casei);
        switch (casei)
        {

            case 1:
            {
                printf("Introduza o path para os clientes\n");
                scanf("%s",s);
                printf("Introduza o path para os produtos\n");
                scanf("%s",s2);
                printf("Introduza o path para as vendas\n");
                scanf("%s",s3);
                sgv = initSGV();
                loadSGVFromFiles(sgv,s,s2,s3);
                break;
            }
            case 2:
            {
                printf("Introduza uma letra maiuscula\n");
                scanf("%s",&c);
                getProductsStartedByLetter(sgv,c);
                break;
            }
            case 3:
            {   
                printf("Introduza o productID\n");
                scanf("%s",&s);
                printf("Introduza o mes\n");
                scanf("%d",&q);
                getProductSalesAndProfit(sgv,s,q);
                break;
            } 
            case 4:
            {
                printf("Introduza o branchID\n");
                scanf("%d",&q);
                getProductsNeverBought(sgv, q);
                break;
            }
            case 5:
            {
                getClientesOfAllBranches(sgv);
                break;
            }
            case 6:
            {
                getClientesAndProductsNeverBoughtCount(sgv);
                break;
            }
            case 7:
            {
                printf("Introduza o clientID \n");
                scanf("%s",&s);
                getProductsBoughtByClient(sgv,s);
                break;
            }
            case 8:
            {
                printf("Introduza o primeiro mes\n");
                scanf("%d",&q);
                printf("Introduza o ultimo mes\n");
                scanf("%d",&q2);
                getSalesAndProfit(sgv,q,q2);
                break;
            }
            case 9:
            {
                printf("Introduza o productID\n");
                scanf("%s",&s);
                printf("Introduza o branchID\n");
                scanf("%d",&q);
                getProductBuyers(sgv,s,q);
                break;
            }
            case 10:
            {
                printf("Introduza o clientID\n");
                scanf("%s",&s);
                printf("Introduza o mes\n");
                scanf("%d",&q);
                getClientFavoriteProducts(sgv,s,q);
                break;
            }
            case 11:
            {
                printf("Introduza o mes\n");
                scanf("%d",&q);
                getTopSelledProducts(sgv,q);
                break;
            }
            case 12:
            {
                printf("Introduza o clientID\n");
                scanf("%s",&s);
                printf("Introduza quantos produtos quer ver\n");
                scanf("%d",&q);
                clock_t t; 
                t = clock();
                getClientTopProfitProducts(sgv,s,q);
                t = clock() - t;
                double time_taken = ((double)t)/CLOCKS_PER_SEC;
                printf("q12 took %f seconds to execute \n", time_taken);

                break;
            }
            case 0:
            {
                flag=0;
                break;
            }
        }// fim do switch

        if (flag!=0)
        {
            printf("Pretende fazer mais alguma coisa?\n");
            printf("0  :exit\n");
            printf("1  :continuar\n");
            scanf("%d",&q);
            flag=q; 
        }
    }

    freeSGV(sgv);    
    return 0;
}
