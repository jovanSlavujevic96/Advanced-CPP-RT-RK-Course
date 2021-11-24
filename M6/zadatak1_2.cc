/**
 * @author Jovan Slavujevic
 */

#include <iostream>
#include <string>

namespace my_std
{
	template <typename T>
	class function;

	template<typename FT, typename... Args>
	class function<FT(Args...)>
	{
		typedef FT(*real_func)(Args...);

		real_func m_func;
	public:
		function() = default;
		~function() = default;

		function(real_func func) : m_func{ func } {}
		function& operator=(real_func func) {
			m_func = func;
			return *this;
		}

		function(const function& other) : m_func{ other.m_func } {}
		function& operator=(const function& other) {
			m_func = other.m_func;
			return *this;
		}

		function(function&& other) : m_func{ other.m_func } {
			other.m_func = nullptr;
		}
		function& operator=(function&& other) {
			m_func = other.m_func;
			other.m_func = nullptr;
			return *this;
		}

		double operator()(double x) const noexcept(false) {
			if (!m_func) {
				throw std::runtime_error("no function assined");
			}
			return m_func(x);
		}

		FT operator()(Args... args) { return m_func(args...); }
	};

	template<typename T>
	function(T*)->function<T>;
}

/* test function(s) */
double square(double x)
{
	return x * x;
}

double sum(double x)
{
	return x + x;
}

void hello_world_print()
{
	std::cout << "Hello world!\n";
}

std::string hello_x_string(const char* x)
{
	return std::string("Hello ") + x;
}
/* **************** */

int main()
{
	my_std::function a(square);
	my_std::function b(sum);
	my_std::function c(hello_world_print);
	my_std::function d(hello_x_string);

	std::cout << a(3) << std::endl;
	std::cout << b(3) << std::endl;
	c();
	std::cout << d("Kaca") << std::endl;

	std::cin.get();
	return 0;
}
