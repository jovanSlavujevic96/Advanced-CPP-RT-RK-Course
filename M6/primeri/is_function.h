#pragma once

#include <type_traits>

template<typename T>
struct is_function : std::false_type {};

template<typename FT, typename... Args>
struct is_function<FT(Args...)> : std::true_type {};

template<typename T>
constexpr bool is_function_v = is_function<T>::value;

#define IS_TARGET(X) is_function_v<X>
