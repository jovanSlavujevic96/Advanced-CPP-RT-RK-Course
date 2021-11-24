#pragma once

#include <type_traits>

namespace my_std
{
	template<typename T>
	struct remove_const
	{
		using type = T;
	};

	template<typename T>
	struct remove_const<const T>
	{
		using type = T;
	};

	template<typename T>
	struct remove_volatile
	{
		using type = T;
	};

	template<typename T>
	struct remove_volatile<volatile T>
	{
		using type = T;
	};

	template<typename T>
	struct remove_cv
	{
		using type = typename remove_volatile<typename remove_const<T>::type>::type;
	};

	template<typename T>
	struct is_void_helper : std::false_type
	{

	};

	template<>
	struct is_void_helper<void> : std::true_type
	{

	};

	template<typename T>
	struct is_void : is_void_helper<typename remove_cv<T>::type>
	{

	};
}

#define IS_VOID(X) my_std::is_void<X>::value

#define IS_TARGET(X) IS_VOID(X)
