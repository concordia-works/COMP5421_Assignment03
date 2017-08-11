#include "MegaCalc.h"

void MegaCalc::factorial(const MegaInt& mega_int) {
	if (mega_int == 0)
		cout << "0! = " << MegaInt{ 1 } << endl;
	else if (mega_int > 0) {
		MegaInt factorial = 1;
		for (MegaInt mI = 1; mI <= mega_int; mI++) {
			cout << mI << "! = " << (factorial *= mI) << endl;
		}
	}
	else
		cout << "Number must be greater or equal to 0" << endl;
}

void MegaCalc::hailstones(const MegaInt& mega_int) {
	if (mega_int > 0) {
		MegaInt temp = mega_int;
		cout << "> " << temp << endl;
		int length = 1;
		while (temp != 1) {
			if (temp.isEven())
				cout << "> " << (temp /= 2) << endl;
			else
				cout << "> " << ((temp *= 3) += 1) << endl;
			length++;
		}
		cout << endl << "length of the hailstone(" << mega_int << ") sequence: " << MegaInt(length) << endl;
	}
	else
		cout << "Number must be greater than 0" << endl;
}

void MegaCalc::parseCmd() { // Validate the command
	removeSpaces();
	if (!cmdLine.empty()) {
		command = cmdLine.front();
		rhs = cmdLine.substr(1);
	}
	switch (command) {
		case '=':
			accumulator = rhs;
			cout << endl;
			break;
		case '+':
			accumulator += rhs;
			cout << endl;
			break;
		case '-':
			accumulator -= rhs;
			cout << endl;
			break;
		case '*':
			accumulator *= rhs;
			cout << endl;
			break;
		case '/':
			accumulator /= rhs;
			cout << endl;
			break;
		case '%':
			accumulator %= rhs;
			cout << endl;
			break;
		case 'h':
			hailstones(accumulator);
			cout << endl;
			break;
		case 'f':
			factorial(accumulator);
			cout << endl;
			break;
		case 'c':
			accumulator = 0;
			cout << endl;
			break;
		case 'n':
			accumulator = -accumulator;
			cout << endl;
			break;
		case 'q':
			break;
		default:
			cout << "Invalid command" << endl << endl;
			break;
	}
}

void MegaCalc::removeSpaces() { // remove all white spaces from a string
	if (!cmdLine.empty()) {
		auto it = cmdLine.begin();
		while (it != cmdLine.end()) {
			if ((*it == ' ') || (*it == '\t'))
				cmdLine.erase(it);
			else
				it++;
		}
	}
}

MegaCalc::MegaCalc() {}

MegaCalc::~MegaCalc() {}

void MegaCalc::run() {
	cout << "Welcome to MegaCalculator" << endl;
	cout << "=========================" << endl << endl;

	while (command != 'q') {
		cout << "Accumulator: " << accumulator << endl;
		cout << "Enter input: ";
		getline(cin, cmdLine);
		parseCmd();
	}
}