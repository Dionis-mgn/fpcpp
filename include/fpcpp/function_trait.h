#include <tuple>
#include <type_traits>

namespace fpcpp
{

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

} // namespace fpcpp
