/**
 * @author Jovan Slavujevic
 */

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <string_view>

#if !defined(__PRETTY_FUNCTION__) && defined(_MSC_VER)
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

template<typename T>
struct is_string
	: public std::disjunction<
	std::is_same<char *, typename std::decay_t<T>>,
	std::is_same<const char *, typename std::decay_t<T>>,
	std::is_same<std::string, typename std::decay_t<T>>
	>{
};

template<typename T>
struct is_integer
	: public std::disjunction<
	std::is_same<int, typename std::decay_t<T>>
	> {
};

void myprintf(std::string str)
{
	std::cout << str;
}

template<typename T, typename... Args>
void myprintf(std::string str, T x, Args... args) noexcept(false)
{
	std::stringstream ss;
	size_t index = 0;
	while (1)
	{
		size_t found = str.find('%', index);
		if (found != std::string::npos)
		{
			auto found_1 = found + 1;
			if (str[found_1] != 's' && str[found_1] != 'd' && str[found_1] != 'f')
			{
				index = found + 2;
				continue;
			}
			ss.str("");
			if (str[found_1] == 's' && !is_string<T>::value)
			{
				ss << "Passed parameter " << x << " is " << type_name<T>() << " but it should be string!";
				throw std::runtime_error(ss.str());
			}
			else if (str[found_1] == 'f' && !std::is_floating_point<T>::value)
			{
				ss << "Passed parameter " << x << " is " << type_name<T>() << " but it should be float!";
				throw std::runtime_error(ss.str());
			}
			else if (str[found_1] == 'd' && !is_integer<T>::value)
			{
				ss << "Passed parameter " << x << " is " << type_name<T>() << " but it should be integer!";
				throw std::runtime_error(ss.str());
			}
			ss << x;
			auto begin_of_replacement = str.begin() + found;
			str.erase(begin_of_replacement, begin_of_replacement + 2);
			str.insert(found, ss.str());
			break;
		}
		else
		{
			ss.str("");
			ss << "Not found special character for passed parameter " << x;
			throw std::runtime_error(ss.str());
		}
	}
	myprintf(std::move(str), args...);
}

int main()
{
	myprintf("Hello from string only\n");
	myprintf("int value: %d\n", 123);
	myprintf("float value: %f\n", 1.23);
	myprintf("const char *value: %s\n", "123456789");
	myprintf("int value: %d, float value: %f, const char *value: %s\n", 123, 1.23, "123456789");

	// Errors
	std::cout << std::endl;
	try
	{
		myprintf("int value: %d\n", "123456789"); // Error
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	try
	{
		myprintf("const char *value: %s", 123456789); // Error
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	try
	{
		myprintf("int value: %d\n", 12345, 6789); // Error
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cin.get();
	return 0;
}
