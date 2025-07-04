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
	if (drv == nullptr)
		return -1;

	return drv->getMarketPrice(stockCode, 0);
}
