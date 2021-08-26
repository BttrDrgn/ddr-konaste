#pragma once

namespace utils
{
	template <typename F> using callback = F*;

	template <typename T, typename F> inline bool any_of(T& container, F predicate)
	{
		return std::any_of(container.begin(), container.end(), predicate);
	}
}