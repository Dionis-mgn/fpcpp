#include <gtest/gtest.h>

#include <string>

#include "fpcpp.h"
using namespace fpcpp;

TEST(equals, implement_operator_equals_to)
{
	using namespace std::string_literals;

	EXPECT_TRUE ( equals(  1,   1) );
	EXPECT_FALSE( equals(  1,   2) );
	EXPECT_FALSE( equals(  2,   1) );
	EXPECT_FALSE( equals(0.9, 1.0) );
	EXPECT_FALSE( equals(  1, 0.9) );

	// It's bad idea to compare floats like that
	//EXPECT_FALSE( equals(0.9,   0.9) );

	EXPECT_FALSE( equals("abc"s , "def"s) );
	EXPECT_FALSE( equals("def"s , "abc"s) );
	EXPECT_TRUE ( equals("test"s, "test"s) );
}

/*  currying tests implemented in gt.cpp (it uses the same implementation)   */
