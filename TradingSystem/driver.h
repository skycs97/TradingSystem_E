#pragma once

class Driver
{
public:
	virtual void loginSystem(string, string) = 0;
	virtual void buyStock(string, int, int) = 0;
	virtual void sellStock(string, int, int) = 0;
	virtual int getMarketPrice(string, int) = 0;
};