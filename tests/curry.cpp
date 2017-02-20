#include <gtest/gtest.h>

#include "fpcpp.h"
using namespace fpcpp;

TEST(curry, pass_all_arguments)
{
	auto mulL = [](int i, int j, int k, int m) { return i * j * k * m; };

	auto curried = curry(mulL, 1, 2, 3, 4);
	EXPECT_EQ(curried(), 24);
}

TEST(curry, pass_no_arguments)
{
	auto mulL = [](int i, int j, int k, int m) { return i * j * k * m; };

	using namespace std::placeholders;

	auto curried = curry(mulL, _1, _2, _3, _4);
	EXPECT_EQ(curried(1, 2, 3, 4), 24);
}

TEST(curry, ignore_extra_leading_args)
{
	auto id = [](int i) { return i; };

	using namespace std::placeholders;

	auto curried = curry(id, _5);
	EXPECT_EQ(curried(1, 2, 3, 4, 5), 5);
}
