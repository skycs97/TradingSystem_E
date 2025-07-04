#pragma once
#include "driver.h"

class AutoTradingSystem {
public:
	void selectStockBrocker(Driver* input);
	void login(std::string stockCode, std::string pass);
	void buy(std::string stockCode, int price, int count);
	void sell(std::string stockCode, int price, int count);
	int getPrice(std::string stockCode);
private:
	Driver* drv = nullptr;
};