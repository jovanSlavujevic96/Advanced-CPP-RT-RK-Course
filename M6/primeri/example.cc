#include <iostream>
#include <string>
#include <cstring>
#include <memory>

#include INCLUDE_PATH

struct hello_world {
	void operator()() const {
		std::cout << "hello world\n";
	}
};

inline std::unique_ptr<char[]> getHello(const char* target)
{
	char hello[1024] = { 0 };
	constexpr size_t hello_len = sizeof(hello);
	snprintf(hello, hello_len, "Hello %s", target);
	return std::unique_ptr<char[]>(_strdup(hello));
}

int main()
{
	auto hello = getHello("world");
	std::cout << hello.get() << std::endl;

	std::cout << "This test checks is some type " << TARGET << std::endl << std::endl;

	std::cout << std::boolalpha << IS_TARGET(int) << std::endl;
	std::cout << std::boolalpha << IS_TARGET(void) << std::endl;
	std::cout << std::boolalpha << IS_TARGET(float) << std::endl;
	std::cout << std::boolalpha << IS_TARGET(double) << std::endl;
	std::cout << std::boolalpha << IS_TARGET(std::string) << std::endl;
	std::cout << std::boolalpha << IS_TARGET(const void) << std::endl;
	std::cout << std::boolalpha << IS_TARGET(const volatile void) << std::endl;
	std::cout << std::boolalpha << IS_TARGET(volatile const void) << std::endl;
	std::cout << std::boolalpha << IS_TARGET(volatile const void*) << std::endl;

	std::cout << std::boolalpha << IS_TARGET(decltype(getHello)) << std::endl;
	std::cout << std::boolalpha << IS_TARGET(decltype(hello)) << std::endl;
	std::cout << std::boolalpha << IS_TARGET(hello_world) << std::endl;
	std::cout << std::boolalpha << IS_TARGET(hello_world()) << std::endl;

	std::cin.get();
	return 0;
}
