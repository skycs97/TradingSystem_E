#include "auto_trading_system.h"

int AutoTradingSystem::getPrice(string stockName)
{
	return selectedDriver->getMarketPrice(stockName, 0);
}

void AutoTradingSystem::addDriver(string driverName, Driver* driver)
{
	//getPrice �׽�Ʈ���� ���ư��� �����θ� ��������ϴ�.
	selectedDriver = driver;
}

void AutoTradingSystem::selectDriver(string driverName)
{
	//getPrice �׽�Ʈ���� ���ư��� �����θ� ��������ϴ�.
	// do nothing.
}
