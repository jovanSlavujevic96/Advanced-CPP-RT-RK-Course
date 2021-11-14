/**
 * @author Jovan Slavujevic
 * @brief zadatak 1 - vezbanje 3
 */

#include "MyBigInt.h"

#include <iostream>

// овде написати следећу функцију:
MyBigInt fibo(unsigned long long n)
{
	MyBigInt x1 = 0;
	MyBigInt x2 = 1;

	for (int i = 1; i < n; ++i)
	{
		auto t = x1 + x2;
		x1 = std::move(x2);
		x2 = std::move(t);
	}
	return x2;
}

int main()
{
	MyBigInt k = fibo(9);
	std::cout << "fibo(9) = " << k << std::endl;
	k = k + 5;
	std::cout << "k + 5 = " << k << std::endl;
	k = 7 + fibo(11);
	std::cout << "7 + fibo(11) = " << k << std::endl;
	k = 13_mbi;
	std::cout << "13_mbi = " << k << std::endl;
	if (fibo(300) != 222232244629420445529739893461909967206666939096499764990979600_mbi)
	{
		std::cout << "Greska!" << std::endl;
		return 1;
	}

	std::cin.get();
	return 0;
}
