#include <gtest/gtest.h>

#include "fpcpp.h"
using namespace fpcpp;

TEST(F, return_value)
{
	EXPECT_FALSE( F() );
	EXPECT_FALSE( F(true) );
	EXPECT_FALSE( F(1) );
	EXPECT_FALSE( F("true") );
	EXPECT_FALSE( F(std::string("true")) );
	EXPECT_FALSE( F(1, 2) );
	EXPECT_FALSE( F(1, true) );
	EXPECT_FALSE( F(true, "true") );
}
