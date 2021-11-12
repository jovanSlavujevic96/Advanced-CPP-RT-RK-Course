/**
 * @author Jovan Slavujevic
 */

#include <iostream>
#include <stdexcept>

// Овде написати следећу функцију:
constexpr int fibo(int n)
{
	// Declare an array to store
    // Fibonacci numbers.
    // 1 extra to handle
    // case, n = 0
    int f[n + 2];
    int i;

	if (n >= 47)
	{
		throw "Bad argument n - argument is too big!";
	}

    // 0th and 1st number of the
    // series are 0 and 1
    f[0] = 0;
    f[1] = 1;
 
    for(i = 2; i <= n; i++)
    {
       //Add the previous 2 numbers
       // in the series and store it
       f[i] = f[i - 1] + f[i - 2];
    }
    return f[n];
}

int main()
{
	static_assert(fibo(7) == 34);
	const int k = fibo(9);
	std::cout << k << std::endl;
	const int l = fibo(300); // 300. Финоначијев број је превелик за int

	return 0;
}
