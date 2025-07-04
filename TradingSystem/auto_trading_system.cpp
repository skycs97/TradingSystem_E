#include <iostream>
#include <exception>
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
	unsigned int last_price = getNicePrice(stockCode, AutoTradingSystem::PricePatternType_Ascending);
	if (last_price == INVALID_PRICE) return false;

	int count = price / last_price;
	drv->buyStock(stockCode, last_price, count);

	return true;
}

bool AutoTradingSystem::sellNiceTiming(std::string stockCode, int count)
{
	unsigned int last_price = getNicePrice(stockCode, AutoTradingSystem::PricePatternType_Descending);
	if (last_price == INVALID_PRICE) return false;

	drv->sellStock(stockCode, static_cast<int>(last_price), count);
	return true;
	
}

unsigned int AutoTradingSystem::getNicePrice(std::string stockCode, AutoTradingSystem::PricePatternType patternType)
{
	unsigned int cur_price = INVALID_PRICE;
	unsigned int prev_price = drv->getMarketPrice(stockCode, SLEEP_MS);
	int check_count = 1;

	while (check_count < GET_MARKET_PRICE_COUNT)
	{
		cur_price = drv->getMarketPrice(stockCode, SLEEP_MS);
		if (isPriceOnPattern(prev_price, cur_price, patternType) == false) {
			return INVALID_PRICE;
		}
		
		check_count++;
		prev_price = cur_price;
	}

	return cur_price;
}

bool AutoTradingSystem::isPriceOnPattern(unsigned int prev_price, unsigned int cur_price, AutoTradingSystem::PricePatternType patternType)
{
	if (patternType == AutoTradingSystem::PricePatternType_Ascending) { return (prev_price < cur_price); }
	else { return  (prev_price > cur_price); }
}
