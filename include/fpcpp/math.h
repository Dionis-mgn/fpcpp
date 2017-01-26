namespace fpcpp
{

template <typename T>
T add(T x, T y)
{
	return x + y;
}

template <typename T>
decltype(auto) add(T x)
{
	return [x](T y)
	{
		return x + y;
	};
}

} // namespace fpcpp
