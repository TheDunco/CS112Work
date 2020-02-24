/*
 * ReversePoemTester.cpp is the implemenation of the ReversePoemTester class.
 *
 *  Created on: Mar 31, 2019
 *      Author: Duncan Van Keulen (djv78)
 */

#include "ReversePoemTester.h"

void ReversePoemTester::runTests() {
	cout << "Testing Reverse Poem Class..." << endl;
	testConstructor();
	testGetterMethods();

	cout << "All tests passed!" << endl;
}

void ReversePoemTester::testConstructor() {
	cout << "- constructor... " << flush;
	ReversePoem rp("poems/cats.txt");
	assert( rp.title == "Cats" );
	cout << " 0a " << flush;
	assert( rp.author == "Leo J. Smada" );
	cout << " 0b " << flush;
	assert( rp.body == "I love it when cats rub against me.\nI could never say\nI hate those purring felines.\n\n");
	cout << " 0c " << flush;
	assert( rp.reverseBody == "\nI hate those purring felines.\nI could never say\nI love it when cats rub against me.\n");
	cout << " 0d " << flush;

	cout << " Passed!" << endl;
}

void ReversePoemTester::testGetterMethods() {
	cout << "- getter methods... " << flush;
	ReversePoem revPoem("poems/cats.txt");
	assert( revPoem.getTitle() == "Cats" );
	cout << " 0 " << flush;
	assert( revPoem.getAuthor() == "Leo J. Smada" );
	cout << " 1 " << flush;
	assert( revPoem.getBody() == "I love it when cats rub against me.\nI could never say\nI hate those purring felines.\n\n");
	cout << " 2 " << flush;
	assert( revPoem.getBodyReversed() == "\nI hate those purring felines.\nI could never say\nI love it when cats rub against me.\n");
	cout << " 3 " << flush;

	cout << " Passed!" << endl;
}
