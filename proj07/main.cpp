/*
 * main.cpp runs the Stack tests and is the
 * application for the Reverse Poem class.
 *
 *  Created on: Mar 30, 2019
 *  	Started by: Joel Adams, for CS 112 at Calvin College.
 *      Author: Duncan Van Keulen (djv78)
 */

#include "ReversePoem.h"
#include "StackTester.h"
#include "ReversePoemTester.h"
#include "ReversePoem.h"
#include <iostream>
using namespace std;

int main() {
	// run the class unit tests
	StackTester st;
	st.runTests();
	ReversePoemTester rpt;
	rpt.runTests();

	// CLI Mini Application
    cout << "\nEnter the name of the poem file: ";
    string poemFile;
    cin >> poemFile;

	ReversePoem reversePoem( poemFile );
	cout << reversePoem.getTitle() << "\n"
			<< reversePoem.getAuthor() << "\n"
			<< "\n*** Top-To-Bottom ***\n\n"
			<< reversePoem.getBody()
			<< "\n\n*** Bottom-To-Top ***\n\n"
			<< reversePoem.getBodyReversed()
			<< endl;
}


