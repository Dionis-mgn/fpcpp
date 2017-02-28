#include <gtest/gtest.h>

#include <string>

#include "fpcpp.h"
using namespace fpcpp;

TEST(tap, return_value)
{
	EXPECT_EQ(always(0)(), 0);
	EXPECT_EQ(always<std::string>("test")(), "test");
	EXPECT_EQ(always(true)(), true);
}

TEST(tap, can_produce_side_effects)
{
	uint32_t sideEffect = 10;
	auto tapper         = [&sideEffect](uint32_t i) { sideEffect *= i; };

	tap(tapper, 5);

	EXPECT_EQ(sideEffect, 50);
}
