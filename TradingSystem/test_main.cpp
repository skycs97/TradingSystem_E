#include <gmock/gmock.h>
#include <string>
#include "kiwer.h""
#include "nemo_api.h"
#include "driver.h"

using std::string;

class MockDriver : public Driver {
public:
	MOCK_METHOD(void, loginSystem, (string, string), (override));
	MOCK_METHOD(void, buyStock, (string, int, int), (override));
	MOCK_METHOD(void, sellStock, (string, int, int), (override));
	MOCK_METHOD(int, getMarketPrice, (string, int), (override));
};

TEST(TradingSystem, NemoLogin) {
	NemoAPI *nemoApi = new NemoAPI();
	KiwerAPI* kiwerApi = new KiwerAPI();
	Driver* nemoDriver = new MockDriver{ nemoApi };
	Driver* kiwerDriver = new MockDriver{ nemoApi };
	StockerBrockerInterface interface;

	interface.setDriver("nemo", nemoDriver);
	interface.setDriver("kiwer", kiwerDriver);

	interface.selectStockBrocker("nemo");

	interface.loginSystem("user", "pass");

	std::ostringstream oss;
	auto oldCoutStreamBuf = std::cout.rdbuf();
	std::cout.rdbuf(oss.rdbuf());

	std::cout.rdbuf(oldCoutStreamBuf);

	string actual = oss.str();

	EXPECT_EQ("[NEMO]user login GOOD\n", actual);
}

TEST(TradingSystem, KiwerLogin) {
	NemoAPI* nemoApi = new NemoAPI();
	KiwerAPI* kiwerApi = new KiwerAPI();
	Driver* nemoDriver = new MockDriver{ nemoApi };
	Driver* kiwerDriver = new MockDriver{ nemoApi };
	StockerBrockerInterface interface;

	interface.setDriver("nemo", nemoDriver);
	interface.setDriver("kiwer", kiwerDriver);

	interface.selectStockBrocker("kiwer");

	interface.loginSystem("user", "pass");

	std::ostringstream oss;
	auto oldCoutStreamBuf = std::cout.rdbuf();
	std::cout.rdbuf(oss.rdbuf());

	std::cout.rdbuf(oldCoutStreamBuf);

	string actual = oss.str();

	EXPECT_EQ("user login success\n", actual);
}

int main(void) {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}