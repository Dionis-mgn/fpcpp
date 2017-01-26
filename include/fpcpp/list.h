namespace fpcpp
{

template <template<typename...> typename T, typename F, typename ...T_ARGS>
decltype(auto) map(F f, const T<T_ARGS...> &t)
{
	using f_result_type = decltype(f(*t.begin()));
	using result_t = T<f_result_type>;
	result_t result;

	for (auto &i : t)
		result.push_back(f(i));

	return result;
}

template <typename F>
decltype(auto) map(F f)
{
	return [f](const auto &t)
	{
		return map(f, t);
	};
}

template <template<typename...> typename T, typename F, typename ...T_ARGS>
decltype(auto) filter(F f, const T<T_ARGS...> &t)
{
	using f_result_type = decltype(f(*t.begin()));
	using value_type = typename std::decay<decltype(t)>::type::value_type;
	static_assert(std::is_same<f_result_type, bool>::value, "Functional object should return a bool");
	using result_t = T<value_type>;
	result_t result;

	for (auto &i : t)
	{
		if (f(i))
			result.push_back(i);
	}

	return result;
}

template <typename F>
decltype(auto) filter(F f)
{
	return [f](const auto &t)
	{
		return filter(f, t);
	};
}

template <typename T, typename F>
decltype(auto) reject(F f, const T &t)
{
	return filter(Not(f), t);
}

template <typename F>
decltype(auto) reject(F f)
{
	return [f](const auto &t)
	{
		return reject(f, t);
	};
}

template <typename F, typename ACC, typename CONTAINER>
ACC reduce(F f, ACC acc, const CONTAINER &container)
{
	for (auto &i : container)
		f(i, acc);

	return acc;
}

template <typename F, typename ACC>
decltype(auto) reduce(F f, ACC acc)
{
	return [f, acc](const auto &container)
	{
		return reduce(f, acc, container);
	};
}

} // namespace fpcpp
