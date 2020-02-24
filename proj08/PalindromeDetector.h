/* The header file for the PalindromeDetector class
 * PalindromeDetector.h
 *
 *  Created on: Apr 18, 2019
 *      Author: Duncan Van Keulen (djv78)
 */

#ifndef PALINDROMEDETECTOR_H_
#define PALINDROMEDETECTOR_H_

#include <string>
#include <iostream>
#include <fstream>
#include <cassert>
#include "Stack.h"
#include "ArrayQueue.h"
using namespace std;

class PalindromeDetector {
public:
	// default constructor
	PalindromeDetector() { inFile = outFile = ""; }
	// explicit constructor
	PalindromeDetector(const string& inFilename, const string& outFilename);

	// getter methods for input file and output file
	string getInFile() const { return inFile; }
	string getOutFile() const { return outFile; }

	// palindrome detection methods
	bool isPalindrome(const string& line) const;
	void detectPalindromes();

private:
	string inFile;
	string outFile;
};

#endif /* PALINDROMEDETECTOR_H_ */
