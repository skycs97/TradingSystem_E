#include <gmock/gmock.h>
#include "auto_trading_system.h"
#include <exception>

TEST(AutoTradingSystemCommonTest, selectStockBrockerDriverIsNull) {
	AutoTradingSystem system;
	try {
		system.selectStockBrocker(nullptr);
		FAIL();
	}
	catch (DriverIsNullPtrException& e) {
		EXPECT_EQ(string("[AutoTradingSystem] driver is null"), string(e.what()));
	}
}

TEST(AutoTradingSystemCommonTest, loginTestDriverIsNull) {
	AutoTradingSystem system;
	try {
		system.login("user", "pass");
		FAIL();
	}
	catch (DriverIsNullPtrException& e) {
		EXPECT_EQ(string("[AutoTradingSystem] can't login"), string(e.what()));
	}
}

TEST(AutoTradingSystemCommonTest, buyTestDriverIsNull) {
	AutoTradingSystem system;
	try {
		system.buy("samsung", 50000, 4);
		FAIL();
	}
	catch (DriverIsNullPtrException& e) {
		EXPECT_EQ(string("[AutoTradingSystem] can't buy stock"), string(e.what()));
	}
}
TEST(AutoTradingSystemCommonTest, sellTestDriverIsNull) {
	AutoTradingSystem system;
	try {
		system.sell("samsung", 50000, 2);
		FAIL();
	}
	catch (DriverIsNullPtrException& e) {
		EXPECT_EQ(string("[AutoTradingSystem] can't sell stock"), string(e.what()));
	}
}
TEST(AutoTradingSystemCommonTest, getPriceTestDriverIsNull) {
	AutoTradingSystem system;
	try {
		int price = system.getPrice("samsung");
		FAIL();
	}
	catch (DriverIsNullPtrException& e) {
		EXPECT_EQ(string("[AutoTradingSystem] can't get price"), string(e.what()));
	}
}


