#include <gtest/gtest.h>

#include <string>

#include "fpcpp.h"
using namespace fpcpp;

TEST(gte, implement_operator_greater_or_equals_to)
{
	using namespace std::string_literals;

	EXPECT_TRUE ( gte(1, 1) );
	EXPECT_FALSE( gte(1, 2) );
	EXPECT_TRUE ( gte(2, 1) );
	EXPECT_FALSE( gte(0.9, 1.0) );
	EXPECT_TRUE ( gte(1, 0.9) );
	EXPECT_FALSE( gte("abc"s, "def"s) );
	EXPECT_TRUE ( gte("def"s, "abc"s) );
}

/*  currying tests implemented in gt.cpp (it uses the same implementation)   */
