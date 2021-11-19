/**
 * @author Jovan Slavujevic
 */

#include <iostream>

template<typename T>
T min(T x, T y)
{
	return (x < y) ? x : y;
}

template<typename T, typename... Args>
T min(T x, Args... args)
{
	auto a1 = min(args...);
	return x < a1 ? x : a1;
}

int main()
{
	std::cout << min(1, 2) << std::endl;
	std::cout << min(55, 6, 1, 23, 0) << std::endl;
	std::cout << min(55, 6, -1, 111, 23, 0) << std::endl;

	std::cin.get();
	return 0;
}
