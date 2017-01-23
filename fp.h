#include <algorithm>
#include <iterator>
#include <sstream>
#include <type_traits>
#include <vector>

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
decltype(auto) map(F f)
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
decltype(auto) filter(F f)
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
decltype(auto) reject(F f)
{
	return [f](const auto &t)
	{
		return reject(f, t);
	};
}

template <typename F, typename ACC, typename CONTAINER>
ACC reduce(F f, ACC acc, const CONTAINER &container)
{
	for (auto &i : container)
		f(i, acc);

	return acc;
}

template <typename F, typename ACC>
decltype(auto) reduce(F f, ACC acc)
{
	return [f, acc](const auto &container)
	{
		return reduce(f, acc, container);
	};
}

/*
template<typename F>
decltype(auto) into(auto container, F func, auto input)
{
	for (auto &i : input)
	{

	}
}
*/
