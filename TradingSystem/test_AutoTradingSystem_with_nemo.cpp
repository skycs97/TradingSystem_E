#include "gmock/gmock.h"
#include <string>

#include "driver.h"
#include "nemo_driver.h"
#include "auto_trading_system.h"
#include "nemo_api.cpp"

using namespace testing;
using std::string;

class AutoTradingSystemFixtureWithNemo : public Test {
protected:
	void SetUp() override {
		system.selectStockBrocker(&driver);
	}
public:
	AutoTradingSystem system;
	NemoDriver driver;
};

TEST_F(AutoTradingSystemFixtureWithNemo, Login) {
	string expected = "[NEMO]nemo login GOOD\n";

	std::ostringstream oss;
	auto oldCoutStreamBuf = std::cout.rdbuf();
	std::cout.rdbuf(oss.rdbuf());

	system.login("nemo", "nemo_passwd");

	std::cout.rdbuf(oldCoutStreamBuf);
	string actual = oss.str();

	EXPECT_EQ(expected, actual);
}

TEST_F(AutoTradingSystemFixtureWithNemo, BuyStock) {
	string expected = "[NEMO]samsung buy stock ( price : 50000 ) * ( count : 15)\n";

	std::ostringstream oss;
	auto oldCoutStreamBuf = std::cout.rdbuf();
	std::cout.rdbuf(oss.rdbuf());

	system.buy("samsung", 50000, 15);

	std::cout.rdbuf(oldCoutStreamBuf);
	string actual = oss.str();

	EXPECT_EQ(expected, actual);
}

TEST_F(AutoTradingSystemFixtureWithNemo, SellSTock) {
	string expected = "[NEMO]samsung sell stock ( price : 50000 ) * ( count * 15)\n";

	std::ostringstream oss;
	auto oldCoutStreamBuf = std::cout.rdbuf();
	std::cout.rdbuf(oss.rdbuf());

	system.sell("samsung", 50000, 15);

	std::cout.rdbuf(oldCoutStreamBuf);
	string actual = oss.str();

	EXPECT_EQ(expected, actual);
}

TEST_F(AutoTradingSystemFixtureWithNemo, GetMarketPrice) {
	srand(777);
	EXPECT_EQ(5500, system.getPrice("samsung"));
}