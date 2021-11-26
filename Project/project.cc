/**
 * @author Jovan Slavujevic
 */

#include <iostream>
#include <vector>
#include <memory>
#include <utility>
#include <cassert>
#include <cstring>

#define DEFAULT_POOL_SIZE 10

namespace project
{
	template<typename T>
	class PoolBase
	{
	protected:
		/* storage for tempalte objects */
		std::vector<T*> m_pool;

		/* template objects PoolBase constructor(s) */
		template <typename... Args>
		PoolBase(unsigned N, Args... args) : m_pool{ N } {
			for (auto it = m_pool.begin(); it != m_pool.end(); it++) {
				*it = new T(std::forward<Args>(args)...);
			}
		}

		/* Pool copy constructor */
		PoolBase(const PoolBase& x) {
			for (auto it = x.m_pool.begin(); it != x.m_pool.end(); it++) {
				m_pool.push_back(new T(**it));
			}
		}

		/* Pool move constructor */
		PoolBase(PoolBase&& x) : m_pool{ std::move(x.m_pool) } {}

		/* destructor */
		virtual ~PoolBase() {
			for (auto it = m_pool.begin(); it != m_pool.end(); it++) {
				delete *it;
			}
		}

		/* copy method */
		void copy(const PoolBase& x) {
			for (auto it = m_pool.begin(); it != m_pool.end(); it++) {
				delete *it;
			}
			m_pool.clear();
			for (auto it = x.m_pool.begin(); it != x.m_pool.end(); it++) {
				m_pool.push_back(new T(**it));
			}
		}

		/* move method */
		void move(PoolBase&& x) {
			for (auto it = m_pool.begin(); it != m_pool.end(); it++) {
				delete *it;
			}
			m_pool = std::move(x.m_pool);
		}
	public:
		/* acquire object method */
		std::shared_ptr<T> acquireObject() {
			/* get first object from storage */
			T* obj = m_pool[0];

			/* remove acquired object from storage */
			m_pool.erase(m_pool.begin());

			/* if storage is empty push new template object */
			if (!m_pool.size()) {
				m_pool.push_back(new T);
			}

			/* put acquired object into smart pointer */
			return std::shared_ptr<T>(obj,
				[this](T* ptr) /* redefined smart pointer deleter */
				{
					m_pool.push_back(ptr); /* get it back to pool storage */
				}
			);
		}

		/* get size of pool storage */
		size_t getPoolSize() const {
			return m_pool.size();
		}
	};

	template<typename T, unsigned N = DEFAULT_POOL_SIZE>
	class Pool : public PoolBase<T>
	{
	public:
		/* template objects Pool constructor(s) */
		template <typename... Args>
		Pool(Args... args) : PoolBase<T>(N, std::forward<Args>(args)...) {}

		Pool(T&& other) : PoolBase<T>(N, std::move(other)) {}

		/* Pool copy constructor */
		Pool(const PoolBase<T>& x) : PoolBase<T>(x) {}

		/* Pool move constructor */
		Pool(PoolBase<T>&& x) : PoolBase<T>(x) {}

		/* Pool assign operator(s) */
		Pool& operator=(const PoolBase<T>& x) {
			this->copy(x);
			return *this;
		}
		
		/* Pool move operator(s) */
		Pool& operator=(PoolBase<T>&& x) {
			this->move(x);
			return *this;
		}

		/* destructor */
		~Pool() = default;
	};
}

/* TESTING */
struct Test
{
	Test() : m_a{ 33 } {}
	Test(int a) : m_a{ a } {}
	Test(float f, const char* word) {
		m_a = (int)f;
		for (auto it = word; it != word + std::strlen(word); ++it) {
			m_a += *it;
		}
	}
	Test(const Test& t) : m_a{ t.m_a } {}
	int m_a;
};

int main()
{
	/* different alloc variants */
	project::Pool<Test> pool(1.0f, "word");
	project::Pool pool1(Test{});
	project::Pool pool2(Test(1024));
	project::Pool<Test, 2> pool3(404);
	project::Pool<Test, 202> pool4;
	auto pool5 = pool3;

	auto size = pool1.getPoolSize();
	assert(size == DEFAULT_POOL_SIZE);
	{
		/* size check && object value */
		Test test;
		auto ptr = pool1.acquireObject();
		assert(size - 1 == pool1.getPoolSize());
		assert(test.m_a == ptr->m_a);
	}
	assert(size == pool1.getPoolSize());

	{
		size = pool2.getPoolSize();
		auto ptr = pool2.acquireObject();
		assert(size - 1 == pool2.getPoolSize());
		assert(1024 == ptr->m_a);
	}

	assert(pool2.getPoolSize() == DEFAULT_POOL_SIZE);
	pool2 = pool3;
	assert(pool2.getPoolSize() != DEFAULT_POOL_SIZE);
	assert(pool2.getPoolSize() == pool3.getPoolSize());

	{
		auto ptr = pool2.acquireObject();
		assert(404 == ptr->m_a);
	}

	std::cin.get();
	return 0;
}
