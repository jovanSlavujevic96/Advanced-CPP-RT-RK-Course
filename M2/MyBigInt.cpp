#include <cstring>
#include <string>
#include <stdexcept>

#include "MyBigInt.h"

MyBigInt::MyBigInt(unsigned long long n)
{
	auto tmp = n;
	do
	{
		tmp /= 10;
		usedDigits++;
	} while (tmp > 0);

	tmp = 0;
	do
	{
		int_least8_t digit = n % 10;
		n /= 10;
		digits[size - 1 - tmp] = digit;
		tmp++;
	} while (tmp < usedDigits);
}

MyBigInt MyBigInt::operator+(unsigned long long n)
{
	MyBigInt other{ n };
	int step = (other.usedDigits > this->usedDigits) ? other.usedDigits : this->usedDigits;
	int surplus = 0;
	for (int i = MyBigInt::size - 1; i >= MyBigInt::size - step; --i)
	{
		int tmp = other[i] + digits[i] + surplus;
		other[i] = tmp % 10;
		surplus = tmp / 10;
	}
	other.usedDigits = step;
	if (surplus > 0)
	{
		other.usedDigits += 1;
		other[MyBigInt::size - other.usedDigits] = surplus;
	}
	return other;
}

MyBigInt MyBigInt::operator+(MyBigInt other)
{
    int step = (other.usedDigits > this->usedDigits) ? other.usedDigits : this->usedDigits;
    int surplus = 0;
    for (int i = MyBigInt::size - 1; i >= MyBigInt::size - step; --i)
    {
        int tmp = other[i] + digits[i] + surplus;
        other[i] = tmp % 10;
        surplus = tmp / 10;
    }
    other.usedDigits = step;
    if (surplus > 0)
    {
        other.usedDigits += 1;
        other[MyBigInt::size - other.usedDigits] = surplus;
    }
    return other;
}

MyBigInt& MyBigInt::operator=(unsigned long long n)
{
	*this = MyBigInt(n);
	return *this;
}

bool MyBigInt::operator!=(MyBigInt other)
{
	return (memcmp(other.digits.data(), this->digits.data(), MyBigInt::size) != 0);
}

std::ostream& operator<<(std::ostream& os, MyBigInt& other)
{
	std::string num = "";
	for (int i = MyBigInt::size - other.usedDigits; i < MyBigInt::size; ++i)
	{
		num += std::to_string(other[i]);
	}
	os << num;
	return os;
}

MyBigInt operator+(unsigned long long num, const MyBigInt& right)
{
	MyBigInt left{ num };
	return left + right;
}

MyBigInt operator""_mbi(const char* x) noexcept(false)
{
	MyBigInt tmp(0);
	int lit_len = std::strlen(x);
	if (lit_len > 70)
	{
		throw std::runtime_error("Literal has more than 70 digits!");
	}
	tmp.usedDigits = 0;
	for (int i = lit_len - 1, j = MyBigInt::size - 1; i >= 0; --i, --j)
	{
		if (!(x[i] >= 48 && x[i] <= 57))
		{
			throw std::runtime_error("Literal contains symbol that is not a digit!");
		}
		tmp[j] = x[i] - 48;
		tmp.usedDigits++;
	}
	return tmp;
}

