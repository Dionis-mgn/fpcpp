#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

#include <functional>

#include "fpcpp.h"
using namespace fpcpp;

RC_GTEST_PROP(divide, identity, (uint32_t x))
{
	RC_ASSERT(divide(x, 1) == x);
	if (x == 0)
	{
		RC_TAG("Empty after trimming");
		return;
	}
	RC_ASSERT(divide(x, x) == 1);
}

TEST(divide, two_numbers)
{
	EXPECT_EQ(divide(10, 5), 2);
}

TEST(divide, curried)
{
	using namespace std::placeholders;

	auto d10 = divide(_1, 10);
	EXPECT_EQ(d10(50), 5);

	auto d10by = divide(10);
	EXPECT_EQ(d10by(5), 2);
}
