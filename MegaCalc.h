#pragma once

#ifndef MEGACALC_H
#define MEGACALC_H

#include "MegaInt.h"
#include <string>

using std::string;
using std::cin;
using std::cout;
using std::endl;

class MegaCalc {
private:
	MegaInt accumulator;
	MegaInt rhs;
	string cmdLine;
	char command;
	static void factorial(const MegaInt&);
	static void hailstones(const MegaInt&);
	void parseCmd(); // Validate the command
	void removeSpaces();
public:
	MegaCalc();
	virtual ~MegaCalc();
	void run();
};

#endif