#include "driver.h"
#include "nemo_api.cpp"

using std::string;

class nemoDriver : public Driver {
public:
	void loginSystem(string stockCode, string pass) override
	{
		api.certification(stockCode, pass);
	}
	void buyStock(string stockCode, int price, int count) override
	{
		api.purchasingStock(stockCode, price, count);
	}
	void sellStock(string stockCode, int price, int count) override
	{
		api.sellingStock(stockCode, price, count);
	}
	int getMarketPrice(string stockCode, int after) override
	{
		api.getMarketPrice(stockCode, after);
		return 0;
	}
private:
	NemoAPI api;
};
