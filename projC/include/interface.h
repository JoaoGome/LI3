#include "sistemaGestaoVendas.h"

SGV init();
void destroySGV(SGV sgv);
void loadSGVFromFiles(SGV sgv, char* clientesFilePath, char* productsFilePath, char* salesFilePath);
int getCurrentFilesInfo(SGV sgv);
void getProductsStartedByLetter(SGV sgv, char letter);
void getProductSalesAndProfit(SGV sgv, char* productID, int month);
void getProductsNeverBought(SGV sgv, int branchID);
void getClientesOfAllBranches(SGV sgv);
void getClientesAndProductsNeverBoughtCount(SGV sgv);
void getProductsBoughtByClient(SGV sgv, char* clientID);
void getSalesAndProfit(SGV sgv,int minMonth,int maxMonth);
void getProductBuyers (SGV sgv, char* productID, int branch);
void getClientFavoriteProducts (SGV sgv, char* clientID, int month);
void getTopSelledProducts (SGV sgv, int limit);
void getClientTopProfitProducts (SGV sgv, char* clientID, int limit);

