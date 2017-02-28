#include <gtest/gtest.h>

#include <cstdint>
#include <functional>
#include <vector>

#include "fpcpp.h"
using namespace fpcpp;

namespace _pipe
{

TEST(pipe, left_to_right_composition)
{
	using container_t = std::vector<uint32_t>;
	container_t input{10, 20, 30};
	container_t expected1{14, 24, 34};
	container_t expected2{12, 22, 32};

	auto fn = pipe(multiply(2), add(), map());

	container_t result1 = fn(2)(input);
	auto        result2 = fn(1)(input);

	EXPECT_EQ(result1, expected1);
	EXPECT_EQ(result2, expected2);
}

class UselessFunctor
{
private:
	uint32_t x;

public:
	UselessFunctor(uint32_t _x) : x(_x)
	{
	}

	uint32_t mult(uint32_t y)
	{
		return x * y;
	}
};

TEST(pipe, std_bind)
{
	using namespace std::placeholders;
	auto functor1 = std::make_unique<UselessFunctor>(2);
	auto functor2 = std::make_unique<UselessFunctor>(10);

	auto fn = pipe(std::bind(&UselessFunctor::mult, _1, _2),
	               std::bind(&UselessFunctor::mult, functor2.get(), _1));

	EXPECT_EQ(fn(functor1, 5), 100); // 2 * 5 * 10
	EXPECT_EQ(fn(functor2, 9), 900); // 9 * 10 * 10
}

} // namespace _pipe
