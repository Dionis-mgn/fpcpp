namespace fpcpp
{

template <typename ... ARGS>
inline bool F(ARGS ...)
{
	return false;
}

template <typename ... ARGS>
inline bool T(ARGS ...)
{
	return true;
}

namespace impl
{
	template <typename T>
	inline T identity(T t)
	{
		return t;
	}

	template <typename T, typename ... OTHER>
	inline T identity(T t, OTHER ...)
	{
		return t;
	}
}

//C++17 variant
//inline auto identity = [](auto v) { return v; };
inline decltype(auto) identity()
{
	return [](auto ... v)
	{
		return impl::identity(v...);
	};
}

namespace impl
{
	template <typename FUNC, typename ARG>
	inline decltype(auto) pipe(ARG &&arg, FUNC func)
	{
		return func(std::forward<ARG>(arg));
	}

	template <typename FUNC, typename ARG, typename ... OTHER>
	inline decltype(auto) pipe(ARG &&arg, FUNC func, OTHER ... other)
	{
		return pipe(func(std::forward<ARG>(arg)), other...);
	}
} // namespace impl

template <typename FIRST, typename ... OTHER>
inline decltype(auto) pipe(FIRST first, OTHER ... other)
{
	return [first, other...](auto&& ... args) mutable
	{
		return impl::pipe(first(std::forward<decltype(args)>(args)...), other...);
	};
}

} // namespace fpcpp
