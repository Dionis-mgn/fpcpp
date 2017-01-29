#include "function_trait.h"

namespace fpcpp
{

template <template<typename...> class T, typename F, typename ...T_ARGS>
inline decltype(auto) map(F f, const T<T_ARGS...> &t)
{
	using f_result_type = decltype(f(*t.begin()));
	using result_t = T<f_result_type>;
	result_t result;

	for (auto &i : t)
		result.push_back(f(i));

	return result;
}

template <typename F>
inline decltype(auto) map(F f)
{
	return [f](const auto &t)
	{
		return map(f, t);
	};
}

inline decltype(auto) map()
{
	return [](auto... f)
	{
		return map(std::forward<decltype(f)>(f)...);
	};
}

template <template<typename...> class T, typename F, typename ...T_ARGS>
inline decltype(auto) filter(F f, const T<T_ARGS...> &t)
{
	using f_result_type = decltype(f(*t.begin()));
	static_assert(std::is_same<f_result_type, bool>::value, "Functional object should return a bool");

	using value_type = typename std::decay<decltype(t)>::type::value_type;
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
inline decltype(auto) filter(F f)
{
	return [f](const auto &t)
	{
		return filter(f, t);
	};
}

inline decltype(auto) filter()
{
	return [](auto&&... t)
	{
		return filter(std::forward<decltype(t)>(t)...);
	};
}

template <typename T, typename F>
inline decltype(auto) reject(F f, const T &t)
{
	return filter(complement(f), t);
}

template <typename F>
inline decltype(auto) reject(F f)
{
	return [f](const auto &t)
	{
		return reject(f, t);
	};
}

inline decltype(auto) reject()
{
	return [](auto&&... t)
	{
		return reject(std::forward<decltype(t)>(t)...);
	};
}

namespace impl
{
	template <typename F, typename ACC, typename CONTAINER>
	inline void call_reducer(F &f, ACC &acc, const CONTAINER &container, std::false_type)
	{
		for (auto &i : container)
			f(i, acc);
	}

	template <typename F, typename ACC, typename CONTAINER>
	inline void call_reducer(F &f, ACC &acc, const CONTAINER &container, std::true_type)
	{
		for (auto &i : container)
			acc = f(i, acc);
	}

	template< class, class = std::void_t<> >
	struct has_type_member : std::false_type { };

	template< class T >
	struct has_type_member<T, std::void_t<typename T::type>> : std::true_type { };
}

template <typename F, typename ACC, typename CONTAINER>
inline ACC reduce(F f, ACC acc, const CONTAINER &container)
{
	using reducer_return_type = typename std::result_of<
			F(decltype(*container.begin()),
			typename std::add_lvalue_reference<ACC>::type)
		>::type;
	using assig_call_avaliable = typename std::is_convertible<reducer_return_type, ACC>::type;
	using reducer_captures_acc_nonref = typename impl::has_type_member<
			typename std::result_of<F(decltype(*container.begin()), ACC)>
		>::type;
	static_assert(assig_call_avaliable()() || !reducer_captures_acc_nonref()(),
	"Reducer should return new value of accumulator OR capture it as non-const reference argument");

	impl::call_reducer(f, acc, container, assig_call_avaliable ());

	return acc;
}

template <typename F, typename ACC>
inline decltype(auto) reduce(F f, ACC acc)
{
	return [f, acc](const auto &container)
	{
		return reduce(f, acc, container);
	};
}

template <typename F>
inline decltype(auto) reduce(F f)
{
	return [f](auto&&... args)
	{
		return reduce(f, std::forward<decltype(args)>(args)...);
	};
}

inline decltype(auto) reduce()
{
	return [](auto&&... args)
	{
		return reduce(std::forward<decltype(args)>(args)...);
	};
}

} // namespace fpcpp
