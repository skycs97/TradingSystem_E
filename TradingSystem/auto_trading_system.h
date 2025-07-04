#pragma once
#include "driver.h"
#include <chrono>
#include <thread>

class AutoTradingSystem {
public:
	void selectStockBrocker(Driver* input);
	void login(std::string stockCode, std::string pass);
	void buy(std::string stockCode, int price, int count);
	void sell(std::string stockCode, int price, int count);
	int getPrice(std::string stockCode);
	bool sellNiceTiming(std::string stockCode, int count);
  
private:
	bool isDescendingPrice(std::string stockCode, int& last_price);

	Driver* drv = nullptr;
};