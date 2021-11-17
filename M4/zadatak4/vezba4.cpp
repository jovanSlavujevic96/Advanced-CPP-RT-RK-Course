/**
 * @author Jovan Slavujevic
 */

#include <thread>
#include <chrono>
#include <mutex>
#include <iostream>
#include <cstdint>

constexpr std::pair<int, int> c_pair[] =
{
	{1,2},
	{3,4},
	{5,6}
};

int main()
{
	std::mutex exit_mtx;
	bool exit = false;

	std::mutex pair_mtx;
	std::pair<int, int> pair;

	std::thread t1(
		[&]()
		{
			uint8_t i = 0;
			while (!exit)
			{
				pair_mtx.lock();
				pair = c_pair[i];
				pair_mtx.unlock();

				i = (i + 1) % 3;
			}
			std::cout << "exit t1\n";
		}
	);

	std::thread t2(
		[&]()
		{
			while (!exit)
			{
				std::cout << pair.first + pair.second << std::endl;
			}
			std::cout << "exit t2\n";
		}
	);

	/** press <ENTER> to exit threads */
	std::cin.get();

	exit_mtx.lock();
	exit = true;
	exit_mtx.unlock();

	t1.join();
	t2.join();

	/** press <ENTER> to exit app */
	std::cin.get();

	return 0;
}
