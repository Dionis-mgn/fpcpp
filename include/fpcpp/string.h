#ifndef FPCPP_STRING_H_
#define FPCPP_STRING_H_

#include <string>
#include <vector>

namespace fpcpp
{

inline std::vector<std::string> split(std::string::value_type separator,
                                      const std::string &     source)
{
	std::vector<std::string> result;

	// creepy, but pretty effective implementation. No FP at all.
	auto start = source.data();
	auto end   = start + source.size();
	auto curr  = start;

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
	if (curr > start)
		result.emplace_back(start, curr - start);
	else
		result.emplace_back("");

	return result;
}

template <std::string::value_type SEPARATOR>
inline std::vector<std::string> split(const std::string &source)
{
	return split(SEPARATOR, source);
}

inline decltype(auto) split(std::string::value_type separator)
{
	return
	  [separator](const std::string &source) { return split(separator, source); };
}

inline decltype(auto) split()
{
	return [](auto &&... args) {
		return split(std::forward<decltype(args)>(args)...);
	};
}

// trim from beginning
inline std::string trimB(const std::string &s)
{
	auto i = s.begin();
	while (i != s.end() && std::isspace(*i))
		i++;

	return std::string(i, s.end());
}

// trim from end
inline std::string trimE(const std::string &s)
{
	auto i = s.end();

	if (i == s.begin())
		return "";

	do
	{
		i--;
	} while (i != s.begin() && std::isspace(*i));

	if (std::isspace(*i))
		return "";

	return std::string(s.begin(), i + 1);
}

// trim from both ends
inline std::string trim(const std::string &s)
{
	auto is = s.begin();
	while (is != s.end() && std::isspace(*is))
		is++;

	if (is == s.end())
		return "";

	auto ie = s.end();
	do
	{
		ie--;
	} while (std::isspace(*ie));

	return std::string(is, ie + 1);
}

} // namespace fpcpp

#endif // Include Guard
