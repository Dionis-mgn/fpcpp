#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

#include <string>

#include "fpcpp.h"
using namespace fpcpp;

RC_GTEST_PROP(map,
	identityMapEqualsToOriginal,
	(const std::vector<std::string> &original))
{
	auto fn = map(identity());
	auto mapped = fn(original);
	RC_ASSERT(mapped == original);
}
