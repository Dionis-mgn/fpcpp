#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

#include <string>

#include "fpcpp.h"
using namespace fpcpp;

namespace _trim
{

RC_GTEST_PROP(trim, first_last_chars_not_spaces, (const std::string &src))
{
	std::string fromBegin = trimB(src);
	std::string fromEnd = trimE(src);
	std::string full = trim(src);

	if (full.empty())
	{
		RC_TAG("Empty after trimming");

		RC_ASSERT(fromBegin.empty());
		RC_ASSERT(fromEnd.empty());
		RC_ASSERT(full.empty());

		return;
	}

	RC_ASSERT_FALSE(std::isspace(fromBegin.front()));
	RC_ASSERT_FALSE(std::isspace(fromEnd.back()));
	RC_ASSERT_FALSE(std::isspace(full.front()));
	RC_ASSERT_FALSE(std::isspace(full.back()));
}

TEST(trim, empty_string)
{
	EXPECT_EQ(trim(""), "");
	EXPECT_EQ(trimB(""), "");
	EXPECT_EQ(trimE(""), "");
}

TEST(trim, single_word)
{
	std::string src = "  test  ";

	EXPECT_EQ(trim(src), "test");
	EXPECT_EQ(trimB(src), "test  ");
	EXPECT_EQ(trimE(src), "  test");
}

TEST(trim, all_spaces)
{
	std::string src = "     ";

	EXPECT_EQ(trim(src), "");
	EXPECT_EQ(trimB(src), "");
	EXPECT_EQ(trimE(src), "");
}

TEST(trim, phrase)
{
	std::string src = "  leave spaces between us, please  ";

	EXPECT_EQ(trim(src), "leave spaces between us, please");
	EXPECT_EQ(trimB(src), "leave spaces between us, please  ");
	EXPECT_EQ(trimE(src), "  leave spaces between us, please");
}

TEST(trim, tabulation)
{
	std::string src = "\t \vleave spaces between us, please\v \t";

	EXPECT_EQ(trim(src), "leave spaces between us, please");
	EXPECT_EQ(trimB(src), "leave spaces between us, please\v \t");
	EXPECT_EQ(trimE(src), "\t \vleave spaces between us, please");
}

} // namespace _trim
