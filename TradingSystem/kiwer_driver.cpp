#include "kiwer_driver.h"
#include <windows.h>

using std::string;

void KiwerDriver::loginSystem(string stockCode, string pass)
{
	api.login(stockCode, pass);
}
void KiwerDriver::buyStock(string stockCode, int price, int count)
{
	api.buy(stockCode, count, price);
}
void KiwerDriver::sellStock(string stockCode, int price, int count)
{
	api.sell(stockCode, count, price);
}
int KiwerDriver::getMarketPrice(string stockCode, int after)
{
	Sleep(after);
	return api.currentPrice(stockCode);
}
