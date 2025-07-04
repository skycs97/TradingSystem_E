#include "kiwer_driver.h"
#include <windows.h>

using std::string;

void kiwerDriver::loginSystem(string stockCode, string pass)
{
	api.login(stockCode, pass);
}
void kiwerDriver::buyStock(string stockCode, int price, int count)
{
	api.buy(stockCode, price, count);
}
void kiwerDriver::sellStock(string stockCode, int price, int count)
{
	api.sell(stockCode, price, count);
}
int kiwerDriver::getMarketPrice(string stockCode, int after)
{
	Sleep(after);
	return api.currentPrice(stockCode);
}
