#include <string>
#include <vector>

namespace fpcpp
{

std::vector<std::string> split(std::string::value_type separator, const std::string &source)
{
	std::vector<std::string> result;

	// creepy, but pretty effective implementation. No FP at all.
	auto start = source.data();
	auto end = start + source.size();
	auto curr = start;

	while (curr < end)
	{
		if (*curr != separator)
		{
			curr++;
			continue;
		}
		result.emplace_back(start, curr - start);
		start = ++curr;
	}
	result.emplace_back(start, curr - start);

	return result;
}

template <std::string::value_type SEPARATOR>
std::vector<std::string> split(const std::string &source)
{
	return split(SEPARATOR, source);
}

decltype(auto) split(std::string::value_type separator)
{
	return [separator](const std::string &source)
	{
		return split(separator, source);
	};
}

// trim from start
static inline std::string ltrim(const std::string &s) {
	auto i = s.begin();
	while (i != s.end() && std::isspace(*i)) i++;

	return std::string (i, s.end());
}

// trim from end // TODO: Fix bug
static inline std::string rtrim(const std::string &s) {
	auto i = s.end();

	if (i == s.begin())
		return "";

	do
	{
		i--;
	}
	while (i != s.begin() && std::isspace(*i));

	return std::string (s.begin(), i);
}

// trim from both ends
static inline std::string trim(const std::string &s) {
	auto is = s.begin();
	while (is != s.end() && std::isspace(*is)) is++;

	if (is == s.end())
		return "";

	auto ie = s.end();
	do
	{
		ie--;
	}
	while (std::isspace(*ie));

	return std::string (is, ie + 1);
}

} // namespace fpcpp
