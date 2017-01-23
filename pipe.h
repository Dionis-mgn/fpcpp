#include <tuple>
#include <type_traits>

template <typename FUNC, typename ARG>
decltype(auto) wrap_impl(ARG &&arg, FUNC func)
{
	return func(std::forward<ARG>(arg));
}

template <typename FUNC, typename ARG, typename ... OTHER>
decltype(auto) wrap_impl(ARG &&arg, FUNC func, OTHER ... other)
{
	return wrap_impl(func(std::forward<ARG>(arg)), other...);
}

template<typename T>
struct function_trait;

template <typename RESULT, typename ... ARGS>
struct function_trait_impl
{
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
		return [func, other...](auto&&... args) mutable
		{
			return wrap_impl(func(std::forward<decltype(args)>(args)...), other...);
		};
	}
};

template <typename RESULT, typename ... ARGS>
struct function_trait<RESULT(ARGS...)> :
	public function_trait_impl<RESULT, ARGS...>
{ };

template <typename RESULT, typename TYPE, typename ... ARGS>
struct function_trait<RESULT(TYPE::*)(ARGS...)> :
	public function_trait_impl<RESULT, ARGS...>
{ };

template <typename RESULT, typename TYPE, typename ... ARGS>
struct function_trait<RESULT(TYPE::*)(ARGS...) const> :
	public function_trait_impl<RESULT, ARGS...>
{ };

template <
	typename FIRST,
	typename ... OTHER,
	typename RAWFUNC = typename std::remove_pointer<FIRST>::type
>
decltype(auto) pipe_impl(FIRST first, std::true_type, OTHER ... other)
{
	return function_trait<RAWFUNC>::wrap(first, other...);
}

template <
	typename FIRST,
	typename ... OTHER,
	typename FUNCOBJ = decltype(&FIRST::operator()),
	typename = typename std::enable_if<std::is_member_function_pointer<FUNCOBJ>::value>::type
>
decltype(auto) pipe_impl(FIRST first, std::false_type, OTHER ... other)
{
	return function_trait<FUNCOBJ>::wrap(first, other...);
}

template <
	typename FIRST,
	typename ... OTHER,
	typename RAWFUNC = typename std::remove_pointer<FIRST>::type
>
decltype(auto) pipe(FIRST first, OTHER ... other)
{
	return pipe_impl(first, std::is_function<RAWFUNC>(), other...);
}
