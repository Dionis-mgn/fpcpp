#ifndef FPCPP_COMMON_H_
#define FPCPP_COMMON_H_

#include "cpp17.h"

#include <tuple>
#include <type_traits>

namespace fpcpp
{
namespace impl
{

template< class, class = void_t<> >
struct has_type_member : std::false_type { };

template< class T >
struct has_type_member<T, void_t<typename T::type>> : std::true_type { };

template<size_t... Indexes>
struct IndexTuple
{
	using next = IndexTuple<Indexes..., sizeof...(Indexes)>;
};

template<size_t Num>
struct BuildIndexTuple
{
	using type = typename BuildIndexTuple<Num - 1>::type::next;
};

template<>
struct BuildIndexTuple<0>
{
	using type = IndexTuple<>;
};

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

template <typename, typename>
struct TupleConcat;

template <typename... Alist, typename... Blist>
struct TupleConcat<std::tuple<Alist...>, std::tuple<Blist...>>
{
	using type = std::tuple<Alist..., Blist...>;
};

template <typename, typename>
struct TuplePushBack;

template <typename... Args, typename T>
struct TuplePushBack<std::tuple<Args...>, T>
{
	using type = std::tuple<Args..., T>;
};

template <typename, typename>
struct TuplePushFront;

template <typename... Args, typename T>
struct TuplePushFront<std::tuple<Args...>, T>
{
	using type = std::tuple<T, Args...>;
};

} // namespace impl
} // namespace fpcpp

#endif // Include Guard
