#include <iostream>
#include "auto_trading_system.h"

void AutoTradingSystem::selectStockBrocker(Driver* input)
{
	drv = input;
}

void AutoTradingSystem::login(std::string stockCode, std::string pass) {
	if (drv == nullptr)
		return;

	drv->loginSystem(stockCode, pass);
}

void AutoTradingSystem::buy(std::string stockCode, int price, int count) {
	if (drv == nullptr)
		return;

	drv->buyStock(stockCode, price, count);
}

void AutoTradingSystem::sell(std::string stockCode, int price, int count) {
	if (drv == nullptr)
		return;

	drv->sellStock(stockCode, price, count);
}

int AutoTradingSystem::getPrice(std::string stockCode) {
	if (drv == nullptr)
		return -1;

	return drv->getMarketPrice(stockCode, 0);
}

bool AutoTradingSystem::sellNiceTiming(std::string stockCode, int count)
{
	int last_price;
	if (isDescendingPrice(stockCode, last_price))
	{
		drv->sellStock(stockCode, last_price, count);
		return true;
	}
	return false;
}

bool AutoTradingSystem::isDescendingPrice(std::string stockCode, int& last_price)
{
	int check_num = 0;
	int price = drv->getMarketPrice(stockCode, 0);
	while (check_num < 2)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(200)); // 200ms ´ë±â
		int cur_price = drv->getMarketPrice(stockCode, 0);
		if ((price - cur_price) > 0)
		{
			check_num++;
			price = cur_price;
		}
		else break;
	}
	
	if (check_num == 2)
	{
		last_price = price;
		return true;
	}
	else return false;
}