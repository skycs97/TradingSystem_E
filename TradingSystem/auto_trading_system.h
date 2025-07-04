#pragma once
#include "driver.h"
#include <stdexcept>
#include <string>
#include <iostream>

class DriverIsNullPtrException : public std::exception {
public:
	DriverIsNullPtrException(const std::string& msg) : message(msg) {};

	const char* what() const noexcept override {
		return message.c_str();
	}

private:
	std::string message;
};

class AutoTradingSystem {
public:
	enum PricePatternType {
		PricePatternType_Ascending = 0,
		PricePatternType_Descending
	};

	void selectStockBrocker(Driver* input);
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
	static const int INVALID_PRICE = 0xFFFFFFFF;

	bool isDriverNull();
	void checkBuyPrecondition(int price, int count);
	void checkSellPrecondition(int price, int count);
	void checkPositiveBuyingPrice(int price);
	void checkPositiveSellingPrice(int price);
	void checkPositiveCount(int count);

	unsigned int getNicePrice(std::string stockCode, AutoTradingSystem::PricePatternType patternType);

	bool isPriceOnPattern(unsigned int prev_price, unsigned int cur_price, AutoTradingSystem::PricePatternType patternType);
};