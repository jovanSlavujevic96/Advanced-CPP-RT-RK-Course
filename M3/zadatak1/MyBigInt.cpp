/**
 * @author Jovan Slavujevic
 * @brief zadatak 1 - vezbanje 3
 */

#include <cstring>
#include <string>
#include <stdexcept>
#include <cstdlib>

#include "MyBigInt.h"

/**
 * @brief constructor w/ param
 */
MyBigInt::MyBigInt(unsigned long long n)
{
	// find number of digits
	auto tmp = n;
	do
	{
		tmp /= 10;
		usedDigits++;
	} while (tmp > 0);

	// alloc new array & fill it w/ digits
	digits = new int_least8_t[usedDigits];
	for (tmp = 0; tmp < usedDigits; ++tmp)
	{
		digits[usedDigits - 1 - tmp] = n % 10;
		n /= 10;
	}
}

/**
 * @brief copy constructor
 */
MyBigInt::MyBigInt(const MyBigInt& other) :
	usedDigits{ other.usedDigits }
{
	// alloc new array & copy digits
	digits = new int_least8_t[usedDigits];
	std::memcpy(digits, other.digits, usedDigits);
}

/**
 * @brief mov constructor
 */
MyBigInt::MyBigInt(MyBigInt&& other) :
	usedDigits{other.usedDigits},
	digits{other.digits}
{
	// make other object empty
	other.usedDigits = 0;
	other.digits = nullptr;
}

/**
 * @brief copy operator
 */
MyBigInt& MyBigInt::operator=(const MyBigInt& other)
{
	// free earlier allocated memory if exists
	if (this->digits)
	{
		delete [] this->digits;
	}

	// alloc new array, copy digits into & assign array size from other object
	this->usedDigits = other.usedDigits;
	this->digits = new int_least8_t[usedDigits];
	std::memcpy(this->digits, other.digits, this->usedDigits);

	return *this;
}

/**
 * @brief mov operator
 */
MyBigInt& MyBigInt::operator=(MyBigInt&& other)
{
	// free earlier allocated memory if exists
	if (this->digits)
	{
		delete [] this->digits;
	}

	// take other objects content
	this->usedDigits = other.usedDigits;
	this->digits = other.digits;

	// make other object empty
	other.usedDigits = 0;
	other.digits = nullptr;

	return *this;
}

/**
 * @brief destructor
 */
MyBigInt::~MyBigInt()
{
	// free earlier allocated memory if exists
	if (digits)
	{
		delete [] digits;
	}
}

/**
 * @brief addition operator of MyBigInt by integer
 */
MyBigInt MyBigInt::operator+(unsigned long long n) const noexcept(false)
{
	MyBigInt other{ n };
	return MyBigInt::operator+(std::move(other)); // throws exception
}

/**
 * @brief addition operator of MyBigInt by other MyBigInt
 */
MyBigInt MyBigInt::operator+(MyBigInt other) const noexcept(false)
{
	// check is MyBigInt corrupted
	if (!this->digits || !other.digits)
	{
		throw std::runtime_error("digits is NULL -> assign some value!");
	}

	// helper variables
	const MyBigInt* greater = nullptr;
	MyBigInt* smaller = nullptr;
	const MyBigInt* pseudo_this = nullptr;

	// check which MyBigInt has more digits
	if (other.usedDigits < this->usedDigits)
	{
		pseudo_this = this;
		greater = this;
		smaller = &other;
	}
	else if (other.usedDigits > this->usedDigits)
	{
		greater = &other;
		// copy to avoid damage of original
		smaller = new MyBigInt(*this);
		pseudo_this = smaller;
	}
	else
	{
		pseudo_this = this;
	}

	// resize action for smaller MyBigInt
	if (greater && smaller)
	{
		smaller->digits = (int_least8_t*)std::realloc(smaller->digits, greater->usedDigits);
		std::memmove(smaller->digits + greater->usedDigits - smaller->usedDigits, smaller->digits, smaller->usedDigits);
		std::memset(smaller->digits, 0, greater->usedDigits - smaller->usedDigits);
		smaller->usedDigits = greater->usedDigits;
	}

	// addition action
	int surplus = 0;
	for (int i = other.usedDigits - 1; i >= 0; --i)
	{
		int tmp = other[i] + pseudo_this->digits[i] + surplus;
		other[i] = tmp % 10;
		surplus = tmp / 10;
	}

	// check is there some surplus left in order to increase number of digits
	if (surplus > 0)
	{
		other.usedDigits += 1;
		other.digits = (int_least8_t*)std::realloc(other.digits, other.usedDigits);
		std::memmove(other.digits + 1, other.digits, other.usedDigits - 1);
		other[0] = surplus;
	}

	// free dynamic allocated tmp MyBigInt
	if (pseudo_this != this)
	{
		delete pseudo_this;
	}

	return std::move(other);
}

/**
 * @brief assign operator of MyBigInt by integer
 */
MyBigInt& MyBigInt::operator=(unsigned long long n)
{
	// create MyBigInt of n integer
	MyBigInt tmp{ n };

	// free earlier allocated memory if exists
	if (this->digits)
	{
		delete [] this->digits;
	}

	// assign tmp content
	this->digits = tmp.digits;
	this->usedDigits = tmp.usedDigits;

	// to avoid free of digits in tmp object's destructor
	tmp.digits = nullptr;

	return *this;
}

/**
 * @brief compare operator between two MyBigInts
 */
bool MyBigInt::operator!=(MyBigInt other) const noexcept(false)
{
	// check is MyBigInt corrupted
	if (!this->digits || !other.digits)
	{
		throw std::runtime_error("digits is NULL -> assign some value!");
	}

	// if digit number is different than it's obvious that they are different
	if (other.usedDigits != this->usedDigits)
	{
		return false;
	}

	// compare arrays
	return (std::memcmp(other.digits, this->digits, this->usedDigits) != 0);
}

/**
 * @brief print operator of MyBigInt
 */
std::ostream& operator<<(std::ostream& os, const MyBigInt& other) noexcept(false)
{
	// check is MyBigInt corrupted
	if (!other.digits)
	{
		throw std::runtime_error("digits is NULL -> assign some value!");
	}

	// string storage
	std::string num = "";

	// fill digits into storage
	for (int i = 0; i < other.usedDigits; ++i)
	{
		num += std::to_string(other[i]);
	}

	// output stream
	os << num;
	return os;
}

/**
 * @brief addition operator of integer by MyBigInt resulting new MyBigInt
 */
MyBigInt operator+(unsigned long long num, const MyBigInt& right) noexcept(false)
{
	// check is MyBigInt corrupted
	if (!right.digits)
	{
		throw std::runtime_error("digits is NULL -> assign some value!");
	}

	// create MyBigInt of num integer
	MyBigInt left{ num };

	// do addition operation between two MyBigInts
	return std::move(left + right);
}

/**
 * @brief Literals operator for MyBigInt
 */
MyBigInt operator""_mbi(const char* x) noexcept(false)
{
	// create tmp MyBigInt
	MyBigInt tmp{ 0 };

	// assign length of passed string
	tmp.usedDigits = (int)std::strlen(x);

	// do resize of array if string has digits more than 1
	if (tmp.usedDigits > 1)
	{
		tmp.digits = (int_least8_t*)std::realloc(tmp.digits, tmp.usedDigits);
	}

	// iterate throgh string and assign digits one by one
	for (int i = 0; i < tmp.usedDigits; ++i)
	{
		// check is current character digit
		if (!(x[i] >= 48 && x[i] <= 57))
		{
			throw std::runtime_error("Literal contains symbol that is not a digit!");
		}
		// remove ASCII value of digit
		tmp[i] = x[i] - 48;
	}

	return std::move(tmp);
}

