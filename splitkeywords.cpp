#include <iostream>
#include <functional>

#include "pipe.h"
#include "fp.h"

int main()
{
	auto splitByComma = [](std::string s){ return split(',', s); };

	auto debugPrint = [](std::vector<std::string> v)
	{
		std::cout << "---VECTOR---" << std::endl;
		for (auto &i : v)
			std::cout << i << std::endl;
		std::cout << "------------" << std::endl;
		return v;
	};

	auto splitKeywords = pipe(
		splitByComma
		,debugPrint
		,mapper(trim)
		,debugPrint
		,rejecter(is_empty)
		,debugPrint
	);

	std::vector<std::string> result = splitKeywords("test, ,  aa,,,   ,, WHATH?");

	return 0;
}
