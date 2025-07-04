#pragma once
#include "driver.h"

class AutoTradingSystem {
public:
	void selectStockBrocker(Driver* input);
	void login(std::string stockCode, std::string pass);
	void buy(std::string stockCode, int price, int count);
	void sell(std::string stockCode, int price, int count);
	int getPrice(std::string stockCode);
	bool buyNiceTiming(std::string stockCode, int price);
  
private:
	Driver* drv = nullptr;
	
	static const int GET_MARKET_PRICE_COUNT = 3;
	static const int SLEEP_MS = 200;

	void checkBuyPrecondition(int price, int count);
	void checkSellPrecondition(int price, int count);
	void checkPositiveBuyingPrice(int price);
	void checkPositiveSellingPrice(int price);
	void checkPositiveCount(int count);
};