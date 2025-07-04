#include "nemo_driver.h"

using std::string;

void NemoDriver::loginSystem(string stockCode, string pass)
{
	api.certification(stockCode, pass);
}
void NemoDriver::buyStock(string stockCode, int price, int count)
{
	api.purchasingStock(stockCode, price, count);
}
void NemoDriver::sellStock(string stockCode, int price, int count)
{
	api.sellingStock(stockCode, price, count);
}
int NemoDriver::getMarketPrice(string stockCode, int after)
{
	return api.getMarketPrice(stockCode, after);
}

