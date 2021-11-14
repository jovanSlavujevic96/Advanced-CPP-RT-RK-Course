#include <iostream>
#include <string>
#include "type_name.hpp"

int main()
{
	std::cout << type_name<decltype(5)>() << std::endl;
	std::cout << type_name<decltype(5.0f)>() << std::endl;
	std::cout << type_name<decltype(5.0)>() << std::endl;
	std::cout << type_name<decltype(5L)>() << std::endl;
	using namespace std::literals::string_literals;
	std::cout << type_name<decltype("Jovan"s)>() << std::endl;
	std::cin.get();
	return 0;
}
