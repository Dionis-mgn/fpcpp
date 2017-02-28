#include <algorithm>
#include <atomic>
#include <cstdint>
#include <functional>
#include <iostream>
#include <string>

#include "fpcpp.h"
using namespace fpcpp;

int main()
{
	using namespace std::placeholders;

	auto mulL = [](int i, int j, int k, int m) { return i * j * k * m; };

	auto curried = curry(mulL, 3, _1, 4, _2);
	std::cout << curried(5, 2) << std::endl
	          << curried(1, _3)(false, "IBM", 2)
	          << std::endl // false and "IBM" arguments will be ignored
	          << curried(1)(3) << std::endl
	  //      << curried(1)(4, false, "IBM") << std::endl // Too many arguments.
	  //                                                     Won't compile.
	  ;

	return 0;
}
