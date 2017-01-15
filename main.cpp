#include <string>
#include <cstdint>
#include <iostream>
#include <functional>

#include "pipe.h"

std::string toString(uint32_t i)
{
	return std::to_string(i) + ", it's works\n";
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

/* MAIN */
int main()
{
	auto f1 = pipe(mul, addThree, multByFour, toString);
	auto f2 = pipe(addThree, multByFour, addTwo);
	std::cout << f1(5, 7) << std::endl  << f2(1) << std::endl;

	return 0;
}
