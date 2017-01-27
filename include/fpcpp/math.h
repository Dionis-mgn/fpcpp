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

} // namespace fpcpp
