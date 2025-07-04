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
		EXPECT_EQ("[AutoTradingSystem] driver is null", e.what());
	}
}