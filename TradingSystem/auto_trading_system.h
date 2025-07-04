#pragma once

class AutoTradingSystem {
public:
	void login(string id, string pw);

private:
	Driver* driver;
};