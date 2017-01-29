#include <gtest/gtest.h>

#include "fpcpp.h"
using namespace fpcpp;

TEST(not, reverce_argument)
{
	EXPECT_TRUE ( Not()(false) );
	EXPECT_FALSE( Not()(true) );
	EXPECT_TRUE ( Not()(0) );
	EXPECT_FALSE( Not()(1) );
	EXPECT_FALSE( Not()(25) );
}
