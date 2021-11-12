#ifndef _MY_BIG_INT_
#define _MY_BIG_INT_

#include <cstdint>
#include <cstring>
#include <array>
#include <iostream>

struct MyBigInt final
{
private:
	friend std::ostream& operator<<(std::ostream&, MyBigInt&);
	friend MyBigInt operator+(unsigned long long left, const MyBigInt& right);
	friend MyBigInt operator""_mbi(const char* x) noexcept(false);
	int_least8_t& operator[] (int n) { return digits[n]; }

	static constexpr int size{ 70 };
	std::array<int_least8_t, size> digits{ 0 };
	int usedDigits{ 0 };
public:
	MyBigInt(unsigned long long n);
	~MyBigInt() = default;

	MyBigInt operator+(unsigned long long n);
	MyBigInt operator+(MyBigInt other);
	MyBigInt& operator=(unsigned long long n);
	bool operator!=(MyBigInt other);
};

std::ostream& operator<<(std::ostream& os, MyBigInt& other);
MyBigInt operator+(unsigned long long left, const MyBigInt& right);
MyBigInt operator""_mbi(const char* x) noexcept(false);

#endif
