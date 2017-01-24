#include <iostream>
#include <functional>

#include <ctime>

#include "pipe.h"
#include "fp.h"
#include "stringutils.h"

using keywordList = std::vector<std::string>;

keywordList nativeSplit(const std::string &source)
{
	keywordList result;

	auto v = split(',', source);
	for (auto &i : v)
	{
		std::string trimmed = trim(i);
		if (!trimmed.empty())
			result.push_back(trimmed);
	}

	return result;
}

int main()
{
	const std::string testStr = "test, ,  aa,,,   ,, WHATH?";

	auto debugPrint = [](keywordList v)
	{
		std::cout << "---VECTOR---" << std::endl;
		for (auto &i : v)
			std::cout << i << std::endl;
		std::cout << "------------" << std::endl;
		return v;
	};

	auto splitByComma = [](const std::string &s){ return split(',', s); };

	auto splitKeywords1 = pipe(
		splitByComma
		,map(trim)
		,reject(is_empty)
	);

	auto valueFormatter = [](const std::string &value, keywordList &accumulator)
	{
		std::string trimmed = trim(value);
		if (!trimmed.empty())
			accumulator.push_back(trimmed);
	};

	keywordList acc;

	auto splitKeywords2 = pipe(
		split(',')
		,reduce(valueFormatter, acc)
	);

#define FUNC nativeSplit

	for (uint32_t i = 0; i < 500; i++)
		FUNC(testStr);

	auto start = clock();
	for (uint32_t i = 0; i < 5000000; i++)
		FUNC(testStr);
	auto end = clock();
	std::cout << ((float)(end - start) * 1000) / CLOCKS_PER_SEC << std::endl;

	return 0;
}
