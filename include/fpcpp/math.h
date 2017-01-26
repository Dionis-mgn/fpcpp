namespace fpcpp
{

template <typename T>
inline T add(T x, T y)
{
	return x + y;
}

template <typename T>
inline decltype(auto) add(T x)
{
	return [x](T y)
	{
		return x + y;
	};
}

} // namespace fpcpp
