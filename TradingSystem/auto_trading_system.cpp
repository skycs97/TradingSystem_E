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

	return 0;
}
