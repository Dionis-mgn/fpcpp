namespace fpcpp
{

template <typename F>
inline decltype(auto) complement(F f)
{
	return [f](auto&&... arg)
	{
		return !f(std::forward<decltype(arg)>(arg)...);
	};
}

inline decltype(auto) complement()
{
	return [](auto&&... args)
	{
		return complement(std::forward<decltype(args)>(args)...);
	};
}

inline decltype(auto) Not()
{
	return [](const auto &arg)
	{
		return !arg;
	};
}

//C++17 variant
//inline auto is_empty = [](const auto &obj) { return obj.empty(); };
inline decltype(auto) is_empty()
{
	return [](const auto &obj)
	{
		return obj.empty();
	};
}

} // namespace fpcpp
