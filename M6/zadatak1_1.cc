/**
 * @author Jovan Slavujevic
 */

#include <iostream>

namespace my_std
{
	template <typename T>
	class function;

	template<>
	class function<double(double)>
	{
		typedef double(*real_func)(double);

		real_func m_func = nullptr;
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
	};

	template<typename T>
	function(T*)->function<T>;
}

double square(double x)
{
	return x * x;
}

double sum(double x)
{
	return x + x;
}

double dif(double x)
{
	return x - x;
}

int main()
{
	my_std::function a = square, b = sum, c = dif;
	const my_std::function<double(double)>* ptr[4] =
	{
		&a,
		&b,
		&c,
		nullptr
	};

	for (auto i = ptr; *i != nullptr; ++i)
	{
		auto& j = **i;
		std::cout << j(2) << std::endl;
		std::cout << j(3) << std::endl;
		std::cout << j(9) << std::endl;
		std::cout << j(1.1f) << std::endl;
		std::cout << std::endl;

		if (i == ptr)
		{
			a = sum;
		}
	}

	std::cin.get();
	return 0;
}
