#ifndef _MY_UNIQUE_PTR_
#define _MY_UNIQUE_PTR_

#include <iostream>

template<class T>
class MyUniquePtr
{
public:
	MyUniquePtr(T* ptr = nullptr) : m_ptr{ ptr } {}
	MyUniquePtr(const MyUniquePtr&) = delete;
	MyUniquePtr(MyUniquePtr&& other) {
		m_ptr = other.m_ptr;
		other.m_ptr = nullptr;
	}
	~MyUniquePtr() { 
		if (m_ptr)
		{
			delete m_ptr;
		}
		std::cout << "Goodbye\n";
	}

	MyUniquePtr& operator=(const MyUniquePtr&) = delete;
	MyUniquePtr& operator=(MyUniquePtr&& other) {
		m_ptr = other.m_ptr;
		other.m_ptr = nullptr;
		return *this;
	}

	T* get() const { return m_ptr; }
	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
private:
	T* m_ptr;
};

#endif
