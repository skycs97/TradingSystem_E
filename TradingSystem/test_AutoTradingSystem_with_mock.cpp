#include "gmock/gmock.h"
#include <string>

#include "driver.h"
#include "auto_trading_system.h"

using namespace testing;
using std::string;

class MockDriver : public Driver {
public:
	MOCK_METHOD(void, loginSystem, (string, string), (override));
	MOCK_METHOD(void, buyStock, (string, int, int), (override));
	MOCK_METHOD(void, sellStock, (string, int, int), (override));
	MOCK_METHOD(int, getMarketPrice, (string, int), (override));
};

class AutoTradingSystemFixtureWithMock : public Test {
protected:
	void SetUp() override {
		system.selectStockBrocker(&driver);
	}
public:
	AutoTradingSystem system;
	MockDriver driver;
};

TEST_F(AutoTradingSystemFixtureWithMock, Login) {
	EXPECT_CALL(driver, loginSystem)
		.Times(1);

	system.login("user", "passwd");
}

TEST_F(AutoTradingSystemFixtureWithMock, BuyStock) {
	EXPECT_CALL(driver, buyStock)
		.Times(1);

	system.buy("samsung", 50000, 15);
}

TEST_F(AutoTradingSystemFixtureWithMock, SellSTock) {
	EXPECT_CALL(driver, sellStock)
		.Times(1);

	system.sell("samsung", 50000, 15);
}

TEST_F(AutoTradingSystemFixtureWithMock, GetMarketPrice) {
	EXPECT_CALL(driver, getMarketPrice(_, _))
		.WillRepeatedly(Return(10000));

	EXPECT_EQ(system.getPrice("samsung"), 10000);
}

TEST_F(AutoTradingSystemFixtureWithMock, buyNiceTiming) {
	EXPECT_CALL(driver, getMarketPrice)
		.WillOnce(Return(10000))
		.WillOnce(Return(12000))
		.WillOnce(Return(14000));

	EXPECT_CALL(driver, buyStock)
		.Times(1);

	EXPECT_EQ(true, system.buyNiceTiming("samsung", 14000));
}

TEST_F(AutoTradingSystemFixtureWithMock, buyNiceTimingNoBuy) {
	EXPECT_CALL(driver, getMarketPrice)
		.WillOnce(Return(10000))
		.WillOnce(Return(12000))
		.WillOnce(Return(11000));

	EXPECT_CALL(driver, buyStock)
		.Times(0);

	EXPECT_EQ(false, system.buyNiceTiming("samsung", 14000));
}

TEST_F(AutoTradingSystemFixtureWithMock, sellNiceTiming) {
	EXPECT_CALL(driver, getMarketPrice)
		.WillOnce(Return(15000))
		.WillOnce(Return(14500))
		.WillOnce(Return(14000));

	EXPECT_CALL(driver, sellStock)
		.Times(1);

	EXPECT_EQ(true, system.sellNiceTiming("samsung", 10));
}

TEST_F(AutoTradingSystemFixtureWithMock, sellNiceTimingNoSell) {
	EXPECT_CALL(driver, getMarketPrice)
		.WillOnce(Return(14000))
		.WillOnce(Return(13500))
		.WillOnce(Return(20000));

	EXPECT_CALL(driver, sellStock)
		.Times(0);

	EXPECT_EQ(false, system.sellNiceTiming("samsung", 10));
}

TEST_F(AutoTradingSystemFixtureWithMock, BuyStockMinusPrice) {
	EXPECT_THROW(system.buy("samsung",  - 1, 10), std::exception);
}
TEST_F(AutoTradingSystemFixtureWithMock, SellStockMinusPrice) {
	EXPECT_THROW(system.sell("samsung", -1, 10000), std::exception);
}

TEST_F(AutoTradingSystemFixtureWithMock, BuyStockMinusCount) {
	EXPECT_THROW(system.buy("samsung", 10000, -1), std::exception);
}
TEST_F(AutoTradingSystemFixtureWithMock, SellStockMinusCount) {
	EXPECT_THROW(system.sell("samsung", 10000, -1), std::exception);
}

