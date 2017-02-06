#ifndef FPCPP_CPP17_H_
#define FPCPP_CPP17_H_

#include <type_traits>

/* Implementation of some C++17 STL fearures for C++14 compiler */

namespace fpcpp
{
namespace impl
{

template<typename...> struct conjunction : std::true_type { };
template<typename B1> struct conjunction<B1> : B1 { };
template<typename B1, typename... Bn>
struct conjunction<B1, Bn...>
	: std::conditional_t<bool(B1::value), conjunction<Bn...>, B1> {};

template<typename...> struct disjunction : std::false_type { };
template<typename B1> struct disjunction<B1> : B1 { };
template<typename B1, typename... Bn>
struct disjunction<B1, Bn...>
	: std::conditional_t<bool(B1::value), B1, disjunction<Bn...>>  { };

template <bool B>
using bool_constant = std::integral_constant<bool, B>;

template<typename B>
struct negation : bool_constant<!B::value> { };

template<typename... Ts> struct make_void { typedef void type;};
template<typename... Ts> using void_t = typename make_void<Ts...>::type;

} // namespace impl
} // namespace fpcpp

#endif // Include Guard
