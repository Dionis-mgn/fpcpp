#include <gtest/gtest.h>

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include "fpcpp.h"
using namespace fpcpp;

TEST(is_empty, string)
{
	EXPECT_EQ(is_empty()(std::string("")), true);
	EXPECT_EQ(is_empty()(std::string("test")), false);
}

TEST(is_empty, vector)
{
	using cont_t = std::vector<uint32_t>;

	EXPECT_EQ(is_empty()( cont_t({ }) ), true);
	EXPECT_EQ(is_empty()( cont_t({0}) ), false);
}

TEST(is_empty, map)
{
	using cont_t = std::unordered_map<uint32_t, std::string>;

	EXPECT_EQ(is_empty()( cont_t({             }) ), true);
	EXPECT_EQ(is_empty()( cont_t({ {0, "test"} }) ), false);
}
