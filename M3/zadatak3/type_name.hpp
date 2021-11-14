#ifndef _TYPE_NAME_
#define _TYPE_NAME_

#include <string_view>

#if !defined(__PRETTY_FUNCTION__) && !defined(__GNUC__)
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif

template <class T>
constexpr std::string_view type_name()
{
    constexpr std::string_view p = __PRETTY_FUNCTION__;
#if defined(__clang__)
    return std::string_view(p.data() + 34, p.size() - 34 - 1);
#elif defined(__GNUC__)
    return std::string_view(p.data() + 49, p.find(';', 49) - 49);
#elif defined(_MSC_VER)
	return std::string_view(p.data() + 84, p.find(">(", 84) - 84);
#endif
}

#endif
