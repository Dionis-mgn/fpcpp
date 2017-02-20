#include <gtest/gtest.h>

#include "fpcpp.h"
using namespace fpcpp;

TEST(curry, pass_all_arguments)
{
	auto mulL = [](int i, int j, int k, int m) { return i * j * k * m; };

	auto curried = curry(mulL, 1, 2, 3, 4);
	EXPECT_EQ(curried(), 24);
}
