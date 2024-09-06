#pragma once

namespace DebTools
{
	template <typename F, typename... Args>
	constexpr bool is_noexcept(F&& f, Args&&... args) {
		return noexcept(std::forward<F>(f)(std::forward<Args>(args)...));
	}

	template <typename F, typename... Args>
	constexpr void check_noexcept(F&& f, Args&&... args) {
		static_assert(is_noexcept(std::forward<F>(f), std::forward<Args>(args)...), "Function must be noexcept.");
	}

	template <typename Func, typename... Args>
	constexpr void check_noexcept_func(Func&& func, Args&&... args) {
		static_assert(noexcept(std::forward<Func>(func)(std::forward<Args>(args)...)), "Function must be noexcept.");
	}
}