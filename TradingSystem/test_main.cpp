#include <gmock/gmock.h>
#include <string>
#include "kiwer.cpp""
#include "nemo_api.cpp"
#include "driver.h"
#include "auto_trading_system.h"

using std::string;
using namespace testing;

class MockDriver : public Driver {
public:
	MOCK_METHOD(void, loginSystem, (string, string), (override));
	MOCK_METHOD(void, buyStock, (string, int, int), (override));
	MOCK_METHOD(void, sellStock, (string, int, int), (override));
	MOCK_METHOD(int, getMarketPrice, (string, int), (override));
};

TEST(TradingSystem, SelectNemoDriver) {
	MockDriver nemoDriver;
	MockDriver kiwerDriver;
	AutoTradingSystem system;

	system.addDriver("nemo", &nemoDriver);
	system.addDriver("kiwer", &kiwerDriver);

	system.selectDriver("nemo");
	EXPECT_EQ("nemo", system.getCurrentDriverName());
}

TEST(TradingSystem, SelectKiwerDriver) {
	MockDriver nemoDriver;
	MockDriver kiwerDriver;
	AutoTradingSystem system;

	system.addDriver("nemo", &nemoDriver);
	system.addDriver("kiwer", &kiwerDriver);

	system.selectDriver("kiwer");
	EXPECT_EQ("kiwer", system.getCurrentDriverName());
}

TEST(TradingSystem, NemoLogin) {
	MockDriver nemoDriver;
	MockDriver kiwerDriver;
	AutoTradingSystem system;

	system.addDriver("nemo", &nemoDriver);
	system.addDriver("kiwer", &kiwerDriver);

	system.selectDriver("nemo");

	EXPECT_CALL(nemoDriver, loginSystem)
		.Times(1);
	EXPECT_CALL(kiwerDriver, loginSystem)
		.Times(0);

	system.login("user", "passwd");
}

TEST(TradingSystem, KiwerLogin) {
	MockDriver nemoDriver;
	MockDriver kiwerDriver;
	AutoTradingSystem system;

	system.addDriver("nemo", &nemoDriver);
	system.addDriver("kiwer", &kiwerDriver);

	system.selectDriver("kiwer");

	EXPECT_CALL(nemoDriver, loginSystem)
		.Times(0);
	EXPECT_CALL(kiwerDriver, loginSystem)
		.Times(1);

	system.login("user", "passwd");
}

TEST(TradingSystem, NemoBuyStock) {
	MockDriver nemoDriver;
	MockDriver kiwerDriver;
	AutoTradingSystem system;

	system.addDriver("nemo", &nemoDriver);
	system.addDriver("kiwer", &kiwerDriver);

	system.selectDriver("nemo");

	EXPECT_CALL(nemoDriver, buyStock)
		.Times(1);
	EXPECT_CALL(kiwerDriver, buyStock)
		.Times(0);

	system.buy("samsung", 50000, 15);
}

TEST(TradingSystem, KiwerBuyStock) {
	MockDriver nemoDriver;
	MockDriver kiwerDriver;
	AutoTradingSystem system;

	system.addDriver("nemo", &nemoDriver);
	system.addDriver("kiwer", &kiwerDriver);

	system.selectDriver("kiwer");

	EXPECT_CALL(nemoDriver, buyStock)
		.Times(0);
	EXPECT_CALL(kiwerDriver, buyStock)
		.Times(1);

	system.buy("samsung", 50000, 15);
}

TEST(TradingSystem, NemoSellSTock) {
	MockDriver nemoDriver;
	MockDriver kiwerDriver;
	AutoTradingSystem system;

	system.addDriver("nemo", &nemoDriver);
	system.addDriver("kiwer", &kiwerDriver);

	system.selectDriver("nemo");

	EXPECT_CALL(nemoDriver, buyStock)
		.Times(1);
	EXPECT_CALL(kiwerDriver, buyStock)
		.Times(0);

	system.sell("samsung", 50000, 15);
}

TEST(TradingSystem, KiwerSellStock) {
	MockDriver nemoDriver;
	MockDriver kiwerDriver;
	AutoTradingSystem system;

	system.addDriver("nemo", &nemoDriver);
	system.addDriver("kiwer", &kiwerDriver);

	system.selectDriver("kiwer");

	EXPECT_CALL(nemoDriver, sellStock)
		.Times(0);
	EXPECT_CALL(kiwerDriver, sellStock)
		.Times(1);

	system.sell("samsung", 50000, 15);
}


int main(void) {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}