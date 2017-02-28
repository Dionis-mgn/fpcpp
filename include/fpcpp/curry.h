#ifndef FPCPP_CURRY_H_
#define FPCPP_CURRY_H_

#include <algorithm>
#include <functional>

#include "common.h"
#include "cpp17.h"
#include "placeholder.h"

namespace fpcpp
{

namespace impl
{
	template <typename... ACC_ARGS>
	struct TupleMergerer
	{
		template <typename... NEW_ARGS>
		struct TypeMerger
		{
			template <int PLACE, typename T>
			struct PlaceholderReplacer
			{
				template <typename COMPLETE, int DIFF>
				struct Impl;

				// We able to take argument from new arguiments
				template <int DIFF>
				struct Impl<std::true_type, DIFF>
				{
					using type = std::tuple_element_t<PLACE - 1, std::tuple<NEW_ARGS...>>;
				};

				// We have to wait argument even more
				template <int DIFF>
				struct Impl<std::false_type, DIFF>
				{
					using type = Placeholder<DIFF>;
				};

				static constexpr int new_args_length = sizeof...(NEW_ARGS);

				using complete_t = std::conditional_t<new_args_length >= PLACE,
				                                      std::true_type, std::false_type>;
				using type = typename Impl<complete_t, PLACE - new_args_length>::type;
			};

			template <typename T>
			struct PlaceholderReplacer<0, T>
			{
				using type = T;
			};

			template <typename T>
			struct TypeSelector
			{
				static constexpr int place = std::is_placeholder<T>::value;
				using type = typename PlaceholderReplacer<place, T>::type;
			};

			using type =
			  typename std::tuple<typename TypeSelector<ACC_ARGS>::type...>;
		};

		template <int PLACE>
		struct TupleElement
		{
			template <typename... NEW_ARGS>
			static decltype(auto) _getPlaceholder(const std::tuple<NEW_ARGS...> &_new,
			                                      std::true_type)
			{
				return std::get<PLACE - 1>(_new);
			}

			template <typename... NEW_ARGS>
			static decltype(auto) _getPlaceholder(const std::tuple<NEW_ARGS...> &_new,
			                                      std::false_type)
			{
				return Placeholder<PLACE - sizeof...(NEW_ARGS)>();
			}

			template <size_t I, typename... NEW_ARGS>
			static decltype(auto)
			_getTupleElement(const std::tuple<ACC_ARGS...> &,
			                 const std::tuple<NEW_ARGS...> &_new, std::true_type)
			{
				using complete_t = std::conditional_t<sizeof...(NEW_ARGS) >= PLACE,
				                                      std::true_type, std::false_type>;
				return _getPlaceholder<NEW_ARGS...>(_new, complete_t());
			}

			template <size_t      I, typename... NEW_ARGS>
			static decltype(auto) _getTupleElement(const std::tuple<ACC_ARGS...> &acc,
			                                       const std::tuple<NEW_ARGS...> &,
			                                       std::false_type)
			{
				return std::get<I>(acc);
			}
		};

		template <size_t      I, typename... NEW_ARGS>
		static decltype(auto) getTupleElement(const std::tuple<ACC_ARGS...> &acc,
		                                      const std::tuple<NEW_ARGS...> &_new)
		{
			using element_type  = std::tuple_element_t<I, std::tuple<ACC_ARGS...>>;
			constexpr int place = std::is_placeholder<element_type>::value;
			using placeholder =
			  std::conditional_t<place != 0, std::true_type, std::false_type>;

			return TupleElement<place>::template _getTupleElement<I>(acc, _new,
			                                                         placeholder());
		}

		template <typename... NEW_ARGS, std::size_t... Indexes>
		static decltype(auto) mergeTuples(const std::tuple<ACC_ARGS...> &acc,
		                                  const std::tuple<NEW_ARGS...> &_new,
		                                  IndexTuple<Indexes...>)
		{
			return typename TypeMerger<NEW_ARGS...>::type(
			  getTupleElement<Indexes>(acc, _new)...);
		}

		template <typename FIRST, typename... ARGS>
		struct MaxPlaceholder
		{
		private:
			static constexpr size_t fvalue = MaxPlaceholder<FIRST>::value;
			static constexpr size_t avalue = MaxPlaceholder<ARGS...>::value;

		public:
			static constexpr size_t value = std::max(fvalue, avalue);
		};

		template <typename ARG>
		struct MaxPlaceholder<ARG>
		{
			static constexpr size_t value = std::is_placeholder<ARG>::value;
		};

		static constexpr size_t expected_arity = MaxPlaceholder<ACC_ARGS...>::value;
	};

	template <typename>
	struct NoPlaceholders;

	template <typename... ARGS>
	struct NoPlaceholders<std::tuple<ARGS...>>
	{
		using negType = typename disjunction<std::is_placeholder<ARGS>...>::type;
		using type    = typename negation<negType>::type;
	};

	// Final call of curried function
	template <typename F, typename... ARGS, std::size_t... INDEXES>
	inline decltype(auto) do_curry(F f, std::tuple<ARGS...> args,
	                               IndexTuple<INDEXES...>, std::true_type)
	{
		return f(std::get<INDEXES>(args)...);
	}

	// There are still placeholders in arg list. Generate new function.
	template <typename F, typename... ARGS, std::size_t... INDEXES>
	inline decltype(auto) do_curry(F f, std::tuple<ARGS...> args,
	                               IndexTuple<INDEXES...>, std::false_type)
	{
		return [f, args](auto... curriedArgs) {
			static_assert(impl::TupleMergerer<ARGS...>::expected_arity >=
			                sizeof...(curriedArgs),
			              "Too many arguments for curried function");

			using index_type = typename impl::BuildIndexTuple<sizeof...(ARGS)>::type;
			std::tuple<decltype(curriedArgs)...> curriedTuple(curriedArgs...);
			auto                                 newTuple =
			  TupleMergerer<ARGS...>::mergeTuples(args, curriedTuple, index_type());
			using noPH = typename NoPlaceholders<decltype(newTuple)>::type;

			return do_curry(f, newTuple, index_type(), noPH()); // std::move?
		};
	}
} // namespace impl

template <typename F, typename... ARGS>
inline decltype(auto) curry(F f, ARGS... args)
{
	std::tuple<decltype(args)...> tuple(args...);
	using index_type = typename impl::BuildIndexTuple<sizeof...(ARGS)>::type;

	return impl::do_curry(f, std::move(tuple), index_type(), std::false_type());
}

} // namespace fpcpp

#endif
