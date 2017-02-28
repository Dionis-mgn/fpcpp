#ifndef FPCPP_PLACEHOLDER_H_
#define FPCPP_PLACEHOLDER_H_

#include <cstddef>
#include <functional>
#include <type_traits>

namespace fpcpp
{

template <int N>
struct Placeholder : public std::integral_constant<int, N>
{
	Placeholder()
	{
	}
	template <typename T,
	          typename = std::enable_if_t<std::is_placeholder<T>::value == N>>
	Placeholder(const T &)
	{
	}
};

template <typename T>
struct PlaceholderConverter
{
	static constexpr int value = std::is_placeholder<T>::value;
	static_assert(value > 0, "Placeholder expected as template argument");

	using type = Placeholder<value>;
};

template <typename T>
inline decltype(auto)
toPlaceholder(const T &t,
              std::enable_if_t<std::is_placeholder<T>::value != 0> * = 0)
{
	return Placeholder<std::is_placeholder<T>::value>();
}

template <typename T>
inline T
toPlaceholder(T &&t, std::enable_if_t<std::is_placeholder<T>::value == 0> * = 0)
{
	return t;
}

} // namespace fpcpp

namespace std
{

template <int N>
struct is_placeholder<fpcpp::Placeholder<N>> : std::integral_constant<int, N>
{
	operator int()
	{
		return decltype(*this)::value;
	}
	int operator()()
	{
		return decltype(*this)::value;
	}
};

} // namespace std

#endif // Include Guard
