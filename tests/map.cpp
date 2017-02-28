#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

#include <cstdint>
#include <string>
#include <type_traits>

#include "fpcpp.h"
using namespace fpcpp;

RC_GTEST_PROP(map, identity_map_equals_to_original,
              (const std::vector<std::string> &original))
{
	auto fn     = map(identity());
	auto mapped = fn(original);
	RC_ASSERT(mapped == original);
}

auto x2  = [](auto i) { return i * 2; };
auto d2  = [](uint32_t i) { return i / 2; };
auto inc = [](auto i) { return i + 1; };
auto dec = [](auto i) { return i - 1; };

TEST(map, simple_math_mapping)
{
	using container_t = std::vector<uint32_t>;

	container_t input{1, 2, 3, 4, 5, 6, 7, 8, 9};
	container_t expected1{0, 1, 2, 3, 4, 5, 6, 7, 8};
	container_t expected2{0, 2, 4, 6, 8, 10, 12, 14, 16};

	auto vecX2  = map(x2);
	auto vecD2  = map(d2);
	auto vecInc = map(inc);
	auto vecDec = map(dec);

	auto r1 = vecDec(input);
	auto r2 = vecX2(r1);
	auto r3 = vecD2(r2);
	auto r4 = vecInc(r3);

	EXPECT_EQ(r1, expected1);
	EXPECT_EQ(r2, expected2);
	EXPECT_EQ(r3, expected1);
	EXPECT_EQ(r4, input);

	static_assert(std::is_same<container_t, decltype(r1)>::value,
	              "map returns wrong container type");
	static_assert(std::is_same<container_t, decltype(r2)>::value,
	              "map returns wrong container type");
	static_assert(std::is_same<container_t, decltype(r3)>::value,
	              "map returns wrong container type");
	static_assert(std::is_same<container_t, decltype(r4)>::value,
	              "map returns wrong container type");
}

TEST(map, empty_container)
{
	using container_t = std::list<uint32_t>;
	container_t input{};

	auto fn     = map(x2);
	auto output = fn(input);

	EXPECT_EQ(input, output);
}

TEST(map, lambda)
{
	using container_t = std::vector<std::string>;
	container_t input{"test", "test2"};
	container_t expected{"test!", "test2!"};

	auto fn     = map([](const std::string &s) { return s + '!'; });
	auto output = fn(input);

	EXPECT_EQ(output, expected);
}

struct ToStringFunctor
{
	std::string operator()(uint32_t v)
	{
		return std::to_string(v);
	}
};

TEST(map, functor)
{
	std::vector<uint32_t>    input{1, 2, 3};
	std::vector<std::string> expected{"1", "2", "3"};

	auto fn     = map(ToStringFunctor());
	auto output = fn(input);

	EXPECT_EQ(output, expected);
}

TEST(map, currying)
{
	using container_t = std::vector<uint32_t>;
	container_t input{1, 2, 3, 4, 5};
	container_t expected{2, 4, 6, 8, 10};

	auto curried         = map(x2);
	auto curriedResult   = curried(input);
	auto uncurriedResult = map(x2, input);

	EXPECT_EQ(uncurriedResult, curriedResult);
	EXPECT_EQ(uncurriedResult, expected);
}
