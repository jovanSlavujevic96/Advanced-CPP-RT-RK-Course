#include "MyBigInt.h"

#include <iostream>

// Овде написати следећу функцију:
MyBigInt fibo(unsigned long long n)
{
	MyBigInt x1 = 0;
	MyBigInt x2 = 1;

    for (int i = 1; i < n; ++i)
    {
        MyBigInt t = x1 + x2;
		x1 = x2;
		x2 = t;
    }
	return x2;
}

int main()
{
	MyBigInt k{ 7 };
	k = fibo(9);
	std::cout << "fibo(9) = " << k << std::endl;
	k = k + 5;
	std::cout << "k + 5 = " << k << std::endl;
	k = 7 + fibo(11);
	std::cout << "7 + fibo(11) = " << k << std::endl;
	k = 13_mbi;
	std::cout << k << std::endl;
	MyBigInt l = fibo(300);
	if (l != 222232244629420445529739893461909967206666939096499764990979600_mbi) {
		std::cout << "Greska!" << std::endl;
		return 1;
	}
	std::cout << "fibo(300) = " <<  l << std::endl;

	std::cin.get();
	return 0;
}
