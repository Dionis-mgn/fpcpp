#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

#include <string>
#include <type_traits>
#include <vector>

#include "fpcpp.h"
using namespace fpcpp;

namespace _filter // preventing multiple definitions of odd
{

auto odd = [](uint32_t x) -> bool { return x % 2; };

RC_GTEST_PROP(filter, filtered_container_not_bigger_than_original,
              (const std::vector<uint32_t> &data))
{
	auto result = filter(odd, data);

	RC_CLASSIFY(result.size() == data.size());

	RC_ASSERT(result.size() <= data.size());

	static_assert(std::is_same<decltype(result), std::vector<uint32_t>>::value,
	              "filter returns wrong container type");
}

RC_GTEST_PROP(filter, return_empty_if_no_satisfied_condition,
              (const std::vector<std::string> &data))
{
	auto result = filter([](const std::string) { return false; }, data);

	RC_ASSERT(result.size() == 0);
}

RC_GTEST_PROP(filter, return_original_container_if_all_elements_accepted,
              (const std::vector<std::string> &data))
{
	auto result = filter([](const std::string) { return true; }, data);

	RC_ASSERT(result == data);
}


TEST(filter, odd_filter)
{
	using container_t = const std::vector<uint32_t>;
	container_t input{1, 2, 3, 4, 5};
	container_t expected{1, 3, 5};

	auto fn     = filter(odd);
	auto result = fn(input);

	EXPECT_EQ(result, expected);
}

TEST(filter, std_list)
{
	using container_t = const std::list<uint32_t>;
	container_t input{1, 2, 3, 4, 5};
	container_t expected{1, 3, 5};

	auto fn     = filter(odd);
	auto result = fn(input);

	EXPECT_EQ(result, expected);
}

TEST(filter, empty)
{
	const std::list<uint32_t> input{};

	auto fn     = filter(odd);
	auto result = fn(input);

	EXPECT_EQ(result, input);
}

} // namespace _filter
