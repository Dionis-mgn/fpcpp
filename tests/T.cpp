#include <gtest/gtest.h>

#include "fpcpp.h"
using namespace fpcpp;

TEST(T, return_value)
{
	EXPECT_TRUE( T() );
	EXPECT_TRUE( T(false) );
	EXPECT_TRUE( T(0) );
	EXPECT_TRUE( T("false") );
	EXPECT_TRUE( T(std::string("false")) );
	EXPECT_TRUE( T(0, 55) );
	EXPECT_TRUE( T(0, false) );
	EXPECT_TRUE( T(false, "false") );
}
