#include <gtest/gtest.h>

#include <string>

#include "fpcpp.h"
using namespace fpcpp;

TEST(always, return_value)
{
	EXPECT_EQ(always(0)(), 0);
	EXPECT_EQ(always<std::string>("test")(), "test");
	EXPECT_EQ(always(true)(), true);
}

TEST(always, ignores_args)
{
	EXPECT_EQ(always(0)(5), 0);
	EXPECT_EQ(always(0)("true"), 0);
	EXPECT_EQ(always(0)(5, 10), 0);
}
