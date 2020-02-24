/* The source file for the Palindrome Detector class
 * PalindromeDetector.cpp
 *
 *  Created on: Apr 18, 2019
 *      Author: Duncan Van Keulen (djv78)
 */

#include "PalindromeDetector.h"

/* Constructor for the PalindromeDetector class
 * @param const string& inFilename: the name of the desired input file
 * @param const string& outFilename: the name of the desired output file
 * postcondition: The inFile and outFile will be initialized
 * 				  based on the input filename.
 * @author: Duncan Van Keulen (project)
 */
PalindromeDetector::PalindromeDetector(const string& inFilename, const string& outFilename) {
	inFile = inFilename;
	outFile = outFilename;

	// this is logic to automatically add "Out" before the .txt extension to determine
	// the outFile name automatically
//	string::size_type position;
//	position = filename.find ('.');
//	outFile = filename.substr(0,position) + "Out" + ".txt";

}

/* Detect if a string is a palindrome
 * @param const string& line: The one-line string to be examined
 * precondition: PalindromeDetector must exist, string must not contain
 * 		punctuation (including spaces) and letters must be a consistent case
 * @return: A bool indicating the whether the string is a palindrome or not
 * @author: Duncan Van Keulen (djv78)
 */
bool PalindromeDetector::isPalindrome(const string& line) const {
	Stack<char> pStack(1);
	ArrayQueue<char> pQueue(1);

	for (unsigned index = 0; index < line.size(); index++) {
		// try to push character to the stack and double size if full
		try {
			pStack.push( line[index] );
		} catch (const StackException& se) {
			pStack.setCapacity( (pStack.getCapacity() * 2) );
			pStack.push( line[index] );
		}

		// try to append character to the queue and double size if full
		try {
			pQueue.append( line[index] );
		} catch (const FullQueueException& fq) {
			pQueue.setCapacity( (pQueue.getCapacity() * 2) );
			pQueue.append( line[index] );
		}
	}

	// if line's size is 0 or 1, we're saying it's not a palindrome
	if ( (pStack.getSize() == 1 && pQueue.getSize() == 1) ||
			(pStack.getSize() == 0 && pQueue.getSize() == 0) ) {
		return false;
	}

	// if any of the characters does not match forward and backward,
	// return false because it's not a palindrome
	while ( !pStack.isEmpty() && !pQueue.isEmpty() ) {
		if ( pStack.pop() != pQueue.remove() ) {
			return false;
		}
	}

	return true;
}

/* Detect palindromes in a file
 * Opens streams for the inFile and outFile and
 * writes asterisks after lines that are palindromes in
 * the out file
 *
 * precondition: inFile must be correctly initialized to a file name
 * postcondition: asterisks will be written after the lines that are
 * palindromes in the file with outFile handle
 *
 * @author: Duncan Van Keulen (project)
 */
void PalindromeDetector::detectPalindromes() {
	ifstream inFStream(inFile);
	ofstream outFStream(outFile);
	assert( inFStream.is_open() );
	assert( outFStream.is_open() );
	string line;

	// loop until the end of the file
	while (inFStream) {
		getline(inFStream, line);
		outFStream << line;

		// strip punctuation and case
		string strippedLine;
		for (unsigned i = 0; i < line.size(); i++) {
			// ignore punctuation
			if (ispunct( line[i] ) || line[i] == ' ') {
				continue;
			}
			// otherwise, concatenate the lowercased character to strippedString
			strippedLine += tolower( line[i] );
		}
		// add asterisks and a newline if it is a palindrome
		if ( isPalindrome(strippedLine) ) {
			outFStream << " ***";
		}
		outFStream << "\n";
	}

	// close the streams
	inFStream.close();
	outFStream.close();

}
