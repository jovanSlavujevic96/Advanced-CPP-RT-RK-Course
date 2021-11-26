#include <iostream>
#include <utility>
#include <array>

namespace my_std
{
	template<typename T>
	class FunctionBase;

	template<typename RT, typename... Args>
	class FunctionBase<RT(Args...)> {
	public:
		virtual RT operator() (Args...) = 0;
		virtual ~FunctionBase() = default;
		virtual FunctionBase* clone() const = 0;
	};

	template<typename TO, typename T>
	class FunctionDerived;

	template<typename TO, typename RT, typename... Args>
	class FunctionDerived<TO, RT(Args...)> : public FunctionBase<RT(Args...)> {
	public:
		FunctionDerived(TO fo) : m_fo(fo) {}

		RT operator() (Args... args) override {
			return m_fo(std::forward<Args>(args)...);
		}

		FunctionBase<RT(Args...)>* clone() const override {
			return new FunctionDerived(*this);
		}
	private:
		TO m_fo;
	};

	template<typename T>
	class function;

	template<typename RT, typename... Args>
	class function<RT(Args...)> {
	public:
		template<typename TO>
		function(TO fo) : m_fp(new FunctionDerived<TO, RT(Args...)>(fo)) {}

		function(const function& x) {
			m_fp = x.m_fp->clone();
		}

		function(function&& x) {
			m_fp = x.m_fp;
			x.m_fp = nullptr;
		}

		function& operator=(const function& x) {
			delete m_fp;
			m_fp = x.m_fp->clone();
			return *this;
		}

		function& operator=(function&& x) {
			delete m_fp;
			m_fp = x.m_fp;
			x.m_fp = nullptr;
			return *this;
		}

		~function() { delete m_fp; }

		RT operator()(Args... args) {
			return (*m_fp)(std::forward<Args>(args)...);
		}
	private:
		FunctionBase<RT(Args...)>* m_fp;
	};
}

int foo(int x) {
	return x + 1;
}

struct fooS {
	fooS(int a) : m_a(a) {}
	int operator()(int x) {
		return x + m_a++;
	}
private:
	int m_a;
};

int main()
{
	my_std::function<int(int)> f1(foo);
	my_std::function<int(int)> f2(fooS(5));

	std::cout << f1(7) << " " << f2(8) << std::endl;

	std::array<my_std::function<int(int)>, 2> arry = { f1, f2 };

	std::cout << arry[0](7) << " " << arry[1](8) << std::endl;
	std::cout << f1(7) << " " << f2(8) << std::endl;

	std::cin.get();
	return 0;
}
