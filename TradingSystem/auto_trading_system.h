#pragma once
#include "driver.h"

class AutoTradingSystem {
public:
	void setStockBroker(Driver* stockBroker);
	void login(std::string stockCode, std::string pass);
	void buy(std::string stockCode, int price, int count);
	void sell(std::string stockCode, int price, int count);
	int getPrice(std::string stockCode);
	bool sellNiceTiming(std::string stockCode, int count);
	bool buyNiceTiming(std::string stockCode, int price);
  
private:
	Driver* drv = nullptr;

	static const int GET_MARKET_PRICE_COUNT = 3;
	static const int SLEEP_MS = 200;
	static const int UINT32_MAX_VALUE = 0xFFFFFFFF;

	void checkBuyPrecondition(int price, int count);
	void checkSellPrecondition(int price, int count);
	void checkPositiveBuyingPrice(int price);
	void checkPositiveSellingPrice(int price);
	void checkPositiveCount(int count);
	bool isDescendingPrice(std::string stockCode, unsigned int& last_price);
};