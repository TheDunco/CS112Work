/* The header source for the unit test of the PalindromeDetector class
 * palindromeTester.cpp
 *
 *  Created on: Apr 16, 2019
 *      Author: Duncan Van Keulen (djv78)
 */

#include "PalindromeDetectorTester.h"

void PalindromeDetectorTester::runTests() {
	cout << "Testing PalindromeDetector class... " << endl;
	testConstructors();
	testIsPalindrome();
	testDetectPalindromes();

	cout << "All tests passed!" << flush;
}

void PalindromeDetectorTester::testConstructors() {
	cout << "- constructors (and getter methods)... " << flush;

	// default constructor
	PalindromeDetector defPD;
	assert( defPD.getInFile() == "" );
	assert( defPD.getOutFile() == "" );
	cout << " 0 " << flush;

	// explicit constructor
	PalindromeDetector pd("palindromeTest.txt", "palindromeTestOut.txt");
	assert( pd.getInFile() == "palindromeTest.txt");
	cout << " 1a " << flush;

	assert ( pd.getOutFile() == "palindromeTestOut.txt");
	cout << " 1b " << flush;

	cout << " Passed!" << endl;
}

void PalindromeDetectorTester::testIsPalindrome() {
	cout << "- isPalindrome()... " << flush;

	PalindromeDetector pd;

	// make sure it correctly identifies true palindromes
	assert( pd.isPalindrome("kayak") == true );
	assert( pd.isPalindrome("racecar") == true );
	assert( pd.isPalindrome("madamimadam") == true );
	cout << " 0 " << flush;

	// make sure it correctly identifies false palindromes
	assert( pd.isPalindrome("blah") == false );
	assert( pd.isPalindrome("Hi, this is not a palindrome") == false );
	assert( pd.isPalindrome(" ") == false );
	assert( pd.isPalindrome("\n") == false );
	assert( pd.isPalindrome("") == false );
	assert( pd.isPalindrome("Sit on a potato pan, Otis!") == false ); // although this is a palindrome,
	//								  this method is not built to get around punctuation/capitalization
	cout << " 1 " << flush;

	cout << " Passed!" << endl;
}

void PalindromeDetectorTester::testDetectPalindromes() {
	cout << "- detectPalindromes()... " << flush;
	PalindromeDetector pd("PDTest.txt", "PDTestOut.txt");

	pd.detectPalindromes();

	ifstream outFin("PDTestOut.txt");
	assert( outFin.is_open() );

	// test each line of the PDTest.txt file to make sure it's behaving correctly
	string oLine;
	getline(outFin, oLine);
	assert( oLine == R"("Madam, I'm Adam" ***)");
	cout << " 0a " << flush;
	getline(outFin, oLine);
	assert( oLine == "This is not a palindrome");
	cout << " 0b " << flush;
	getline(outFin, oLine);
	assert( oLine == "");
	cout << " 0c " << flush;
	getline(outFin, oLine);
	assert( oLine == "neither is that blank line or this, but the next line should be");
	cout << " 0d " << flush;
	getline(outFin, oLine);
	assert( oLine == R"("Sit on a potato pan, Otis!" ***)");
	cout << " 0e " << flush;
	getline(outFin, oLine);
	assert( oLine == "kayak ***");
	cout << " 0f " << flush;
	getline(outFin, oLine);
	assert( oLine == "racecar ***");
	cout << " 0g " << flush;

	outFin.close();

 	// run palindrome detection on palindromeTest.txt
 	PalindromeDetector pd1("palindromeTest.txt", "palindromeTestOutput.txt");
 	pd1.detectPalindromes();
 	cout << " 1 (look at palindromeTestOutput.txt) " << flush;

	cout << " Passed!" << endl;
}
