#include <iostream>

template<typename T>
struct Tad
{
	Tad(T x) : m_v(x) {}
	T m_v;
};

#ifndef EX3
#define EX3
#endif

#ifdef EX1
template<typename T>
auto makeTad(T x)
{
	return Tad<T>{ x };
}
#endif

#ifdef EX2
template<typename T>
auto makeTad(T x) -> Tad<T>
{
	return Tad<T>{ x };
}
#endif

#ifdef EX3
template<typename T>
Tad(T x)->Tad<T>;
#endif

int main()
{
	Tad a{ 55 };
	auto b = Tad{ 5 };

	std::cout << a.m_v << std::endl;
	std::cout << b.m_v << std::endl;

	std::cin.get();
	return 0;
}
