#include <gtest/gtest.h>

#include <string>

#include "fpcpp.h"
using namespace fpcpp;

namespace _split
{

auto allEmpty = [](const auto &container) {
	for (auto &v : container)
	{
		if (!v.empty())
			return false;
	}
	return true;
};

TEST(split, split_keywords)
{
	std::string              source   = "test,keywords,bingo!";
	std::vector<std::string> expected = {"test", "keywords", "bingo!"};

	EXPECT_EQ(split(',', source), expected);
}

TEST(split, empty_input)
{
	auto result = split(',', "");
	EXPECT_EQ(result.size(), 1);
	EXPECT_TRUE(allEmpty(result));

	result = split(' ', "");
	EXPECT_EQ(result.size(), 1);
	EXPECT_TRUE(allEmpty(result));
}

TEST(split, no_separator)
{
	std::string source = "test,keywords,bingo!";

	auto result = split(' ', source);

	EXPECT_EQ(result.size(), 1);
	EXPECT_EQ(result[0], source);
}

TEST(split, just_separator)
{
	std::string s1 = ",";
	std::string s2 = ",,";
	std::string s3 = ",,,,,,";

	auto r1 = split(',', s1);
	auto r2 = split(',', s2);
	auto r3 = split(',', s3);

	EXPECT_EQ(r1.size(), 2);
	EXPECT_TRUE(allEmpty(r1));
	EXPECT_EQ(r2.size(), 3);
	EXPECT_TRUE(allEmpty(r2));
	EXPECT_TRUE(allEmpty(r3));
}

} // namespace _split
