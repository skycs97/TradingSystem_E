#include "gmock/gmock.h"
#include <string>

#include "driver.h"
#include "kiwer_driver.h"
#include "auto_trading_system.h"

using namespace testing;
using std::string;

class AutoTradingSystemFixtureWithKiwer : public Test {
protected:
	void SetUp() override {
		system.selectStockBrocker(&driver);
	}
public:
	AutoTradingSystem system;
	KiwerDriver driver;
};

TEST_F(AutoTradingSystemFixtureWithKiwer, Login) {
	string expected = "kiwer login success\n";

	std::ostringstream oss;
	auto oldCoutStreamBuf = std::cout.rdbuf();
	std::cout.rdbuf(oss.rdbuf());

	system.login("kiwer", "kiwer_passwd");

	std::cout.rdbuf(oldCoutStreamBuf);
	string actual = oss.str();

	EXPECT_EQ(expected, actual);
}

TEST_F(AutoTradingSystemFixtureWithKiwer, BuyStock) {
	string expected = "samsung : Buy stock ( 50000 * 15)\n";

	std::ostringstream oss;
	auto oldCoutStreamBuf = std::cout.rdbuf();
	std::cout.rdbuf(oss.rdbuf());

	system.buy("samsung", 50000, 15);

	std::cout.rdbuf(oldCoutStreamBuf);
	string actual = oss.str();

	EXPECT_EQ(expected, actual);
}

TEST_F(AutoTradingSystemFixtureWithKiwer, SellSTock) {
	string expected = "samsung : Sell stock ( 50000 * 15)\n";

	std::ostringstream oss;
	auto oldCoutStreamBuf = std::cout.rdbuf();
	std::cout.rdbuf(oss.rdbuf());

	system.sell("samsung", 50000, 15);

	std::cout.rdbuf(oldCoutStreamBuf);
	string actual = oss.str();

	EXPECT_EQ(expected, actual);
}

class MockedKiwerDriver : public KiwerDriver {
public:
	MOCK_METHOD(int, getMarketPriceFromKiwerAPI, (string stockCode), (override));
	MOCK_METHOD(void, sleep, (int ms), (override));
};

TEST(KiwerDriverTest, getMarketPrice) {
	MockedKiwerDriver mockedDriver;
	EXPECT_CALL(mockedDriver, getMarketPriceFromKiwerAPI(_)).WillRepeatedly(Return(10000));
	EXPECT_CALL(mockedDriver, sleep(200)).Times(1);
	EXPECT_EQ(10000, mockedDriver.getMarketPrice("samsung", 200));
}