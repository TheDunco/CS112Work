/*
 * application.cpp
 *
 * Proj03
 *
 * @author: Josh Ridder (jmr59)
 * @author: Duncan Van Keulen (djv78)
 *
 *  Created on: Feb 21, 2019
 */


#include "application.h"
#include "Vec.h"
#include <iostream>
using namespace std;

/* Application for Vec class
 *
 * Let's the user enter and add up vectors
 * how ever many dimensions they want
 */
void application::doStuff() {
	int dimensions;

	// ask the user to enter the number of dimensions they want
	cout << "Enter a number of dimensions for the vectors: " << flush;
	cin >> dimensions;

	// get the starting coordinates from the user
	cout << "Enter the starting coordinates: " << endl;
	Vec startingVec(dimensions);
	double position;
	for (int i = 0; i < dimensions; i++) {
		cout << i << " value: " << flush;
		cin >> position;
		startingVec.setItem(i, position);
	}

	// initialize needed variables and vector objects
	string userResponse;
	Vec userVec(dimensions);
	double userValue;
	Vec resultVec(dimensions);
	resultVec = startingVec;

	cout << "Enter " << dimensions << " dimensional vectors: " << endl;

	// repeatedly get the other vectors from the user until they want to stop
	while (userResponse != "q") {
		for (int i = 0; i < dimensions; i++) {
			cout << i << " value: " << flush;
			cin >> userValue;
			userVec.setItem(i, userValue);
		}
		resultVec = resultVec + userVec; // add up the vectors as more vectors are entered
		cout << "{" << flush;

		// print out the vector for the user to see
		for (int i = 0; i < dimensions - 1; i++) {
			cout << resultVec.getItem(i) << ", " << flush;
		}

		// ask the user if they want to quit
		cout << resultVec.getItem(dimensions - 1) << "}" << endl;
		cout << "Enter q to quit adding vectors or any key to continue: " << flush;
		cin >> userResponse;
	}
}
