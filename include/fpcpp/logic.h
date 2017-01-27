namespace fpcpp
{

template <typename F>
inline decltype(auto) Not(F f)
{
	return [f](auto &&arg)
	{
		return !f(std::forward<decltype(arg)>(arg));
	};
}

inline decltype(auto) Not()
{
	return [](auto&&... args)
	{
		return Not(std::forward<decltype(args)>(args)...);
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
