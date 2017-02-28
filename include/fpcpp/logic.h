#ifndef FPCPP_LOGIC_H_
#define FPCPP_LOGIC_H_

#include <utility>

namespace fpcpp
{

template <typename F1, typename F2>
inline decltype(auto) both(F1 f1, F2 f2)
{
	return [f1, f2](auto &&... args) {
		auto res1 = f1(args...);
		if (!res1)
			return res1;
		return f2(args...);
	};
}

template <typename F>
inline decltype(auto) complement(F f)
{
	return
	  [f](auto &&... args) { return !f(std::forward<decltype(args)>(args)...); };
}

inline decltype(auto) complement()
{
	return [](auto &&... args) {
		return complement(std::forward<decltype(args)>(args)...);
	};
}

inline decltype(auto) Not()
{
	return [](const auto &arg) { return !arg; };
}

// C++17 variant
// inline auto is_empty = [](const auto &obj) { return obj.empty(); };
inline decltype(auto) is_empty()
{
	return [](const auto &obj) { return obj.empty(); };
}

} // namespace fpcpp

#endif // Include Guard
