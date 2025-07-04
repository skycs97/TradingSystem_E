#pragma once
#include "driver.h"
#include <string>
#include <stdexcept>
#include <cassert>

using std::string;

class AutoTradingSystem {
public:
	void addDriver(string name, Driver* driver);

	void selectDriver(string name);

	string getCurrentDriverName();

private:
	Driver* nemo_driver{ nullptr };
	Driver* kiwer_driver{ nullptr };
	Driver* cur_driver{ nullptr };
};