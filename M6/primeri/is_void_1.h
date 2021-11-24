#pragma once

namespace my_std
{
	template<typename T>
	struct is_void
	{
		static constexpr bool value = false;
	};

	template<>
	struct is_void<void>
	{
		static constexpr bool value = true;
	};
}

#define IS_VOID(X) my_std::is_void<X>::value

#define IS_TARGET(X) IS_VOID(X)
