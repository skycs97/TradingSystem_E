#include "driver.h"
#include "kiwer.cpp"
#include <windows.h>

using std::string;

class kiwerDriver : public Driver {
public:
	void loginSystem(string stockCode, string pass) override
	{
		api.login(stockCode, pass);
	}
	void buyStock(string stockCode, int price, int count) override
	{
		api.buy(stockCode, price, count);
	}
	void sellStock(string stockCode, int price, int count) override
	{
		api.sell(stockCode, price, count);
	}
	int getMarketPrice(string stockCode, int after) override
	{
		Sleep(after);
		return api.currentPrice(stockCode);
	}
private:
	KiwerAPI api;
};