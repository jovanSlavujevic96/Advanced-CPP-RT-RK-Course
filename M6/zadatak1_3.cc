/**
 * @author Jovan Slavujevic
 */

#include <iostream>
#include <string>
#include <memory>

namespace my_std
{
	template <typename T>
	class function;

	template<typename FT, typename... Args>
	class function<FT(Args...)>
	{
		// REAL FUNCTION
		typedef FT(*real_func)(Args...); //using real_func = FT(*)(Args...)
		real_func m_func = nullptr;

		// FUNCTOR
		typedef FT(*functor_func)(void*, Args...);
		functor_func m_functor_func = nullptr;

		template<typename Functor>
		static FT invokeFunctorFunction(Functor* fn, Args... args) {
			return (*fn)(args...);
		}

		typedef void*(*functor_constructor)(void*);
		functor_constructor m_functor_construct = nullptr;

		template<typename Functor>
		static void* invokeFunctorConstructor(Functor* fn) {
			return new Functor(*fn);
		}

		typedef void(*functor_destructor)(void*);
		functor_destructor m_functor_destruct = nullptr;

		template<typename Functor>
		static void invokeFunctorDestructor(Functor* fn) {
			fn->~Functor();
		}

		std::unique_ptr<char[]> m_functor_obj = nullptr;
	public:
		function() = default;
		~function() {
			if (m_functor_destruct) {
				m_functor_destruct(m_functor_obj.get());
			}
		}

		template <typename Functor>
		function(Functor f) {
			m_functor_func = reinterpret_cast<functor_func>(invokeFunctorFunction<Functor>);
			m_functor_construct = reinterpret_cast<functor_constructor>(invokeFunctorConstructor<Functor>);
			m_functor_destruct = reinterpret_cast<functor_destructor>(invokeFunctorDestructor<Functor>);
			m_functor_obj = std::unique_ptr<char[]>(reinterpret_cast<char*>(m_functor_construct(&f)));
		}
		template <typename Functor>
		function& operator=(const Functor& f) {
			m_func = nullptr;

			m_functor_func = reinterpret_cast<functor_func>(invokeFunctorFunction<Functor>);
			m_functor_construct = reinterpret_cast<functor_constructor>(invokeFunctorConstructor<Functor>);
			m_functor_destruct = reinterpret_cast<functor_destructor>(invokeFunctorDestructor<Functor>);
			m_functor_obj = std::unique_ptr<char[]>(reinterpret_cast<char*>(m_functor_construct(&f)));
			return *this;
		}

		function(real_func func) : m_func{ func } {}
		function& operator=(real_func func) {
			if (m_functor_destruct && m_functor_obj) {
				m_functor_destruct(m_functor_obj.get());
			}
			m_functor_destruct = nullptr;
			m_functor_obj = nullptr;
			m_functor_func = nullptr;

			m_func = func;
			return *this;
		}

		function(const function& other) : m_func{ other.m_func },
			m_functor_func{ other.m_functor_func },
			m_functor_construct{ other.m_functor_construct },
			m_functor_destruct{ other.m_functor_destruct } {
			if (m_functor_construct) {
				m_functor_obj = std::unique_ptr<char[]>(
					reinterpret_cast<char*>(m_functor_construct(other.m_functor_obj.get()))
				);
			}
		}
		function& operator=(const function& other) {
			m_func = other.m_func;

			m_functor_func = other.m_functor_func;
			m_functor_construct = other.m_functor_construct;
			m_functor_destruct = other.m_functor_destruct;
			if (m_functor_construct) {
				m_functor_obj = std::unique_ptr<char[]>(
					reinterpret_cast<char*>(m_functor_construct(other.m_functor_obj.get()))
				);
			}
			return *this;
		}

		FT operator()(Args... args) noexcept(false) {
			if (m_func) {
				return m_func(std::forward<Args>(args)...);
			}
			else if (m_functor_func && m_functor_obj) {
				return m_functor_func(m_functor_obj.get(), std::forward<Args>(args)...);
			}
			else {
				throw std::runtime_error("function/functor is NULL");
			}
		}
	};

	template<typename T>
	function(T*)->function<T>;
}

/* test function(s) */

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

/* test functor(s) */

struct square
{
	double operator()(double x) {
		return x * x;
	}
};

/* **************** */

int main()
{
	my_std::function<double(double)> a = square();
	my_std::function<void(int)> e = [](int x) {
		std::cout << "Number is: " << x << std::endl;
	};
	my_std::function b(sum);
	my_std::function c(hello_world_print);
	my_std::function d(hello_x_string);

	try {
		std::cout << a(3) << std::endl;
		std::cout << a(9) << std::endl;
		std::cout << b(3) << std::endl;
		c();
		e(404);
		std::cout << d("Jovan") << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	std::cin.get();
	return 0;
}
