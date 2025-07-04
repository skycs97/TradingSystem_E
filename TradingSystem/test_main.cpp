#include <gmock/gmock.h>
#include <string>
#include "kiwer.cpp""
#include "nemo_api.cpp"
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
	Driver* nemoDriver = new MockDriver{ nemoApi, kiwerApi };

	std::ostringstream oss;
	auto oldCoutStreamBuf = std::cout.rdbuf();
	std::cout.rdbuf(oss.rdbuf());

	EXPECT_CALL(nemoDriver, loginSystem)
		.WithRepeatedly("[NEMO]user login GOOD\n");

	nemoDriver.loginSystem("user", "pass");


	std::cout.rdbuf(oldCoutStreamBuf);

	string actual = oss.str();

	EXPECT_EQ("[NEMO]user login GOOD\n", actual);
}

TEST(TradingSystem, KiwerLogin) {
	NemoAPI* nemoApi = new NemoAPI();
	KiwerAPI* kiwerApi = new KiwerAPI();
	Driver* nemoDriver = new MockDriver{ nemoApi, kiwerApi };

	std::ostringstream oss;
	auto oldCoutStreamBuf = std::cout.rdbuf();
	std::cout.rdbuf(oss.rdbuf());

	EXPECT_CALL(nemoDriver, loginSystem)
		.WithRepeatedly("user login success\n");

	nemoDriver.loginSystem("user", "pass");

	std::cout.rdbuf(oldCoutStreamBuf);

	string actual = oss.str();

	EXPECT_EQ("user login success\n", actual);
}

TEST(TradingSystem, NemoBuyStock) {
	NemoAPI* nemoApi = new NemoAPI();
	KiwerAPI* kiwerApi = new KiwerAPI();
	Driver* nemoDriver = new MockDriver{ nemoApi, kiwerApi };

	std::ostringstream oss;
	auto oldCoutStreamBuf = std::cout.rdbuf();
	std::cout.rdbuf(oss.rdbuf());

	EXPECT_CALL(nemoDriver, buyStock)
		.WithRepeatedly("[NEMO]samsung buy stock ( price : 50000 ) * ( count : 15)\n");

	nemoDriver.buyStock("samsung", 50000, 15);

	std::cout.rdbuf(oldCoutStreamBuf);

	string actual = oss.str();

	EXPECT_EQ("[NEMO]samsung buy stock ( price : 50000 ) * ( count : 15)\n", actual);
}
TEST(TradingSystem, KiwerBuyStock) {
	NemoAPI* nemoApi = new NemoAPI();
	KiwerAPI* kiwerApi = new KiwerAPI();
	Driver* nemoDriver = new MockDriver{ nemoApi, kiwerApi };

	std::ostringstream oss;
	auto oldCoutStreamBuf = std::cout.rdbuf();
	std::cout.rdbuf(oss.rdbuf());

	EXPECT_CALL(nemoDriver, buyStock)
		.WithRepeatedly("samsung : Buy stock ( 50000 * 15)\n");

	nemoDriver.buyStock("samsung", 50000, 15);

	std::cout.rdbuf(oldCoutStreamBuf);

	string actual = oss.str();

	EXPECT_EQ("samsung : Buy stock ( 50000 * 15)\n", actual);
}


int main(void) {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}