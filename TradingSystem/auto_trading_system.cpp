#include <iostream>
#include <exception>
#include "auto_trading_system.h"

void AutoTradingSystem::setStockBroker(Driver* stockBroker)
{
	drv = stockBroker;
}

void AutoTradingSystem::login(std::string stockCode, std::string pass) {
	if (drv == nullptr)
		return;

	drv->loginSystem(stockCode, pass);
}

void AutoTradingSystem::buy(std::string stockCode, int price, int count) {
	if (drv == nullptr)
		return;
	checkBuyPrecondition(price, count);
	drv->buyStock(stockCode, price, count);
}

void AutoTradingSystem::sell(std::string stockCode, int price, int count) {
	if (drv == nullptr)
		return;
	checkSellPrecondition(price, count);
	drv->sellStock(stockCode, price, count);
}

void AutoTradingSystem::checkBuyPrecondition(int price, int count)
{
	checkPositiveBuyingPrice(price);
	checkPositiveCount(count);
}

void AutoTradingSystem::checkSellPrecondition(int price, int count)
{
	checkPositiveSellingPrice(price);
	checkPositiveCount(count);
}

void AutoTradingSystem::checkPositiveBuyingPrice(int price)
{
	if (price <= 0) {
		throw std::exception("매수가는 0보다 커야합니다.\n");
	}
}

void AutoTradingSystem::checkPositiveSellingPrice(int price)
{
	if (price <= 0) {
		throw std::exception("매도가는 0보다 커야합니다.\n");
	}
}

void AutoTradingSystem::checkPositiveCount(int count)
{
	if (count <= 0) {
		throw std::exception("수량은 0보다 커야합니다.\n");
	}
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
