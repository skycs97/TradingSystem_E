#pragma once
#include "driver.h"
#include "nemo_api.cpp"
#include <iostream>

using std::string;

class nemoDriver : public Driver {
public:
	void loginSystem(string stockCode, string pass) override;
	void buyStock(string stockCode, int price, int count) override;
	void sellStock(string stockCode, int price, int count) override;
	int getMarketPrice(string stockCode, int after) override;

private:
	NemoAPI api;
};
