#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

#include "fpcpp.h"
using namespace fpcpp;

/* *add* commutative ONLY in case if (operator +) for used type is commutative */
RC_GTEST_PROP(add, commutative, (uint32_t x, uint32_t y))
{
	EXPECT_EQ(add(x, y), add(y, x));
}

/* *add* associative ONLY in case if (operator +) for used type is commutative */
RC_GTEST_PROP(add, associative, (uint32_t x, uint32_t y, uint32_t z))
{
	EXPECT_EQ(add(x, add(y, z)), add(add(x, y), z));
}

RC_GTEST_PROP(add, identity, (uint32_t x))
{
	EXPECT_EQ(add(x, 0), x);
	EXPECT_EQ(add(0, x), x);
}

TEST(add, two_numbers)
{
	EXPECT_EQ( add(20, 5), 25 );
}

TEST(add, curried)
{
	auto addFive = add(5);
	EXPECT_EQ( addFive(20), 25 );
}

TEST(add, strings)
{
	const std::string te("te");
	const std::string st("st");
	const std::string test("test");

	EXPECT_EQ(add(te, st), test);

	auto curried = add(st);
	EXPECT_EQ(curried(te), test);
}

TEST(add, temporary_strings)
{
	EXPECT_EQ(add(std::string("te"), std::string("st")), std::string("test"));
}
