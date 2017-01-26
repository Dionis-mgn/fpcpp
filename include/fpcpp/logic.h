namespace fpcpp
{

template <typename F>
decltype(auto) Not(F f)
{
	return [f](auto &&arg)
	{
		return !f(std::forward<decltype(arg)>(arg));
	};
}

//C++17 variant
//inline auto is_empty = [](const auto &obj) { return obj.empty(); };
decltype(auto) is_empty()
{
	return [](const auto &obj)
	{
		return obj.empty();
	};
}

} // namespace fpcpp
