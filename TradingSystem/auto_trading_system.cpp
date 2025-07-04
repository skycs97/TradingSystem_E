#include <iostream>
#include <exception>
#include "auto_trading_system.h"

void AutoTradingSystem::selectStockBrocker(Driver* input)
{
	if (input == nullptr)
		throw DriverIsNullPtrException("[AutoTradingSystem] driver is null");
	drv = input;
}

void AutoTradingSystem::login(std::string stockCode, std::string pass) {
	if (isDriverNull())
		throw DriverIsNullPtrException("[AutoTradingSystem] can't login");
	drv->loginSystem(stockCode, pass);
}

void AutoTradingSystem::buy(std::string stockCode, int price, int count) {

	if (isDriverNull())
		throw DriverIsNullPtrException("[AutoTradingSystem] can't buy stock");
	checkBuyPrecondition(price, count);
	drv->buyStock(stockCode, price, count);
}

void AutoTradingSystem::sell(std::string stockCode, int price, int count) {
	if (isDriverNull())
		throw DriverIsNullPtrException("[AutoTradingSystem] can't sell stock");;
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
	if (isDriverNull())
		throw DriverIsNullPtrException("[AutoTradingSystem] can't get price");
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

bool AutoTradingSystem::sellNiceTiming(std::string stockCode, int count)
{
	unsigned int last_price;
	if (isDescendingPrice(stockCode, last_price))
	{
		drv->sellStock(stockCode, static_cast<int>(last_price), count);
		return true;
	}
	return false;
}

bool AutoTradingSystem::isDescendingPrice(std::string stockCode, unsigned int& last_price)
{
	int check_num = 0;
	unsigned int prev_price = UINT32_MAX_VALUE;
	while (check_num < GET_MARKET_PRICE_COUNT)
	{
		unsigned int cur_price = drv->getMarketPrice(stockCode, SLEEP_MS);
		if (prev_price > cur_price)
		{
			check_num++;
			prev_price = cur_price;
		}
		else break;
	}

	if (check_num == GET_MARKET_PRICE_COUNT)
	{
		last_price = prev_price;
		return true;
	}
	else return false;
}

bool AutoTradingSystem::isDriverNull() {

	return (drv == nullptr);
}