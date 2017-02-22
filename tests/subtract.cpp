#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

#include <functional>

#include "fpcpp.h"
using namespace fpcpp;

RC_GTEST_PROP(subtract, identity, (uint32_t x))
{
	RC_ASSERT(subtract(x, 0) == x);
	RC_ASSERT(subtract(x, x) == 0);
}

TEST(subtract, two_numbers)
{
	EXPECT_EQ( subtract(10, 8), 2 );
}

TEST(subtract, curried)
{
	using namespace std::placeholders;

	auto s10 = subtract(_1, 10);
	EXPECT_EQ( s10(50), 40 );

	auto s_from10 = subtract(10);
	EXPECT_EQ( s_from10(8), 2 );
}
