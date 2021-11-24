#pragma once

#include <type_traits>

template<typename T1, typename T2>
constexpr bool is_same_v = false;

template<typename T>
constexpr bool is_same_v<T,T> = true;

#define IS_CONST_VOID(X) is_same_v<X, const void>

#define IS_TARGET(X) IS_CONST_VOID(X)
