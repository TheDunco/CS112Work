/* Vec.cpp defines the methods for Vec, a simple vector class.
 * Date: 2-19-19
 * Begun by: Joel C. Adams, for CS 112 at Calvin College.
 * @author: Josh Ridder (jmr59)
 * @author: Duncan Van Keulen (djv78)
 * Josh Ridder:
 *    operator[] (write)
 *    != operator
 *    readFrom
 *    + operator
 * Duncan Van Keulen:
 * 	  operator[] (read)
 * 	  writeTo
 * 	  - operator
 * 	  * operator
 */
 
#include "Vec.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
using namespace std;

typedef double Item;

Vec::Vec() {
	mySize = 0;
	myArray = NULL;
}

Vec::~Vec() {
	delete [] myArray;
	myArray = NULL;
	mySize = 0;
}

Vec::Vec(unsigned size) {
	mySize = size;
	if (size > 0) {
		myArray = new Item[size];
		for (unsigned i = 0; i < size; i++) {
			myArray[i] = 0;
		}
	}
	else {
		myArray = NULL;
	}
}

Vec::Vec(const Vec& original) {
	mySize = original.mySize;
	if (mySize > 0) {
		myArray = new Item[mySize];
		for (unsigned i = 0; i < mySize; i++) {
			myArray[i] = original.myArray[i];
		}
	}
	else {
		myArray = NULL;
	}
}

Vec& Vec::operator=(const Vec& original) {
	if (mySize != original.mySize) {
		if (mySize > 0) {
			delete [] myArray;
			myArray = NULL;
		}
		if (original.mySize > 0) {
			myArray = new Item[original.mySize];
		}
	}
	mySize = original.mySize;
	for (unsigned i = 0; i < mySize; i++) {
		myArray[i] = original.myArray[i];
	}


      return *this;
}

void Vec::setItem(unsigned index, const Item& it) {
	if (index < mySize){
		myArray[index] = it;
	}
	else {
		throw range_error("Invalid index given to setItem method");
	}
}

Item Vec::getItem(unsigned index) const {
	if (index < mySize) {
		return myArray[index];
	}
	else {
		throw range_error("Invalid index given to getItem method");
	}
}

void Vec::setSize(unsigned newSize) {
	if (mySize != newSize) {
		if (newSize == 0) {
			delete [] myArray;
			myArray = NULL;
			mySize = 0;
		}
		else {
			Item* newArray = new Item[newSize];
			if (mySize < newSize) {
				for (unsigned i = 0; i < mySize; i++) {
					newArray[i] = myArray[i];
				}
				for (unsigned i = mySize; i < newSize; i++) {
					newArray[i] = 0;
				}
			}
			else {
				for (unsigned i = 0; i < newSize; i++) {
					newArray[i] = myArray[i];
				}
			}
			mySize = newSize;
			delete [] myArray;
			myArray = newArray;
		}
	}
}

bool Vec::operator==(const Vec& v2) const {
   if (mySize == v2.getSize()) {
	   for (unsigned i = 0; i < mySize; i++) {
		   if (myArray[i] != v2.myArray[i]) {
			   return false;
		   }
	   }
	  return true;
   }
   return false;
}

void Vec::writeTo(ostream& out) const {
	for (unsigned i = 0; i < mySize; i++) {
		out << myArray[i] << endl;
	}
}

void Vec::readFrom(istream& in) {
	unsigned i = 0;
	while (in) {
		in >> myArray[i];
		i++;
	}
}

/* Returns the value at the given index
 * @param: const unsigned i
 * returns: item at index value i
 */
const Item& Vec::operator[](unsigned i) const {
	if (i < mySize) {
		return myArray[i];
	}
	else {
		throw range_error("Invalid index given to index operator");
	}
}

Item& Vec::operator[](unsigned i) {
	if (i < mySize) {
		return myArray[i];
	}
	else {
		throw range_error("Invalid index given to the index operator");
	}
}

/* Tests for equality between two vectors
 * @param: const Vec v2
 * precondition: two defined vec objects
 * returns: false if vec objects are identical in size and values; true otherwise
 */
bool Vec::operator!=(const Vec& v2) {
	if (mySize == v2.getSize()) {
		if (mySize == 0) {
			return false;
		}
		for (unsigned i = 0; i < mySize; i++) {
			if (myArray[i] != v2.myArray[i]) {
				return true;
			}
		}
		return false;
	}
	return true;
}

/* Reads vector data from a file
 * @param: const string fileName
 * precondition: vector (will be overwritten) and file with data values
 * postcondition: vector has size and values according to file
 */
void Vec::readFrom(const string& fileName) {
	delete [] myArray;
	ifstream in;
	in.open(fileName.c_str());
	assert(in.is_open());
	unsigned num;
	in >> num;
	mySize = num;
	Item* newArray = new Item[mySize];
	for (unsigned i = 0; i < mySize; i++) {
		in >> newArray[i];
	}
	in.close();
	myArray = newArray;
}

/* Writes a vector to a file with the first value as the Size
 * @param: const string fileName
 * precondition: nonempty vector
 * postcondition: vector's contents written to file
*/
void Vec::writeTo(const string& fileName) {
	ofstream fout;
	fout.open(fileName.c_str());
	assert(fout.is_open());
	fout << mySize << endl;
	for (unsigned i = 0; i < mySize; i++) {
		fout << myArray[i] << endl;
	}
	fout.close();
}

// overload the "+" operator to support vectors
Vec Vec::operator+(const Vec& v2) const {
	if (v2.mySize == mySize) {
		Vec newVec(mySize);
		for (unsigned i = 0; i < mySize; i++) {
			newVec.myArray[i] = (myArray[i] + v2.myArray[i]);
		}
		return newVec;
	}
	throw invalid_argument("Vectors are not the same size");
}

// overload the "-" operator to support vectors
Vec Vec::operator-(const Vec& v2) const {
	if (v2.mySize == mySize) {
		Vec newVec(mySize);
		for (unsigned i = 0; i < mySize; i++) {
			newVec.myArray[i] = (myArray[i] - v2.myArray[i]);
		}
		return newVec;
	}
	throw invalid_argument("Vectors are not the same size");
}

// overload the "*" operator to support vectors
double Vec::operator*(const Vec& v2) const {
	if (v2.mySize == mySize) {
		double product = 0;
		for (unsigned i = 0; i < mySize; i++) {
			product += (myArray[i] * v2.myArray[i]);
		}
		return product;
	}
	throw invalid_argument("Vectors are not the same size");
}
