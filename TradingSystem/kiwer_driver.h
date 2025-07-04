#pragma once
#include "driver.h"
#include "kiwer_api.cpp"
#include <iostream>

using std::string;

class KiwerDriver : public Driver {
public:
	void loginSystem(string stockCode, string pass) override;
	void buyStock(string stockCode, int price, int count) override;
	void sellStock(string stockCode, int price, int count) override;
	int getMarketPrice(string stockCode, int after) override;
protected:
	virtual int getMarketPriceFromKiwerAPI(string stockCode) {
		return api.currentPrice(stockCode);
	}
	virtual void sleep(int ms);
private:
	KiwerAPI api;
};