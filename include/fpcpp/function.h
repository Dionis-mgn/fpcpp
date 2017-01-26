namespace fpcpp
{

template <typename ... ARGS>
bool F(ARGS ...)
{
	return false;
}

template <typename ... ARGS>
bool T(ARGS ...)
{
	return true;
}

//C++17 variant
//inline auto identity = [](auto v) { return v; };
decltype(auto) identity()
{
	return [](auto v)
	{
		return v;
	};
}

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

} // namespace fpcpp
