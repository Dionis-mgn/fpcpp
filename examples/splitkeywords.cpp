/*******************************************************************************
 * FPCPP Example — Split Keywords
 *
 *  This example shows two ways to parse comma-separated text
 * as a set of keywords/tags using FPCPP. "a,b,c" -> "a","b","c".
 ******************************************************************************/

#include <iostream>
#include <vector>

#include "fpcpp.h"
using namespace fpcpp;

using keywordList = std::vector<std::string>;

int main()
{
	/* DEBUG PRINT
	 * The only purpose of this function - print some collectioon to STDOUT. */
	auto printContainer = [](const auto &v) {
		std::cout << "---CONTAINER---" << std::endl;
		for (auto &i : v)
			std::cout << i << std::endl;
		std::cout << "---------------" << std::endl;

		return v;
	};

	/* TWO PASSES VERSION
	 * It splits string to collection of substrings and iterate it twice.
	 * First time it trims each of the substring and second time it removes all
	 * empty substrings.
	 * So, performance is not as good as it may be. Still, this implementation is
	 * pretty easy.*/
	auto splitKeywords_twoPasses =
	  pipe(split(','), map(trim), reject(is_empty()), printContainer);

	/* This variant is also correct (there are no printContainer in pipe call):
	auto splitKeywords = pipe(split(','), map(trim), reject(is_empty()));
	printContainer(splitKeywords("some,data, string,")); */

	/* ONE PASS VERSION
	 * This version splits string to collection of substrings and uses reduce to
	 * trim and reject empty substrings in one pass.
	 * This version looks much uglier (in the main because I have to implement
	 * reducer — valueFormatter function) but at the same time it is much faster.
	 */
	auto valueFormatter = [](const std::string &value, keywordList &accumulator) {
		std::string trimmed = trim(value);
		if (!trimmed.empty())
			accumulator.push_back(trimmed);
	};

	keywordList acc;

	auto splitKeywords_onePass =
	  pipe(split(','), reduce(valueFormatter, acc), printContainer);

	/* TEST DATA */
	const std::string testStr = "  all ,this,, , keywords, will,   ,,be printed"
	                            ", separately   , without trailing ws,,,Yep!    ";

	/* CALLS TO FUNCTIONS */
	std::cout << "Two Passes version:\n" << std::endl;
	splitKeywords_twoPasses(testStr);
	std::cout << "\nOne Pass version:\n" << std::endl;
	splitKeywords_onePass(testStr);

	return 0;
}
