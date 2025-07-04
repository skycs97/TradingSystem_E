#pragma once
#include "driver.h"
#include "nemo_api.cpp"
#include <iostream>

using std::string;

class NemoDriver : public Driver {
public:
	void loginSystem(string stockCode, string pass) override;
	void buyStock(string stockCode, int price, int count) override;
	void sellStock(string stockCode, int price, int count) override;
	int getMarketPrice(string stockCode, int after) override;
protected:
	virtual int getMarketPriceFromNemoAPI(string stockCode, int ms) {
		return api.getMarketPrice(stockCode, ms);
	}
private:
	NemoAPI api;
};
