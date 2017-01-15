#include <tuple>

template <typename FUNC, typename ARG>
decltype(auto) wrap_impl(ARG arg, FUNC func)
{
	return func(arg);
}

template <typename FUNC, typename ARG, typename ... OTHER>
decltype(auto) wrap_impl(ARG arg, FUNC func, OTHER ... other)
{
	return wrap_impl(func(arg), other...);
}

template<typename T>
struct function_trait;

template <typename RESULT, typename ... ARGS>
struct function_trait<RESULT(*)(ARGS...)>
{
public:
	using result_type = RESULT;
	using args_tuple_type = std::tuple<ARGS...>;

	static const size_t nargs = sizeof...(ARGS);

	template <size_t i>
	struct arg
	{
		using type = typename std::tuple_element<i, std::tuple<ARGS...>>::type;
	};

	template <typename FUNC, typename ... OTHER>
	static decltype(auto) wrap(FUNC func, OTHER... other)
	{
		return [func, other...](ARGS... args)
		{
			return wrap_impl(func(args...), other...);
		};
	}
};


template <typename FIRST, typename ... OTHER>
decltype(auto) pipe(FIRST first, OTHER ... other)
{
	return function_trait<FIRST>::wrap(first, other...);
}
