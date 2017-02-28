#include <gtest/gtest.h>

#include <list>
#include <vector>

#include "fpcpp.h"
using namespace fpcpp;

namespace _reduce
{

TEST(reduce, simple_vector_operations)
{
	using container_t = std::vector<uint32_t>;
	container_t input{1, 2, 3, 4, 5};

	EXPECT_EQ(reduce(add(), 0)(input), 15);
	EXPECT_EQ(reduce(multiply(), 1)(input), 120);
}

TEST(reduce, return_accumulator_for_an_empty_container)
{
	EXPECT_EQ(reduce(add(), 1)(std::list<uint32_t>({})), 1);
	EXPECT_EQ(reduce(multiply(), 55)(std::vector<uint32_t>({})), 55);
}

TEST(reduce, currying)
{
	using container_t = std::vector<uint32_t>;
	container_t input{1, 2, 3, 4, 5};
	uint32_t    expected = 15;

	uint32_t r1 = reduce(add(), 0, input);
	uint32_t r2 = reduce(add(), 0)(input);
	uint32_t r3 = reduce(add())(0, input);
	uint32_t r4 = reduce(add())(0)(input);
	uint32_t r5 = reduce()(add(), 0, input);
	uint32_t r6 = reduce()(add())(0, input);
	uint32_t r7 = reduce()(add(), 0)(input);
	uint32_t r8 = reduce()(add())(0)(input);

	EXPECT_EQ(r1, expected);
	EXPECT_EQ(r2, expected);
	EXPECT_EQ(r3, expected);
	EXPECT_EQ(r4, expected);
	EXPECT_EQ(r5, expected);
	EXPECT_EQ(r6, expected);
	EXPECT_EQ(r7, expected);
	EXPECT_EQ(r8, expected);
}

} // namespace _reduce
