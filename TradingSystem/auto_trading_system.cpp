#include "auto_trading_system.h"

int AutoTradingSystem::getPrice(string stockName)
{
	return selectedDriver->getMarketPrice(stockName, 0);
}

void AutoTradingSystem::addDriver(string driverName, Driver* driver)
{
	//getPrice 테스트에서 돌아가는 정도로만 만들었습니다.
	selectedDriver = driver;
}

void AutoTradingSystem::selectDriver(string driverName)
{
	//getPrice 테스트에서 돌아가는 정도로만 만들었습니다.
	// do nothing.
}
