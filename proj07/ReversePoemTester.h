/*
 * ReversePoemTester.h is the header file for the ReversePoemTester class.
 *
 *  Created on: Mar 31, 2019
 *      Author: Duncan Van Keulen (djv78)
 */

#ifndef REVERSEPOEMTESTER_H_
#define REVERSEPOEMTESTER_H_

#include "ReversePoem.h"
#include <iostream>
#include <cassert>
#include <stdexcept>
using namespace std;

class ReversePoemTester {
public:
	void runTests();
	void testConstructor();
	void testGetterMethods();
};

#endif /* REVERSEPOEMTESTER_H_ */
