#include <iostream>
#include <vector>

#include "fpcpp.h"
using namespace fpcpp;

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
		,debugPrint
	);

	const std::string testStr = "  all ,this,, , keywords, should,   ,,be printed"
	                            ", separately   , without trailing ws,,,Yep!    ";
	splitKeywords(testStr);

	return 0;
}
