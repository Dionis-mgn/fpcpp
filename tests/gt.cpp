#include <gtest/gtest.h>

#include <string>

#include "fpcpp.h"
using namespace fpcpp;

TEST(gt, implement_operator_greater_than)
{
	using namespace std::string_literals;

	EXPECT_FALSE(gt(1, 1));
	EXPECT_FALSE(gt(1, 2));
	EXPECT_TRUE(gt(2, 1));
	EXPECT_FALSE(gt(0.9, 1.0));
	EXPECT_TRUE(gt(1, 0.9));
	EXPECT_FALSE(gt("abc"s, "def"s));
	EXPECT_TRUE(gt("def"s, "abc"s));
}

TEST(gt, currying)
{
	auto _gt = gt();

	auto fiveGreaterThan = _gt(5);
	EXPECT_TRUE(fiveGreaterThan(1));

	using namespace std::placeholders;

	auto strangeComparation1 = gt(_2, _4);
	auto strangeComparation2 = _gt(_4, _2);

	EXPECT_TRUE(strangeComparation1(10, 9, 8, 7));
	EXPECT_FALSE(strangeComparation2(10, 9, 8, 7));
}

TEST(gt, currying_special_case)
{
	using namespace std::placeholders;

	auto gt5 = gt(_1, 5);

	EXPECT_TRUE(gt5(10));
	EXPECT_FALSE(gt5(1));
	EXPECT_FALSE(gt5(5));
}
