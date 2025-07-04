#pragma once
#include <string>
#include <map>
#include "driver.h"
using std::string;
using std::map;
class AutoTradingSystem {
public:
	int getPrice(string stockName);
	void addDriver(string driverName, Driver* driver);
	void selectDriver(string driverName);
private:
	
	Driver* selectedDriver;
};