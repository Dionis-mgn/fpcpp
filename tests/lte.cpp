#include <gtest/gtest.h>

#include <string>

#include "fpcpp.h"
using namespace fpcpp;

TEST(lte, implement_operator_less_or_equals_to)
{
	using namespace std::string_literals;

	EXPECT_TRUE(lte(1, 1));
	EXPECT_FALSE(lte(2, 1));
	EXPECT_TRUE(lte(1, 2));
	EXPECT_FALSE(lte(1.9, 1.0));
	EXPECT_TRUE(lte(1, 1.9));
	EXPECT_FALSE(lte("def"s, "abc"s));
	EXPECT_TRUE(lte("abc"s, "def"s));
}

/*  currying tests implemented in gt.cpp (it uses the same implementation)   */
