/* The implementation file for the BST height experiment
 * Experiment.cpp
 *
 *  Created on: Apr 27, 2019
 *      Author: Duncan Van Keulen (djv78)
 */

#include "Experiment.h"

/* Set the file name of the Experiment object
 * precondition: Experiment must exist
 * postcondition: myFile will be set to the file the user enters
 */
void Experiment::setFileName() {
	cout << "Enter name of file containing random integers: " << flush;
	cin >> myFile;
}

/* Run the Experiment on myFile
 * Outputs the results to the console
 */
void Experiment::run() {
	unsigned duplicates = 0;
	long val;

	ifstream fin( myFile.c_str() );
	if ( !fin.is_open() ) {
		cout << "Incorrect file name!" << endl;
		setFileName();
	}

	assert( fin.is_open() );

	while (fin) {
		fin >> val;
		try {
			myBST.insert(val);
		} catch (const Exception& bst) {
			duplicates++;
		}
	}
	// compensate for extra random duplicate that isn't actually there...
	duplicates--;

	// display the results
	cout << "Ran experiment on " << myFile << endl
			<< "BST height: " << myBST.getHeight() << endl
			<< "Duplicates: " << duplicates << endl << endl;
	fin.close();
}

/* Main execution loop
 * Ask the user if they want to continue, then
 * run the argument if the do, and repeat
 */
void Experiment::loop() {
	string response;
	cout << "Continue (y/n) " << flush;
	cin >> response;
	while (response != "n") {
		myBST.~BST();
		setFileName();
		run();
		cout << "Continue (y/n) " << flush;
		cin >> response;
	}
	cout << "Goodbye" << flush;
	exit(0);

}
