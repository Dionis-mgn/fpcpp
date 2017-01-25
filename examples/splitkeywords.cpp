#include <iostream>
#include <functional>

#include "fp.h"
#include "stringutils.h"

using keywordList = std::vector<std::string>;

int main()
{
	auto debugPrint = [](const auto &v)
	{
		std::cout << "---CONTAINER---" << std::endl;
		for (auto &i : v)
			std::cout << i << std::endl;
		std::cout << "---------------" << std::endl;

		return v;
	};

	auto valueFormatter = [](const std::string &value, keywordList &accumulator)
	{
		std::string trimmed = trim(value);
		if (!trimmed.empty())
			accumulator.push_back(trimmed);
	};

	keywordList acc;

	auto splitKeywords = pipe(
		split(',')
		,reduce(valueFormatter, acc)
		//,debugPrint
	);

	const std::string testStr = "test,aa,WHATH?,aa,WHATH?,aa, WHATH?,aa,  ,, WHATH?, ,  aa, WHATH?, ,  aa,  ,, WHATH?";
	splitKeywords(testStr);

	return 0;
}
