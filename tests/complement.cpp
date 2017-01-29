#include <gtest/gtest.h>

#include "fpcpp.h"
using namespace fpcpp;

TEST(complement, no_arg_functions)
{
	EXPECT_TRUE ( complement(F())() );
	EXPECT_FALSE( complement(T())() );
}

TEST(complement, int_casting)
{
	EXPECT_FALSE( complement(identity())(1) );
	EXPECT_FALSE( complement(identity())(5) );
	EXPECT_TRUE ( complement(identity())(0) );
}

TEST(complement, multiple_args)
{
	EXPECT_TRUE ( complement(add(1))(-1) );
	EXPECT_FALSE( complement(add())(2, 4) );
}
