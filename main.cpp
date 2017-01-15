#include <algorithm>
#include <atomic>
#include <cstdint>
#include <functional>
#include <iostream>
#include <string>

#include "pipe.h"

std::string toString(uint32_t i)
{
	return std::to_string(i) + ", it's works";
}

uint32_t addThree(uint32_t i)
{
	return i + 3;
}

uint32_t addTwo(uint32_t i)
{
	return i + 2;
}

uint32_t multByFour(uint32_t i)
{
	return i * 4;
}

uint32_t mul(uint32_t x, uint32_t y)
{
	return x * y;
}

uint32_t one()
{
	return 1;
}

int main()
{
	auto mulLambda = [](int i, int j) { return i * j; };

	auto f1 = pipe(
						mulLambda,
						addThree
					);

	auto f2 = pipe(
						mul,
						addThree,
						multByFour,
						toString
					);

	auto f3 = pipe(
						[](uint32_t i) {
							static std::atomic<uint32_t> counter = { 0 };
							std::cout << "COUNTER = " << ++counter << " value = " << i << std::endl;
							return i;
						},
						multByFour,
						toString,
						[](std::string in) {
							std::transform(in.begin(), in.end(), in.begin(), ::toupper);
							return in;
						}
					);

	std::cout
		<< f3(5)    << std::endl // 20   +STR
		<< f1(5, 7) << std::endl // 38
		<< f2(1, 5) << std::endl // 32   +str
		<< f3(7)    << std::endl // 28   +STR
		<< f3(15)   << std::endl // 60   +STR
		<< f3(523)  << std::endl // 2092 +STR
		<< f3(45)   << std::endl // 180  +STR
		;

	return 0;
}
