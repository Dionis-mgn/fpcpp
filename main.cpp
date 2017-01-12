#include <string>
#include <cstdint>
#include <iostream>
#include <functional>


std::string toString(uint32_t i)
{
	return std::to_string(i) + ", it's works\n";
}

uint32_t addThree(uint32_t i)
{
	return i + 3;
}

uint32_t addTwo(uint32_t i)
{
	return i + 2;
}

uint32_t multByFour(uint32_t i)
{
	return i * 4;
}

uint32_t mul(uint32_t x, uint32_t y)
{
	return x * y;
}

uint32_t one()
{
	return 1;
}

template<typename T>
struct function_trait;

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


/* MAIN */
int main()
{
	auto f1 = pipe(mul, addThree, multByFour, toString);
	auto f2 = pipe(addThree, multByFour, addTwo);
	std::cout << f1(5, 7) << std::endl  << f2(1) << std::endl;

	return 0;
}
