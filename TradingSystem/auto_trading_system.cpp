#include "auto_trading_system.h"

void AutoTradingSystem::addDriver(string name, Driver* driver)
{
	if (name == "nemo") nemo_driver = driver;
	else if (name == "kiwer") kiwer_driver = driver;
}

void AutoTradingSystem::selectDriver(string name)
{
	if (name == "nemo") cur_driver = nemo_driver;
	else if (name == "kiwer") cur_driver = kiwer_driver;
}

string AutoTradingSystem::getCurrentDriverName()
{
	assert(cur_driver != nullptr);

	if (cur_driver == nemo_driver) return "nemo";
	else if (cur_driver == kiwer_driver) return "kiwer";

	throw std::exception();
}