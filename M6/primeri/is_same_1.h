#pragma once

#include <type_traits>

template<typename T1, typename T2>
struct is_same : std::false_type {};

template<typename T>
struct is_same<T,T> : std::true_type {};

#define IS_VOID(X) is_same<X, void>::value

#define IS_TARGET(X) IS_VOID(X)
