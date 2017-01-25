#include <algorithm>
#include <iterator>
#include <sstream>
#include <type_traits>
#include <vector>

/*******************************************************************************
*                                                                        COMMON
*******************************************************************************/

template <typename ... ARGS>
bool F(ARGS ...)
{
	return false;
}

template <typename ... ARGS>
bool T(ARGS ...)
{
	return true;
}

//C++17 variant
//inline auto identity = [](auto v) { return v; };
decltype(auto) identity()
{
	return [](auto v)
	{
		return v;
	};
}

template <typename T>
T add(T x, T y)
{
	return x + y;
}

template <typename T>
decltype(auto) add(T x)
{
	return [x](T y)
	{
		return x + y;
	};
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
decltype(auto) map(F f)
{
	return [f](const auto &t)
	{
		return map(f, t);
	};
}

template <template<typename...> typename T, typename F, typename ...T_ARGS>
decltype(auto) filter(F f, const T<T_ARGS...> &t)
{
	using f_result_type = decltype(f(*t.begin()));
	using value_type = typename std::decay<decltype(t)>::type::value_type;
	static_assert(std::is_same<f_result_type, bool>::value, "Functional object should return a bool");
	using result_t = T<value_type>;
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
	return [f](auto &&arg)
	{
		return !f(std::forward<decltype(arg)>(arg));
	};
}

template <typename T, typename F>
decltype(auto) reject(F f, const T &t)
{
	return filter(nnot(f), t);
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

template <typename FUNC, typename ARG>
decltype(auto) pipe_impl(ARG &&arg, FUNC func)
{
	return func(std::forward<ARG>(arg));
}

template <typename FUNC, typename ARG, typename ... OTHER>
decltype(auto) pipe_impl(ARG &&arg, FUNC func, OTHER ... other)
{
	return pipe_impl(func(std::forward<ARG>(arg)), other...);
}

template <typename FIRST, typename ... OTHER>
decltype(auto) pipe(FIRST first, OTHER ... other)
{
	return [first, other...](auto&& ... args)
	{
		return pipe_impl(first(std::forward<decltype(args)>(args)...), other...);
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
