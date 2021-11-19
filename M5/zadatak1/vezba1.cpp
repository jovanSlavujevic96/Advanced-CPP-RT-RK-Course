/**
 * @author Jovan Slavujevic
 */

#include <iostream>

template<typename T>
T sum(T x)
{
	return x;
}

template<typename T, typename... Args>
T sum(T x, Args... args)
{
	return x + sum(args...);
}

int main()
{
	std::cout << sum(1, 2, 3) << std::endl;
	std::cout << sum(1, 2, 3, 4, 5, 6) << std::endl;

	std::cin.get();
	return 0;
}
