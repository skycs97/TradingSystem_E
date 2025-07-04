#include "nemo_driver.h"

using std::string;

void nemoDriver::loginSystem(string stockCode, string pass)
{
	api.certification(stockCode, pass);
}
void nemoDriver::buyStock(string stockCode, int price, int count)
{
	api.purchasingStock(stockCode, price, count);
}
void nemoDriver::sellStock(string stockCode, int price, int count)
{
	api.sellingStock(stockCode, price, count);
}
int nemoDriver::getMarketPrice(string stockCode, int after)
{
	api.getMarketPrice(stockCode, after);
	return 0;
}

