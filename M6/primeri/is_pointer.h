#include "is_void_4.h"

namespace detail
{
	template<typename T>
	struct is_pointer_helper : std::false_type {};

	template<typename T>
	struct is_pointer_helper<T*> : std::true_type {};
}

template<typename T>
struct is_pointer : detail::is_pointer_helper<typename my_std::remove_cv<T>::type> {};

#define IS_POINTER(X) is_pointer<X>::value

#define IS_TARGET(X) IS_POINTER(X)
