#include <tuple>
#include <type_traits>

template<typename T>
struct function_trait;

template <typename RESULT, typename ... ARGS>
struct function_trait_impl
{
	using result_type = RESULT;
	using args_tuple_type = std::tuple<ARGS...>;

	static const size_t arity = sizeof...(ARGS);

	template <size_t i>
	struct arg
	{
		using type = typename std::tuple_element<i, std::tuple<ARGS...>>::type;
	};
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
