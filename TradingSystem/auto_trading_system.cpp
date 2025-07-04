#include "auto_trading_system.h"


void AutoTradingSystem::loginSystem(string id, string pw)
{
	driver->login(id, pw);
}

