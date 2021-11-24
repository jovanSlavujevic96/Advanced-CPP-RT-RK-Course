#pragma once

namespace my_std
{
	template <typename T>
	constexpr bool is_void_v = false;

	template<>
	constexpr bool is_void_v<void> = true;

	template<>
	constexpr bool is_void_v<const void> = true;

	template<>
	constexpr bool is_void_v<volatile void> = true;

	template<>
	constexpr bool is_void_v<const volatile void> = true;
}

#define IS_VOID(X) my_std::is_void_v<X>

#define IS_TARGET(X) IS_VOID(X)
