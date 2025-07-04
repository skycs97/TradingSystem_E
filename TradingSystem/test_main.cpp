#include <gmock/gmock.h>
#include <string>

using std::string;
using namespace testing;

int main(void) {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}