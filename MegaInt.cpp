#include "MegaInt.h"
#include <algorithm>

// Helper functions
char MegaInt::intToChar(int i) const { // convert int to char
	return static_cast<char>(i + '0');
}

int MegaInt::charToInt(char c) const { // convert char to int
	return c - int{ '0' };
}

void MegaInt::removeSpaces(string& str) const { // remove all white spaces from a string
	if (!str.empty()) {
		auto it = str.begin();
		while (it != str.end()) {
			if ((*it == ' ') || (*it == '\t'))
				str.erase(it);
			else
				it++;
		}
	}
}

deque<char> MegaInt::plus(const deque<char>& x, const deque<char>& y) {
	deque<char> result;
	int m = x.size();
	int n = y.size();
	int p = std::max(m, n) + 1;
	int carry = 0;
	int i = p - 1;
	int j = m - 1;
	int k = n - 1;

	while (j >= 0 && k >= 0) {
		int t = charToInt(x.at(j)) + charToInt(y[k]) + carry;
		result.push_front(intToChar(t % 10));
		carry = t / 10;
		i--;
		j--;
		k--;
	}

	while (j >= 0) {
		int t = charToInt(x.at(j)) + carry;
		result.push_front(intToChar(t % 10));
		carry = t / 10;
		i--;
		j--;
	}

	while (k >= 0) {
		int t = charToInt(y[k]) + carry;
		result.push_front(intToChar(t % 10));
		carry = t / 10;
		i--;
		k--;
	}

	result.push_front(intToChar(carry));
	return result;
}

deque<char> MegaInt::minus(const deque<char>& x, const deque<char>& y) {
	deque<char> result;
	int m = x.size();
	int n = y.size();
	int p = std::max(m, n);
	int borrow = 0;
	int i = p - 1;
	int j = m - 1;
	int k = n - 1;

	while (j >= 0 && k >= 0) {
		int t = charToInt(x.at(j)) - (charToInt(y[k]) + borrow);
		borrow = 0;
		if (t < 0) {
			borrow = 1;
			t += 10;
		}
		result.push_front(intToChar(t));
		i--;
		j--;
		k--;
	}

	while (j >= 0) {
		int t = charToInt(x.at(j)) - borrow;
		borrow = 0;
		if (t < 0) {
			borrow = 1;
			t += 10;
		}
		result.push_front(intToChar(t));
		i--;
		j--;
	}

	if (borrow == 1 || k >= 0) {
		cout << "X cannot be less than Y in (X - Y)" << endl;
		throw "X cannot be less than Y in (X - Y)";
	}
		
	
	return result;
}

deque<char> MegaInt::multiply(const deque<char>& x, size_t y) {
	deque<char> result;
	int carry = 0;
	for (int i = x.size() - 1; i >= 0; i--) {
		int t = y * charToInt(x.at(i)) + carry;
		result.push_front(intToChar(t % 10));
		carry = t / 10;
	}
	if (carry != 0)
		result.push_front(intToChar(carry));
	return result;
}

void MegaInt::divide_m1(const MegaInt& lhs, MegaInt& rhs, MegaInt& quotient) { // D1 method
	bool lhsSign = lhs.sign;
	MegaInt remainder = +lhs;
	bool rhsSign = rhs.sign;
	rhs = +rhs;
	quotient = 0;
	while (remainder >= rhs) {
		remainder -= rhs;
		quotient++;
	}

	if (!rhsSign)
		quotient.sign = !lhsSign;
	else
		quotient.sign = lhsSign;
}

MegaInt& MegaInt::divide_m2(MegaInt& d, const string& desiredResult) { // D2 method
	MegaInt q;
	MegaInt r;
	bool thisSign = this->sign;
	bool rhsSign = d.sign;
	if (this->mega_int < d.mega_int) {
		q = 0;
		r = *this;
	}
	else {
		MegaInt n = +(*this);
		d = +d;

		// Get n'
		size_t counter = d.length();
		if (counter > 1)
			n = n.subMegaInt(0, --counter);
		else {
			n = 0;
			--counter;
		}

		r = n;

		while (counter < this->length()) {
			(n = r).push_back((*this)[counter]);
			int qk;
			if (n < d)
				qk = 0;
			else
				qk = initialGuess(n, d);
			//divide_m1(n, d, qk);
			q.push_back(qk);
			r = n - d * qk;
			counter++;
		}
	}

	if (desiredResult == "quotient") {
		this->mega_int = q.mega_int;
		if (!rhsSign)
			this->sign = !thisSign;
		else
			this->sign = thisSign;
	}
	else if (desiredResult == "remainder") {
		this->mega_int = r.mega_int;
		if (thisSign)
			this->sign = true;
		else
			this->sign = false;
	}
	else {
		cout << "Invalid Desired Result: either quotient or remainder" << endl;
		throw "Invalid Desired Result: either quotient or remainder";
	}

	normalize();
	return *this;
}

void MegaInt::normalize() {
	if (mega_int.size() > 1) {
		auto it = mega_int.begin();
		int count = 0;
		while (it != mega_int.end() && *it == '0') { // count no of 0 lying before any other digit
			count++;
			it++;
		}

		while (count > 0) { // remove all counted 0
			mega_int.pop_front();
			count--;
		}

		if (mega_int.empty()) // case mega_int is "000000...", all digits are removed
			mega_int.push_front('0');
	}

	if (mega_int.front() == '0') // after normalized, first digit is 0 mean it's the only digit
		sign = true;
}

void MegaInt::push_back(const char c) { // add a digit to the end of MegaInt
	if (('0' <= c) && (c <= '9')) {
		this->mega_int.push_back(c);
		normalize();
	}
	else
		cout << "Invalid input" << endl;
}

void MegaInt::push_back(const int i) { // add a digit to the end of MegaInt
	char c = intToChar(i);
	push_back(c);
}

void MegaInt::push_back(const MegaInt& mInt) { // add a MegaInt to the end of MegaInt
	if (mInt.length() != 0) {
		for (auto it = mInt.mega_int.begin(); it < mInt.mega_int.end(); it++)
			push_back(*it);
	}
}

int MegaInt::initialGuess(const MegaInt& n, const MegaInt& d) {
	int guess = 5;
	MegaInt r = const_cast<MegaInt&>(n) - const_cast<MegaInt&>(d) * guess;
	if (r == 0)
		return guess;
	else if (r < 0) {
		while (r < 0) {
			guess--;
			r = const_cast<MegaInt&>(n) - const_cast<MegaInt&>(d) * guess;
		}
		return guess;
	}
	else {
		while (r >= d) {
			guess++;
			r = const_cast<MegaInt&>(n) - const_cast<MegaInt&>(d) * guess;
		}
		return guess;
	}
}

// Ctors
MegaInt::MegaInt(int i) { // conversion ctor
	if (i < 0) {
		sign = false;
		i = -i;
	}
	else {
		sign = true;
	}

	while (i > 0) {
		int lastDigit = i % 10;
		mega_int.push_front(intToChar(lastDigit));
		i = i / 10;
	}

	// Case 0
	if (mega_int.empty())
		mega_int.push_back('0');
}

MegaInt::MegaInt(const string& str) { // conversion ctor
	// Clean the string
	removeSpaces(const_cast<string&>(str));

	// Case empty
	if (str.empty()) {
		sign = true;
		mega_int.push_front('0');
		return;
	}

	// '-' is negative, otherwise is positive
	auto it = str.begin();
	if (*it == '-') {
		sign = false;
		it++;
	}
	else if (*it == '+') {
		sign = true;
		it++;
	}
	else if (isdigit(*it)) {
		sign = true;
	}
	else {
		// MegaInt must begin with '+' '-' or a digit
		cout << "Invalid MegaInt format" << endl;
		return;
	}

	// All zeros at the beginning shouldn't be added
	bool isPlaceholder;
	if (*it == '0')
		isPlaceholder = true;
	else
		isPlaceholder = false;

	while (it != str.end()) {
		if (!isdigit(*it)) {
			cout << "Invalid MegaInt format" << endl;
			return;
		}
			
		if (!isPlaceholder)
			mega_int.push_back(*it);
		else {
			if (*it != '0') {
				isPlaceholder = false;
				mega_int.push_back(*it);
			}
		}
		it++;
	}

	// Case "00000000" or "-00000000" or "+00000000"
	if (mega_int.empty()) {
		sign = true;
		mega_int.push_back('0');
	}
}

MegaInt::MegaInt(bool sign, const deque<char>& mega_int) : sign(sign), mega_int(mega_int) {}

MegaInt::MegaInt(const MegaInt& megaInt) { // copy ctor
	this->sign = megaInt.sign;
	this->mega_int = megaInt.mega_int;
}

MegaInt::~MegaInt() {} // dtor

// Calculation operators overloading
MegaInt MegaInt::operator+(const MegaInt& rhs) { // operator + overloading
	MegaInt result = *this;
	return result += rhs;
}

MegaInt& MegaInt::operator+=(const MegaInt& rhs) { // operator += overloading
	if (this->sign == rhs.sign) {
		this->mega_int = plus(this->mega_int, rhs.mega_int);
	}
	else {
		if (this->mega_int > rhs.mega_int) {
			this->mega_int = minus(this->mega_int, rhs.mega_int);
		}
		else if (this->mega_int < rhs.mega_int) {
			this->sign = rhs.sign;
			this->mega_int = minus(rhs.mega_int, this->mega_int);
		}
		else {
			this->sign = true;
			this->mega_int.clear();
			this->mega_int.push_front('0');
		}
	}
	normalize();
	return *this;
}

MegaInt& MegaInt::operator++() { // prefix increment operator overloading
	return *this += MegaInt(1);
}

MegaInt MegaInt::operator++(int) { // postfix increment operator overloading
	MegaInt result = *this;
	*this += MegaInt(1);
	return result;
}

MegaInt MegaInt::operator-(const MegaInt& rhs) { // operator - overloading
	MegaInt result = *this;
	return result -= rhs;
}

MegaInt& MegaInt::operator-=(const MegaInt& rhs) { // operator -= overloading
	if (this->sign != rhs.sign) {
		this->mega_int = plus(this->mega_int, rhs.mega_int);
	}
	else {
		if (this->mega_int > rhs.mega_int) {
			this->mega_int = minus(this->mega_int, rhs.mega_int);
		}
		else if (this->mega_int < rhs.mega_int) {
			this->sign = !this->sign;
			this->mega_int = minus(rhs.mega_int, this->mega_int);
		}
		else {
			this->sign = true;
			this->mega_int.clear();
			this->mega_int.push_front('0');
		}
	}
	normalize();
	return *this;
}

MegaInt& MegaInt::operator--() { // prefix decrement operator overloading
	return *this -= MegaInt(1);
}

MegaInt MegaInt::operator--(int) { // postfix decrement operator overloading
	MegaInt result = *this;
	*this -= MegaInt(1);
	return result;
}

MegaInt MegaInt::operator*(const MegaInt& rhs) { // operator * overloading
	MegaInt result = *this;
	return result *= rhs;
}

//MegaInt& MegaInt::operator*=(const MegaInt& rhs) { // M1 method operator *= overloading
//	if (*this == 0 || rhs == 0) {
//		*this = 0;
//	}
//	else {
//		MegaInt original = *this;
//		MegaInt counter;
//		if (!rhs.isPositive()) {
//			counter = --(-rhs);
//			this->sign = !this->sign;
//		}
//		else {
//			counter = const_cast<MegaInt&>(rhs) - 1;
//		}
//
//		while (counter != 0) {
//			this->mega_int = plus(this->mega_int, original.mega_int);
//			counter--;
//		}
//
//		normalize(this->mega_int);
//	}
//	
//	return *this;
//}

MegaInt& MegaInt::operator*=(const MegaInt& rhs) { // M2 method operator *= overloading
	MegaInt m;
	MegaInt n;
	if (this->length() < rhs.length()) {
		m = *this;
		n = rhs;
	}
	else {
		m = rhs;
		n = *this;
	}

	MegaInt partialSum;
	int mIndex = m.length() - 1;
	int leftShiftPos = 0;
	for (size_t i = 0; i < m.length(); i++) {
		deque<char> contributor = multiply(n.mega_int, m[mIndex--]);
		for (int j = 1; j <= leftShiftPos; j++)
			contributor.push_back('0'); // left-shift ... position
		partialSum.mega_int = plus(partialSum.mega_int, contributor);
		leftShiftPos++;
	}
	this->mega_int = partialSum.mega_int;

	if (!rhs.isPositive())
		this->sign = !this->sign;

	normalize();

	return *this;
}

MegaInt MegaInt::operator/(const MegaInt& rhs) { // operator / overloading
	MegaInt result = *this;
	return result /= rhs;
}

MegaInt& MegaInt::operator/=(const MegaInt& rhs) { // D1 method operator /= overloading
	if (rhs == 0) {
		cout << "Cannot divided by 0" << endl;
		return *this;
	}

	return divide_m2(const_cast<MegaInt&>(rhs), "quotient");
}

MegaInt MegaInt::operator%(const MegaInt& rhs) { // operator % overloading
	MegaInt result = *this;
	return result %= rhs;
}

MegaInt& MegaInt::operator%=(const MegaInt& rhs) { // operator %= overloading
	if (rhs == 0) {
		cout << "Cannot divided by 0" << endl;
		return *this;
	}

	return divide_m2(const_cast<MegaInt&>(rhs), "remainder");
}

MegaInt MegaInt::operator+(int rhs) { // operator + overloading
	MegaInt mRhs{ rhs };
	return (*this + mRhs);
}

MegaInt& MegaInt::operator+=(int rhs) { // operator += overloading
	MegaInt mRhs{ rhs };
	return (*this += mRhs);
}

MegaInt MegaInt::operator-(int rhs) { // operator - overloading
	MegaInt mRhs{ rhs };
	return (*this - mRhs);
}

MegaInt& MegaInt::operator-=(int rhs) { // operator -= overloading
	MegaInt mRhs{ rhs };
	return (*this -= mRhs);
}

MegaInt MegaInt::operator*(int rhs) { // operator * overloading
	MegaInt mRhs{ rhs };
	return (*this * mRhs);
}

MegaInt& MegaInt::operator*=(int rhs) { // operator *= overloading
	MegaInt mRhs{ rhs };
	return (*this *= mRhs);
}

MegaInt MegaInt::operator/(int rhs) { // operator / overloading
	MegaInt mRhs{ rhs };
	return (*this / mRhs);
}

MegaInt& MegaInt::operator/=(int rhs) { // operator /= overloading
	MegaInt mRhs{ rhs };
	return (*this /= mRhs);
}

MegaInt MegaInt::operator%(int rhs) { // operator % overloading
	MegaInt mRhs{ rhs };
	return (*this % mRhs);
}

MegaInt& MegaInt::operator%=(int rhs) { // operator %= overloading
	MegaInt mRhs{ rhs };
	return (*this %= mRhs);
}

MegaInt operator+(int lhs, const MegaInt& rhs) {
	MegaInt result = lhs;
	return (result += rhs);
}

MegaInt operator-(int lhs, const MegaInt& rhs) {
	MegaInt result = lhs;
	return (result -= rhs);
}

MegaInt operator*(int lhs, const MegaInt& rhs) {
	MegaInt result = lhs;
	return (result *= rhs);
}

MegaInt operator/(int lhs, const MegaInt& rhs) {
	MegaInt result = lhs;
	return (result /= rhs);
}

MegaInt operator%(int lhs, const MegaInt& rhs) {
	MegaInt result = lhs;
	return (result %= rhs);
}

MegaInt MegaInt::operator-() const { // unary operator - overloading
	bool newSign;
	if (*this == 0)
		newSign = true;
	else
		newSign = !sign;
	return MegaInt(newSign, mega_int);
}

MegaInt MegaInt::operator+() const { // unary operator + overloading
	if (sign)
		return MegaInt(sign, mega_int);
	else
		return MegaInt(!sign, mega_int);
}

// Relational operators overloading
bool MegaInt::operator==(const MegaInt& rhs) const { // operator == overloading
	// Different sign means different value
	if (this->sign != rhs.sign)
		return false;

	return (this->mega_int == rhs.mega_int);
}

bool MegaInt::operator==(int rhs) const { // operator == overloading
	MegaInt mRhs{ rhs };
	return (*this == mRhs);
}

bool operator==(const deque<char>& lhs, const deque<char>& rhs) {
	// Different number of digits means different value
	if (lhs.size() != rhs.size())
		return false;

	// Compare digit by digit from left to right
	auto itLhs = lhs.begin();
	auto itRhs = rhs.begin();
	while (itLhs != lhs.end()) {
		if (*itLhs != *itRhs)
			return false;
		itLhs++;
		itRhs++;
	}

	return true;
}

bool MegaInt::operator<(const MegaInt& rhs) const { // operator < overloading
	// Negative number is smaller than Positive number
	if (!this->isPositive() && rhs.isPositive())
		return true;
	else if (this->isPositive() && !rhs.isPositive())
		return false;

	// Both have same sign, compare the absolute value
	bool isLhsSmaller = (this->mega_int < rhs.mega_int);

	// Both numbers are Positive
	if (this->isPositive() && rhs.isPositive()) {
		if (isLhsSmaller)
			return true;
		else
			return false;
	}
	else { // Both numbers are Negative
		if (isLhsSmaller)
			return false;
		else
			return true;
	}
}

bool MegaInt::operator<(int rhs) const { // operator < overloading
	MegaInt mRhs{ rhs };
	return (*this < mRhs);
}

bool operator<(const deque<char>& lhs, const deque<char>& rhs) {
	// Shorter number is smaller
	if (lhs.size() < rhs.size())
		return true;
	else if (lhs.size() > rhs.size())
		return false;
	else { // Same length
		auto itLhs = lhs.begin();
		auto itRhs = rhs.begin();
		while (itLhs < lhs.end()) {
			if (*itLhs < *itRhs) {
				return true;
			}
			else if (*itLhs > *itRhs) {
				return false;
			}
			itLhs++;
			itRhs++;
		}
		return false; // case equal
	}
}

bool MegaInt::operator>(const MegaInt& rhs) const { // operator > overloading
	return (rhs < *this);
}

bool MegaInt::operator>(int rhs) const {
	MegaInt mRhs{ rhs };
	return (*this > mRhs);
}

bool operator>(const deque<char>& lhs, const deque<char>& rhs) {
	return (rhs < lhs);
}

bool MegaInt::operator<=(const MegaInt& rhs) const { // operator <= overloading
	return !(rhs < *this);
}

bool MegaInt::operator<=(int rhs) const {
	MegaInt mRhs{ rhs };
	return (*this <= mRhs);
}

bool operator<=(const deque<char>& lhs, const deque<char>& rhs) {
	return !(rhs < lhs);
}

bool MegaInt::operator>=(const MegaInt& rhs) const { // operator >= overloading
	return !(*this < rhs);
}

bool MegaInt::operator>=(int rhs) const {
	MegaInt mRhs{ rhs };
	return (*this >= mRhs);
}

bool operator>=(const deque<char>& lhs, const deque<char>& rhs) {
	return !(lhs < rhs);
}

bool MegaInt::operator!=(const MegaInt& rhs) const { // operator != overloading
	bool rs = !(*this == rhs);
	return rs;
}

bool MegaInt::operator!=(int rhs) const {
	MegaInt mRhs{ rhs };
	return (*this != mRhs);
}

bool operator!=(const deque<char>& lhs, const deque<char>& rhs) {
	return !(lhs == rhs);
}

bool operator==(const int lhs, const MegaInt& rhs) {
	return (MegaInt{ lhs } == rhs);
}

bool operator<(const int lhs, const MegaInt& rhs) {
	return (MegaInt{ lhs } < rhs);
}

bool operator>(const int lhs, const MegaInt& rhs) {
	return (MegaInt{ lhs } > rhs);
}

bool operator<=(const int lhs, const MegaInt& rhs) {
	return (MegaInt{ lhs } <= rhs);
}

bool operator>=(const int lhs, const MegaInt& rhs) {
	return (MegaInt{ lhs } >= rhs);
}

bool operator!=(const int lhs, const MegaInt& rhs) {
	return (MegaInt{ lhs } != rhs);
}

// Other operators overloading
MegaInt& MegaInt::operator=(const MegaInt& megaInt) { // operator= overloading
	this->sign = megaInt.sign;
	this->mega_int = megaInt.mega_int;
	return *this;
}

MegaInt& MegaInt::operator=(const int rhs) { // operator= overloading
	MegaInt mRhs{ rhs };
	return (*this = mRhs);
}

ostream& operator<<(ostream& out, const MegaInt& megaInt) { // operator<< overloading
	if (megaInt.isPositive())
		out << '+';
	else
		out << '-';

	for (auto it = megaInt.mega_int.begin(); it != megaInt.mega_int.end(); it++)
		out << *it;

	return out;
}

int MegaInt::operator[](size_t index) const { // operator[] overloading
	if (index >= this->length()) {
		cout << "Index OutOfRange" << endl;
		throw "Index OutOfRange";
	}
		
	return charToInt(mega_int.at(index));
}

// Utility functions
bool MegaInt::isPositive() const { // get the sign of MegaInt
	return sign;
}

bool MegaInt::isEven() const { // check if the MegaInt is even number
	return ((*this)[this->length() - 1] % 2 == 0);
}

size_t MegaInt::length() const { // get the length of MegaInt
	return (this->mega_int.size());
}

MegaInt MegaInt::subMegaInt(size_t beginPos, size_t endPos) {
	if ((beginPos >= endPos) || (beginPos >= this->length()) || (endPos > this->length())) {
		cout << "Index OutOfRange" << endl;
		throw "Index OutOfRange";
	}

	MegaInt result;
	for (size_t i = beginPos; i < endPos; i++)
		result.mega_int.push_back(this->mega_int.at(i));
	result.sign = this->sign;
	result.normalize();
	return result;
}