#ifndef FPCPP_MATH_H_
#define FPCPP_MATH_H_

#include <functional>
#include <type_traits>
#include <utility>

#include "curry.h"

namespace fpcpp
{
#define DECLARE_BINARY_OP(_name_, _op_)                                        \
                                                                               \
	/* Basic version */                                                          \
	template <typename T1, typename T2>                                          \
	inline decltype(auto) _name_(                                                \
	  T1 a, T2 b,                                                                \
	  typename std::enable_if_t<                                                 \
	    std::is_placeholder<typename std::decay_t<T1>>::value == 0 &&            \
	    std::is_placeholder<typename std::decay_t<T2>>::value == 0> * = 0)       \
	{                                                                            \
		return a _op_ b;                                                           \
	}                                                                            \
                                                                               \
	/* First argument is curried (ex.: auto gt10 = gt(_1, 10); ) */              \
	template <typename T1, typename T2>                                          \
	inline decltype(auto) _name_(                                                \
	  T1, T2 &&b,                                                                \
	  typename std::enable_if_t<                                                 \
	    std::is_placeholder<typename std::decay_t<T1>>::value == 1 &&            \
	    std::is_placeholder<typename std::decay_t<T2>>::value == 0> * = 0)       \
	{                                                                            \
		return [b{std::forward<decltype(b)>(b)}](auto a)                           \
		{                                                                          \
			return a _op_ b;                                                         \
		};                                                                         \
	}                                                                            \
                                                                               \
	/* General curried versioon (ex.: auto strangeGt = gt(_4, _10); ) */         \
	template <typename T1, typename T2>                                          \
	inline decltype(auto) _name_(                                                \
	  T1 &&a, T2 &&b,                                                            \
	  typename std::enable_if_t<                                                 \
	    std::is_placeholder<typename std::decay_t<T1>>::value >= 2 ||            \
	    std::is_placeholder<typename std::decay_t<T2>>::value != 0> * = 0)       \
	{                                                                            \
		return curry(                                                              \
		  [](auto &&... args) {                                                    \
			  return _name_(std::forward<decltype(args)>(args)...);                  \
		  },                                                                       \
		  std::forward<decltype(a)>(a), std::forward<decltype(b)>(b));             \
	}                                                                            \
                                                                               \
	/* Second argument is curried (ex.: auto xGreatThan = gt(x); ) */            \
	template <typename T1>                                                       \
	inline decltype(auto) _name_(T1 &&a)                                         \
	{                                                                            \
		return [a{std::forward<decltype(a)>(a)}](auto b)                           \
		{                                                                          \
			return _name_(a, b);                                                     \
		};                                                                         \
	}                                                                            \
                                                                               \
	/* Auto-curried version */                                                   \
	inline decltype(auto) _name_()                                               \
	{                                                                            \
		return [](auto &&... args) { return _name_(args...); };                    \
	}

DECLARE_BINARY_OP(gt, >);
DECLARE_BINARY_OP(gte, >=);
DECLARE_BINARY_OP(lt, <);
DECLARE_BINARY_OP(lte, <=);
DECLARE_BINARY_OP(equals, ==);
DECLARE_BINARY_OP(add, +);
DECLARE_BINARY_OP(subtract, -);
DECLARE_BINARY_OP(multiply, *);
DECLARE_BINARY_OP(divide, /);

#undef DECLARE_BINARY_OP

} // namespace fpcpp

#endif // Include Guard
