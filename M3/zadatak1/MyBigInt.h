/**
 * @author Jovan Slavujevic
 * @brief zadatak 1 - vezbanje 3
 */

#ifndef _MY_BIG_INT_
#define _MY_BIG_INT_

#include <cstdint>
#include <cstring>
#include <array>
#include <iostream>

struct MyBigInt final
{
private:
	friend std::ostream& operator<<(std::ostream&, const MyBigInt&);
	friend MyBigInt operator+(unsigned long long left, const MyBigInt& right);
	friend MyBigInt operator""_mbi(const char* x) noexcept(false);
	inline int_least8_t& operator[](int n) { return digits[n]; }
	inline const int_least8_t& operator[](int n) const { return digits[n]; }

	int_least8_t* digits = nullptr;
	int usedDigits{ 0 };
public:
	MyBigInt(unsigned long long n);
	MyBigInt(const MyBigInt& other);
	MyBigInt(MyBigInt&& other);
	MyBigInt& operator=(const MyBigInt& other);
	MyBigInt& operator=(MyBigInt&& other);
	~MyBigInt();

	MyBigInt operator+(unsigned long long n) const noexcept(false);
	MyBigInt operator+(MyBigInt other) const noexcept(false);
	MyBigInt& operator=(unsigned long long n);
	bool operator!=(MyBigInt other) const noexcept(false);
};

std::ostream& operator<<(std::ostream& os, const MyBigInt& other);
MyBigInt operator+(unsigned long long left, const MyBigInt& right);
MyBigInt operator""_mbi(const char* x) noexcept(false);

#endif
