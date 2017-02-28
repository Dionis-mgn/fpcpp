#include <gtest/gtest.h>

#include <vector>

#include "fpcpp.h"
using namespace fpcpp;

namespace _all
{

auto eq3     = [](uint32_t v) { return v == 3; };
auto isFalse = [](bool b) { return !b; };

using c_t  = std::vector<uint32_t>;
using bc_t = std::vector<bool>;

TEST(all, returns_true_if_all_args_passed_pred)
{
	EXPECT_TRUE(all(eq3, c_t{3, 3, 3, 3}));
	EXPECT_TRUE(all(eq3)(c_t{3, 3, 3, 3}));

	EXPECT_TRUE(all(isFalse)(bc_t{false, false, 0}));
}

TEST(all, returns_false_if_any_args_failed_pred)
{
	EXPECT_FALSE(all(eq3, c_t{3, 1, 3, 3}));
	EXPECT_FALSE(all(eq3)(c_t{3, 1, 3, 3}));
}

TEST(all, returns_true_on_empty_container)
{
	EXPECT_TRUE(all(eq3, c_t{}));
	EXPECT_TRUE(all(eq3)(c_t{}));
}

} // namespace _all
