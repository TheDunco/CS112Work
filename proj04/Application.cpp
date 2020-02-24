/*
 * Application.cpp provides a textual UI for a user to use the Matrix Class
 *
 *  Created on: Mar 4, 2019
 *      Author: Ben Brower (bpb9)
 *      Author: Duncan Van Keulen (djv78)
 */

#include "Application.h"


void Application::Menu() {
	//Create a while loop that continues to display the menu after each action is performed until "0" is entered
	while (true) {
		//Welcome the user and display the menu
		cout << " " << endl;
		cout << "Welcome to the Matrix Application!" << endl;

		cout << "Here are your options:" << endl;
		cout << "     1. Matrix Addition" << endl;
		cout << "     2. Matrix Subtraction" << endl;
		cout << "     3. Matrix Transposition" << endl;
		cout << "     0. Exit Application" << endl;
		cout << "(Any letters entered first also exits the Applicaiton.)" << endl;

		//Have the user enter a choice and change that string into type unsigned
		cout << "Enter your choice: " << flush;
		string choicestr;
		getline(cin, choicestr);
		unsigned choice = atoi(choicestr.c_str() );
		cout << endl;

		//Check to see that the first digit entered is not a letter or 0, 1, 2, or 3
		if (choice != 1 and choice != 2 and choice != 3 and choice != 0) {
			cout << "That was not a valid entry.  Please enter a new choice." << endl;
		}

		//If the user entered 0, break from the loop and stop displaying the Application
		if (choice == 0) {
			cout << "Exiting Application..." << endl;
			break;
		}

		//If the user entered 1, add two matrices together
		if (choice == 1) {
			this->addMatrices();
		}


		//If the user entered 2, subtract the second matrix from the first
		if (choice == 2) {
			this->subtractMatrices();
		}

		//If the user entered 3, transpose the matrix
		if (choice == 3) {
			this->transposeMatrices();
		}
	}
}

void Application::addMatrices() {
	//Ask for two files and use the readFrom method to create matrices from the files
	cout << "Enter a file name that contains your first matrix: " << flush;
	string filename1 = " ";
	getline(cin, filename1);
	Matrix<double> m1;
	m1.readFrom(filename1);

	cout << "Enter a file name that contains your second matrix: " << flush;
	string filename2 = " ";
	getline(cin, filename2);
	Matrix<double> m2;
	m2.readFrom(filename2);

	//Do the addition operation and print out the final matrix
	cout << endl;
	cout << "Here is your result after addition: " << endl;
	Matrix<double> m3;
	m3 = m1 + m2;
	for (unsigned i = 0; i < m3.getRows(); i++) {
		for (unsigned j = 0; j < m3.getColumns(); j++) {
			cout << m3[i][j] << " " << flush;
			if ((j+1) == m3.getColumns()) {
				cout << endl;
			}
		}
	}
}

void Application::subtractMatrices() {
	//Ask for two files and use the readFrom method to create matrices from the files
	cout << "Enter a file name that contains your first matrix: " << flush;
	string filename1 = " ";
	getline(cin, filename1);
	Matrix<double> m1;
	m1.readFrom(filename1);

	cout << "Enter a file name that contains your second matrix: " << flush;
	string filename2 = " ";
	getline(cin, filename2);
	Matrix<double> m2;
	m2.readFrom(filename2);

	//Do the subtraction operation and print out the final matrix
	cout << endl;
	cout << "Here is your result after subtraction: " << endl;
	Matrix<double> m3;
	m3 = m1 - m2;
	for (unsigned i = 0; i < m3.getRows(); i++) {
		for (unsigned j = 0; j < m3.getColumns(); j++) {
			cout << m3[i][j] << " " << flush;
			if ((j+1) == m3.getColumns()) {
				cout << endl;
			}
		}
	}
}

void Application::transposeMatrices() {
	//Ask for a file name and use the readFrom method to create a matrix from the file
	cout << "Enter a file name that contains your matrix: " << flush;
	string filename1 = " ";
	getline(cin, filename1);
	Matrix<double> m1;
	m1.readFrom(filename1);

	//Do the transposition operation and print out the final matrix
	cout << endl;
	cout << "Here is your result after transposition: " << endl;
	Matrix<double> m3;
	m3 = m1.getTranspose();
	for (unsigned i = 0; i < m3.getRows(); i++) {
		for (unsigned j = 0; j < m3.getColumns(); j++) {
			cout << m3[i][j] << " " << flush;
			if ((j+1) == m3.getColumns()) {
				cout << endl;
			}
		}
	}
}

Application::~Application() {
	// TODO Auto-generated destructor stub
}
