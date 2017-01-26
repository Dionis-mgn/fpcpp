#include <algorithm>
#include <atomic>
#include <cstdint>
#include <functional>
#include <iostream>
#include <string>

#include "fpcpp.h"
using namespace fpcpp;

std::string toString(uint32_t i)
{
	return std::to_string(i) + ", it's works";
}

uint32_t addThree(uint32_t i)
{
	return i + 3;
}

uint32_t multByFour(uint32_t i)
{
	return i * 4;
}

uint32_t mul(uint32_t x, uint32_t y)
{
	return x * y;
}

struct MulFunctor
{
	uint32_t operator () (uint32_t i, uint32_t j) { return i * j; }
};

struct AddThreeFunctor
{
	uint32_t operator () (uint32_t i) { return i + 3; }
};

int main()
{
	auto mulLambda = [](int i, int j) { return i * j; };
	MulFunctor mulFunctor;
	AddThreeFunctor addThreeFunctor;


	auto f1 = pipe(
		mulLambda,
		addThreeFunctor
	);

	auto f2 = pipe(
		mul,
		addThree,
		multByFour,
		toString
	);

	auto f3 = pipe(
		mulFunctor,
		addThree
	);

	auto f4 = pipe(
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

	auto f5 = pipe(
		mul,
		std::bind(mul, std::placeholders::_1, 2)
	);

	std::cout
		<< f1(5, 7) << std::endl // 38
		<< f2(1, 5) << std::endl // 32   +str
		<< f3(2, 2) << std::endl // 7
		<< f4(45)   << std::endl // 180  +STR
		<< f5(4,5)  << std::endl // 40
		;

	return 0;
}
