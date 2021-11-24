#pragma once

namespace my_std
{
	struct false_type
	{
		static constexpr bool value = false;
	};

	struct true_type
	{
		static constexpr bool value = true;
	};

	template<typename T>
	struct is_void : false_type
	{
	};

	template<>
	struct is_void<void> : true_type
	{
	};

	template<>
	struct is_void<const void> : true_type
	{
	};

	template<>
	struct is_void<volatile void> : true_type
	{
	};

	template<>
	struct is_void<const volatile void> : true_type
	{
	};
}

#define IS_VOID(X) my_std::is_void<X>::value

#define IS_TARGET(X) IS_VOID(X)
