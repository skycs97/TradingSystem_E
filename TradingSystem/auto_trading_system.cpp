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

bool AutoTradingSystem::buyNiceTiming(std::string stockCode, int price)
{
	int check_price_count = 0;
	int previous_price = 0;
	int current_price = 0;

	while (check_price_count < GET_MARKET_PRICE_COUNT)
	{
		current_price = drv->getMarketPrice(stockCode, SLEEP_MS);
		if (current_price < previous_price) {
			return false;
		}

		check_price_count++;
		previous_price = current_price;
	}

	int count = price / current_price;

	drv->buyStock(stockCode, current_price, count);

	return true;
}
