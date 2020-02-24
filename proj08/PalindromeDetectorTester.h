/* The header file for the unit test of the PalindromeDetector class
 * palindromeTester.h
 *
 *  Created on: Apr 16, 2019
 *      Author: Duncan Van Keulen (djv78)
 */

#ifndef PALINDROMEDETECTORTESTER_H_
#define PALINDROMEDETECTORTESTER_H_

#include "PalindromeDetector.h"
#include <iostream>
#include <cassert>
#include <fstream>
using namespace std;

class PalindromeDetectorTester {
public:
	void runTests();
	void testConstructors();
	void testIsPalindrome();
	void testDetectPalindromes();
};

#endif /* PALINDROMEDETECTORTESTER_H_ */
