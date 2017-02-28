#include <gtest/gtest.h>

#include "fpcpp.h"
using namespace fpcpp;

TEST(both, combines_to_functions_in_one)
{
	using namespace std::placeholders;

	auto gt10 = gt(_1, 10);
	auto lt20 = lt(_1, 20);

	auto inRange = both(gt10, lt20);

	EXPECT_TRUE(inRange(15));
	EXPECT_FALSE(inRange(20));
	EXPECT_FALSE(inRange(30));
}

TEST(both, accept_functions_with_several_arguments)
{
	using namespace std::placeholders;

	auto is_sorted        = [](int a, int b, int c) { return a <= b && b <= c; };
	auto sum_more_than_10 = [](int a, int b, int c) { return (a + b + c) > 10; };

	auto f = both(is_sorted, sum_more_than_10);

	EXPECT_TRUE(f(10, 20, 30));
	EXPECT_FALSE(f(1, 2, 3));
	EXPECT_FALSE(f(20, 10, 30));
}

TEST(both, accept_variadic_functions)
{
	using namespace std::placeholders;

	auto more_than_5  = [](auto &&... args) { return sizeof...(args) > 5; };
	auto first_is_odd = [](auto &&arg1, auto &&... args) -> bool {
		return arg1 % 2;
	};

	auto f = both(more_than_5, first_is_odd);

	EXPECT_TRUE(f(1, 2, 3, 4, 5, 6));
	EXPECT_FALSE(f(1));
	EXPECT_FALSE(f(2, 3, 4, 5, 6, 7));
}

TEST(both, does_not_execute_second_function_if_first_returned_false)
{
	using namespace std::placeholders;

	bool first_exec  = false;
	bool second_exec = false;

	auto first = [&first_exec](int) {
		first_exec = true;
		return false;
	};
	auto second = [&second_exec](int) {
		second_exec = true;
		return false;
	};

	auto f = both(first, second);

	EXPECT_FALSE(f(5));
	EXPECT_TRUE(first_exec);
	EXPECT_FALSE(second_exec);
}
