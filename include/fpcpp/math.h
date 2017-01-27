namespace fpcpp
{

template <typename T1, typename T2>
inline decltype(auto) add(T1 x, T2 y)
{
	return x + y;
}

template <typename T>
inline decltype(auto) add(T x)
{
	return [x](auto y)
	{
		return y + x;
	};
}

inline decltype(auto) add()
{
	return [](auto&&... x)
	{
		return add(std::forward<decltype(x)>(x)...);
	};
}

template <typename T1, typename T2>
inline decltype(auto) multiply(T1 x, T2 y)
{
	return x * y;
}

template <typename T>
inline decltype(auto) multiply(T x)
{
	return [x](auto y)
	{
		return y * x;
	};
}

inline decltype(auto) multiply()
{
	return [](auto&&... x)
	{
		return multiply(std::forward<decltype(x)>(x)...);
	};
}

} // namespace fpcpp
