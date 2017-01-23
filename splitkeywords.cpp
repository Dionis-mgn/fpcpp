#include <iostream>
#include <functional>

#include <ctime>

#include "pipe.h"
#include "fp.h"
#include "stringutils.h"
std::vector<std::string> nativeSplit(const std::string source)
{
	std::vector<std::string> result;

	auto v = split(',', source);
	for (auto &i : v)
	{
		std::string trimmed = trim(i);
		if (!i.empty())
			result.push_back(i);
	}

	return result;
}

int main()
{
	std::string testStr = "test, ,  aa,,,   ,, WHATH?";
	using keywordList = std::vector<std::string>;

	auto debugPrint = [](std::vector<std::string> v)
	{
		std::cout << "---VECTOR---" << std::endl;
		for (auto &i : v)
			std::cout << i << std::endl;
		std::cout << "------------" << std::endl;
		return v;
	};

	auto splitByComma = [](std::string s){ return split(',', s); };

	auto splitKeywords1 = pipe(
		splitByComma
		,map(trim)
		,reject(is_empty)
	);

	auto valueFormatter = [](std::string value, keywordList &accumulator)
	{
		value = trim(value);
		if (!value.empty())
			accumulator.push_back(value);
	};

	keywordList acc;

	auto splitKeywords2 = pipe(
		splitByComma
		,reduce(valueFormatter, acc)
	);

#define FUNC splitKeywords2

	for (uint32_t i = 0; i < 500; i++)
		FUNC(testStr);

	auto start = clock();
	for (uint32_t i = 0; i < 5000000; i++)
		FUNC(testStr);
	auto end = clock();
	std::cout << ((float)(end - start) * 1000) / CLOCKS_PER_SEC << std::endl;

	return 0;
}
