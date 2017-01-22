#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include <type_traits>

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

template <typename T, typename F>
decltype(auto) map(F f, const T &t)
{
	using result_t = typename std::vector<decltype(f(*t.begin()))>;
	result_t result;

	for (auto &i : t)
		result.push_back(f(i));

	return result;
}

template <typename F>
decltype(auto) mapper(F f)
{
	return [f](const auto &t)
	{
		return map(f, t);
	};
}

template <typename T, typename F>
decltype(auto) filter(F f, const T &t)
{
	using f_result_type = decltype(f(*t.begin()));
	using value_type = typename T::value_type;
	static_assert(std::is_same<f_result_type, bool>::value, "Functional object should return a bool");
	using result_t = typename std::vector<value_type>;
	result_t result;

	for (auto &i : t)
	{
		if (f(i))
			result.push_back(i);
	}

	return result;
}

template <typename F>
decltype(auto) filterer(F f)
{
	return [f](const auto &t)
	{
		return filter(f, t);
	};
}

template <typename F>
decltype(auto) nnot(F f)
{
	return [f](auto arg)
	{
		return !f(arg);
	};
}

template <typename T, typename F>
decltype(auto) reject(F f, const T &t)
{
	auto functor = nnot(f);
	return filter(functor, t);
}

template <typename F>
decltype(auto) rejecter(F f)
{
	return [f](const auto &t)
	{
		return reject(f, t);
	};
}

bool is_empty(const std::string &s)
{
	return s.empty();
}
