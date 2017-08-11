#pragma once

#ifndef MEGAINT_H
#define MEGAINT_H

#include <iostream>
#include <deque>
#include <utility>

using std::deque;
using std::string;
using std::cout;
using std::endl;
using std::ostream;

class MegaInt {
private:
	// Data members
	deque<char> mega_int;
	bool sign; // false means negative, true means positive

	// Helper functions
	char intToChar(int) const; // convert int to char
	int charToInt(char) const; // convert char to int
	void removeSpaces(string&) const; // remove all white spaces from a string
	deque<char> plus(const deque<char>&, const deque<char>&);
	deque<char> minus(const deque<char>&, const deque<char>&);
	deque<char> multiply(const deque<char>&, size_t);
	void divide_m1(const MegaInt&, MegaInt&, MegaInt&);
	MegaInt& divide_m2(MegaInt&, const string&);
	void normalize();
	void push_back(const char); // add a digit to the end of MegaInt
	void push_back(const int); // add a digit to the end of MegaInt
	void push_back(const MegaInt&); // add a MegaInt to the end of MegaInt
	int initialGuess(const MegaInt&, const MegaInt&);
public:
	// Ctors and Dtor
	MegaInt(int = 0); // default + conversion ctor
	MegaInt(const string&); // conversion ctor
	MegaInt(bool, const deque<char>&);
	MegaInt(const MegaInt&); // copy ctor
	virtual ~MegaInt(); // default dtor

	// Calculation operators overloading
	MegaInt operator+(const MegaInt&); // operator + overloading
	MegaInt& operator+=(const MegaInt&); // operator += overloading
	MegaInt& operator++(); // prefix increment operator overloading
	MegaInt operator++(int); // postfix increment operator overloading

	MegaInt operator-(const MegaInt&); // operator - overloading
	MegaInt& operator-=(const MegaInt&); // operator -= overloading
	MegaInt& operator--(); // prefix decrement operator overloading
	MegaInt operator--(int); // postfix decrement operator overloading

	MegaInt operator*(const MegaInt&); // operator * overloading
	MegaInt& operator*=(const MegaInt&); // operator *= overloading

	MegaInt operator/(const MegaInt&); // operator / overloading
	MegaInt& operator/=(const MegaInt&); // operator /= overloading

	MegaInt operator%(const MegaInt&); // operator % overloading
	MegaInt& operator%=(const MegaInt&); // operator %= overloading

	MegaInt operator+(int); // operator + overloading
	MegaInt& operator+=(int); // operator += overloading
	MegaInt operator-(int); // operator - overloading
	MegaInt& operator-=(int); // operator -= overloading
	MegaInt operator*(int); // operator * overloading
	MegaInt& operator*=(int); // operator *= overloading
	MegaInt operator/(int); // operator / overloading
	MegaInt& operator/=(int); // operator /= overloading
	MegaInt operator%(int); // operator % overloading
	MegaInt& operator%=(int); // operator %= overloading

	friend MegaInt operator+(int, const MegaInt&);
	friend MegaInt& operator+=(int, MegaInt&);
	friend MegaInt operator-(int, const MegaInt&);
	friend MegaInt& operator-=(int, MegaInt&);
	friend MegaInt operator*(int, const MegaInt&);
	friend MegaInt& operator*=(int, MegaInt&);
	friend MegaInt operator/(int, const MegaInt&);
	friend MegaInt& operator/=(int, MegaInt&);
	friend MegaInt operator%(int, const MegaInt&);
	friend MegaInt& operator%=(int, MegaInt&);

	friend bool operator==(const deque<char>&, const deque<char>&);
	friend bool operator<(const deque<char>&, const deque<char>&);
	friend bool operator>(const deque<char>&, const deque<char>&);
	friend bool operator<=(const deque<char>&, const deque<char>&);
	friend bool operator>=(const deque<char>&, const deque<char>&);
	friend bool operator!=(const deque<char>&, const deque<char>&);

	MegaInt operator-() const; // unary operator - overloading
	MegaInt operator+() const; // unary operator + overloading

	// Relational operators overloading
	bool operator==(const MegaInt&) const; // operator == overloading
	bool operator==(int rhs) const;
	bool operator<(const MegaInt&) const; // operator < overloading
	bool operator<(int rhs) const;
	bool operator>(const MegaInt&) const; // operator > overloading
	bool operator>(int rhs) const;
	bool operator<=(const MegaInt&) const; // operator <= overloading
	bool operator<=(int rhs) const;
	bool operator>=(const MegaInt&) const; // operator >= overloading
	bool operator>=(int rhs) const;
	bool operator!=(const MegaInt&) const; // operator != overloading
	bool operator!=(int rhs) const;

	friend bool operator==(const int, const MegaInt&);
	friend bool operator<(const int, const MegaInt&);
	friend bool operator>(const int, const MegaInt&);
	friend bool operator<=(const int, const MegaInt&);
	friend bool operator>=(const int, const MegaInt&);
	friend bool operator!=(const int, const MegaInt&);

	// Other operators overloading
	MegaInt& operator=(const MegaInt&); // operator= overloading
	MegaInt& operator=(const int); // operator= overloading
	friend ostream& operator<<(ostream&, const MegaInt&); // operator<< overloading
	int operator[](size_t) const; // operator[] overloading

	// Utility functions
	bool isPositive() const; // get the sign of MegaInt
	bool isEven() const; // check if the MegaInt is even number
	size_t length() const; // get the length of MegaInt
	MegaInt subMegaInt(size_t beginPos, size_t endPos);
};

#endif