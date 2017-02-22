#include <gtest/gtest.h>

#include <string>

#include "fpcpp.h"
using namespace fpcpp;

TEST(lt, implement_operator_less_than)
{
	using namespace std::string_literals;

	EXPECT_FALSE( lt(1, 1) );
	EXPECT_FALSE( lt(2, 1) );
	EXPECT_TRUE ( lt(1, 2) );
	EXPECT_FALSE( lt(1.9, 1.0) );
	EXPECT_TRUE ( lt(1, 1.9) );
	EXPECT_FALSE( lt("def"s, "abc"s) );
	EXPECT_TRUE ( lt("abc"s, "def"s) );
}

/*  currying tests implemented in gt.cpp (it uses the same implementation)   */
