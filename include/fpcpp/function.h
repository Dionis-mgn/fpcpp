namespace fpcpp
{

inline decltype(auto) F()
{
	return [](auto...)
	{
		return false;
	};
}

inline decltype(auto) T()
{
	return [](auto...)
	{
		return true;
	};
}

template <typename T>
inline decltype(auto) always(const T &value)
{
	return [value](auto&& ...)
	{
		return value;
	};
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

template <typename F, typename T>
inline T tap(F &&f, T &&t)
{
	using cT = typename std::add_const<T>::type;

	f(static_cast<cT>(t));
	return t;
}

template <typename F>
inline decltype(auto) tap(F f)
{
	return [f](auto && t)
	{
		f(t);
		return t;
	};
}

inline decltype(auto) tap()
{
	return [](auto&&... args)
	{
		return tap(std::forward<decltype(args)>(args)...);
	};
}

} // namespace fpcpp
