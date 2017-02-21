#include <gtest/gtest.h>

#include <vector>

#include "fpcpp.h"
using namespace fpcpp;

namespace _any {

auto eq3 = [](uint32_t v) { return v == 3; };
auto isFalse = [](bool b) { return !b; };

using c_t = std::vector<uint32_t>;
using bc_t = std::vector<bool>;

TEST(any, returns_true_if_any_args_passed_pred)
{
	EXPECT_TRUE ( any(eq3, c_t{0, 0, 3, 0}) );
	EXPECT_TRUE ( any(eq3)(c_t{0, 0, 3, 0}) );

	EXPECT_TRUE ( any(isFalse)(bc_t{false, true, 0}) );
}

TEST(any, returns_false_if_all_args_failed_pred)
{
	EXPECT_FALSE( any(eq3, c_t{1, 1, 1, 1}) );
	EXPECT_FALSE( any(eq3)(c_t{1, 1, 1, 1}) );
}

TEST(any, returns_false_on_empty_container)
{
	EXPECT_FALSE( any(eq3, c_t{}) );
	EXPECT_FALSE( any(eq3)(c_t{}) );
}

} // namespace _any
