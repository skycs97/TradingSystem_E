#include <gmock/gmock.h>
#include "kiwer.cpp""
#include "nemo_api.cpp"

int main(void) {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}