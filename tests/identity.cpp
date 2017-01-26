#include <gtest/gtest.h>

#include "fpcpp.h"
using namespace fpcpp;

TEST(identity, return_value)
{
	std::string test("test");

	EXPECT_EQ( identity()(false) , false);
	EXPECT_EQ( identity()(0) , 0);
	EXPECT_EQ( identity()(std::string("test")) , test);
	EXPECT_EQ( identity()(test, 1, false) , test);
	EXPECT_EQ( identity()(0, 55) , 0);
	EXPECT_EQ( identity()(55, 0) , 55);
}
