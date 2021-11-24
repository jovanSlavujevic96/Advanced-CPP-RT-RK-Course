#include <iostream>
#include <string>
#include <type_traits>

template<typename T>
class Something
{
	friend std::ostream& operator<<(std::ostream& rhs, const Something& lhs)
	{
		rhs << lhs.m_x;
		return rhs;
	}
	T m_x;
public:
	inline Something(const T& x) : m_x{ x } {}
};

Something(const char*) -> Something<std::string>;

int main()
{
	Something s{ "Cao" };
	std::cout << s << std::endl;

	std::cin.get();
	return 0;
}