/* array.cpp defines "C style" array operations
 * Name: Duncan Van Keulen
 * Date: 12 February 2019
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 */

#include "array.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

/*
 * precondition: a is an array of size size
 * @param double *a: The pointer to an array of doubles
 * @param unsigned size: The size of the array
 * postcondition: array will be initialized to values 0 - size
 */
void initialize(double *a, unsigned size) {
	int val = 0;
	for (unsigned i = 0; i < size; i++) {
		val = i+1;
		a[i] = val;
	}
}
/*
 * precondition: a is an array of size size
 * @param double *a: The pointer to an array of doubles
 * @param unsigned size: The size of the array
 * postcondition: the contents of the array will be
 * 							printed to the terminal
 */
void print(double *a, unsigned size) {
	for (unsigned i = 0; i < size; i++) {
		cout << *a << '\t';
		a++;
	}
}

/*
 * precondition: a is an array of size size
 * @param double *a: The pointer to an array of doubles
 * @param unsigned size: The size of the array
 * returns: a double of the average of the values in the array
 */
double average(double *a, unsigned size) {
	double total = 0;
	for (unsigned i = 0; i < size; i++) {
		total += *a;
		a++;
	}
	return total / size;
}

/*
 * precondition: a is an array of size size
 * @param double *a: The pointer to an array of doubles
 * @param unsigned size: The size of the array
 * returns: a double of the sum of the values in the array
 */
double sum(double *a, unsigned size) {
	double total = 0;
	for (unsigned i = 0; i < size; i++) {
		total += *a;
		a++;
	}
	return total;
}

/*
 * precondition: a is an array of size size
 * @param istream& in: an istream that will be used to read
 * 					   the values into a
 * @param double *a: The pointer to an array of doubles
 * @param unsigned size: The size of the array
 * returns: a double of the sum of the values in the array
 */
void read(istream& in, double *a, unsigned size) {
	for (unsigned i = 0; i < size; i++) {
		if (!(in)) { break; }
		double line;
		in >> line;
		a[i] = line;
	}
}

/*
 * precondition: a is an array of size size and there exists
 * 			     a file with name fileName containing numbers
 * @param const string& fileName: a string of the file
 * 								  containing the values
 * 								  to fill the array with
 * @param double *a: The pointer to an array of doubles
 * postcondition: array will be filled with the values in the file
 * 				  (The first value of the file will be used as the
 * 				  size of the array)
 */
void fill(const string& fileName, double *&a, int &numValues) {
	ifstream fin(fileName.c_str());
	assert( fin.is_open() );

	fin >> numValues;
	delete [] a;
	a = new double[numValues];

	for (int i = 0; i < numValues; i++) {
		fin >> a[i];
	}

	fin.close();
}

/*
 * precondition: a is an array of size size
 * @param double *a: The pointer to an array of doubles
 * @param unsigned oldSize: The initial size of the array when
 * 						    passed into the function
 * @param unsigned newSize: The desired new size of the array
 * postcondition: array will have new size newSize,
 * 				  if newSize was less than oldSize, array was truncated
 */
void resize(double *&a, unsigned oldSize, unsigned newSize) {
	double val = 0;
	double * newA = new double[newSize];
	if (newSize > oldSize) {
		for (unsigned i = 0; i < oldSize; i++) {
			newA[i] = *&a[i];
		}
		delete [] a;
		a = newA;
	}

	else if (newSize < oldSize) {
		for (unsigned i = 0; i < newSize; i++) {
			val = *&a[i];
			newA[i] = val;
		}
		delete [] a;
		a = newA;
	}
}

/* precondition: arrays 1, 2, and 3 are arrays with size of their
 * 										respective size variables
 * @param double *a1: an array of size...
 * @param int size1
 *
 * @param double *a2: an array of size...
 * @param int size2
 *
 * @param double *&a3: an array of size...
 * @param &size3
 *
 * postcondition: Array 3 will be a concatenation of array 1 and 2 with size
 */
void concat(double *a1, int size1, double *a2, int size2, double *&a3, int &size3) {
	size3 = size1 + size2;

	double * b = new double[size3];

	for (int i = 0; i < size1; i++) {
		b[i] = a1[i];
	}

	int j = 0;
	for (int i = size1; i < size3; i++) {
		b[i] = a2[j];
		j++;
	}
	delete [] a3;
	a3 = b;
}

