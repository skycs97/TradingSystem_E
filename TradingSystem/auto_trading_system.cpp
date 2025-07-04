#include <iostream>
#include <exception>
#include "auto_trading_system.h"

void AutoTradingSystem::setStockBroker(Driver* stockBroker)
{
	this->stockBroker = stockBroker;
}

void AutoTradingSystem::login(std::string stockCode, std::string pass) {
	if (stockBroker == nullptr)
		return;

	stockBroker->loginSystem(stockCode, pass);
}

void AutoTradingSystem::buy(std::string stockCode, int price, int count) {
	if (stockBroker == nullptr)
		return;
	checkBuyPrecondition(price, count);
	stockBroker->buyStock(stockCode, price, count);
}

void AutoTradingSystem::sell(std::string stockCode, int price, int count) {
	if (stockBroker == nullptr)
		return;
	checkSellPrecondition(price, count);
	stockBroker->sellStock(stockCode, price, count);
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
		throw std::exception("�ż����� 0���� Ŀ���մϴ�.\n");
	}
}

void AutoTradingSystem::checkPositiveSellingPrice(int price)
{
	if (price <= 0) {
		throw std::exception("�ŵ����� 0���� Ŀ���մϴ�.\n");
	}
}

void AutoTradingSystem::checkPositiveCount(int count)
{
	if (count <= 0) {
		throw std::exception("������ 0���� Ŀ���մϴ�.\n");
	}
}

int AutoTradingSystem::getPrice(std::string stockCode) {
	if (stockBroker == nullptr)
		return -1;

	return stockBroker->getMarketPrice(stockCode, 0);
}

bool AutoTradingSystem::buyNiceTiming(std::string stockCode, int price)
{
	int check_price_count = 0;
	int previous_price = 0;
	int current_price = 0;

	while (check_price_count < GET_MARKET_PRICE_COUNT)
	{
		current_price = stockBroker->getMarketPrice(stockCode, SLEEP_MS);
		if (current_price < previous_price) {
			return false;
		}

		check_price_count++;
		previous_price = current_price;
	}

	int count = price / current_price;

	stockBroker->buyStock(stockCode, current_price, count);

	return true;
}
