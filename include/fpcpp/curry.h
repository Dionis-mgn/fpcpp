#ifndef FPCPP_CURRY_H_
#define FPCPP_CURRY_H_

#include <functional>

#include "cpp17.h"
#include "common.h"

namespace fpcpp
{

namespace impl
{
	template <typename ... AccArgs>
	struct TupleMergerer
	{
		template <typename ... NewArgs>
		struct TypeMerger
		{
			template <size_t PLACE, typename T>
			struct PlaceholderReplacer
			{
				using type = typename std::tuple_element<PLACE - 1, std::tuple<NewArgs...>>::type;
			};

			template <typename T>
			struct PlaceholderReplacer <0, T>
			{
				using type = T;
			};

			template <typename T>
			struct TypeSelector
			{
				static constexpr int place = std::is_placeholder<T>::value;
				using type = typename PlaceholderReplacer<place, T>::type;
			};

			using type = typename std::tuple<typename TypeSelector<AccArgs>::type...>;
		};

		template <int PLACE>
		struct TupleElement
		{
			template <size_t I, typename ... NewArgs>
			static decltype(auto) _getTupleElement(const std::tuple<AccArgs...> &, const std::tuple<NewArgs...> &_new, std::true_type)
			{
				return std::get<PLACE - 1>(_new);
			}

			template <size_t I, typename ... NewArgs>
			static decltype(auto) _getTupleElement(const std::tuple<AccArgs...> &acc, const std::tuple<NewArgs...> &, std::false_type)
			{
				return std::get<I>(acc);
			}
		};

		template <size_t I, typename ... NewArgs>
		static decltype(auto) getTupleElement(const std::tuple<AccArgs...> &acc, const std::tuple<NewArgs...> &_new)
		{
			using element_type = typename std::tuple_element<I, std::tuple<AccArgs...>>::type;
			constexpr int place = std::is_placeholder<element_type>::value;
			using placeholder = typename std::conditional<place != 0, std::true_type, std::false_type>::type;

			return TupleElement<place>::template _getTupleElement<I> (acc, _new, placeholder());
		}

		template <typename ... NewArgs, std::size_t ... Indexes>
		static decltype(auto) mergeTuples(const std::tuple<AccArgs...> &acc
		                                 ,const std::tuple<NewArgs...> &_new
		                                 ,IndexTuple<Indexes...>)
		{
			return typename TypeMerger<NewArgs...>::type(getTupleElement<Indexes>(acc, _new)...);
		}
	};

	template <typename>
	struct NoPlaceholders;

	template <typename ... ARGS>
	struct NoPlaceholders<std::tuple<ARGS...>>
	{
		using negType = typename disjunction<std::is_placeholder<ARGS>...>::type;
		using type = typename negation<negType>::type;
	};

	// Final call of curried function
	template <typename F, typename ... ARGS, std::size_t... Indexes>
	decltype(auto) applyTuple(F f, std::tuple<ARGS...> args, IndexTuple<Indexes...>, std::true_type)
	{
		return f(std::get<Indexes>(args)...);
	}

	// There are still placeholders in arg list. Generate new function.
	template <typename F, typename ... ARGS, std::size_t... Indexes>
	decltype(auto) applyTuple(F f, std::tuple<ARGS...> args, IndexTuple<Indexes...>, std::false_type)
	{
		return [f, args](auto ... cArgs)
		{
			using index_type = typename impl::BuildIndexTuple<sizeof...(ARGS)>::type;
			std::tuple<decltype(cArgs)...> cTuple(cArgs...);
			auto newTuple = TupleMergerer<ARGS...>::mergeTuples(args, cTuple, index_type());
			using noPH = typename NoPlaceholders<decltype(newTuple)>::type;

			return applyTuple(f, newTuple, index_type(), noPH()); // std::move?
		};
	}
}

template <typename F, typename ... ARGS>
decltype(auto) curry(F f, ARGS... args)
{
	std::tuple<decltype(args)...> tuple(args...);

	return [f, tuple{std::move(tuple)}](auto... cArgs)
	{
		using index_type = typename impl::BuildIndexTuple<sizeof...(ARGS)>::type;
		std::tuple<decltype(cArgs)...> cTuple(cArgs...);
		auto newTuple = impl::TupleMergerer<ARGS...>::mergeTuples(tuple, cTuple, index_type());
		using noPH = typename impl::NoPlaceholders<decltype(newTuple)>::type;

		return impl::applyTuple(f, newTuple, index_type(), noPH()); // std::move?
	};
}

}

#endif
