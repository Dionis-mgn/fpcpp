#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

#include "fpcpp.h"
using namespace fpcpp;

/* *multiply* commutative ONLY in case if (operator *) for used type is commutative */
RC_GTEST_PROP(multiply, commutative, (uint32_t x, uint32_t y))
{
	RC_ASSERT(multiply(x, y) == multiply(y, x));
}

/* *multiply* associative ONLY in case if (operator *) for used type is commutative */
RC_GTEST_PROP(multiply, associative, (uint32_t x, uint32_t y, uint32_t z))
{
	RC_ASSERT(multiply(x, multiply(y, z)) == multiply(multiply(x, y), z));
}

RC_GTEST_PROP(multiply, identity, (uint32_t x))
{
	RC_ASSERT(multiply(x, 1) == x);
	RC_ASSERT(multiply(1, x) == x);
}

TEST(multiply, two_numbers)
{
	EXPECT_EQ( multiply(2, 5), 10 );
}

TEST(multiply, curried)
{
	auto x10 = multiply(10);
	EXPECT_EQ( x10(5), 50 );
}
