/* Vec.cpp defines the methods for Vec, a simple vector class.
 * Student Name: Duncan Van Keulen
 * Date: 19 February 2019
 * Begun by: Joel C. Adams, for CS 112 at Calvin College.
 */
 
#include "Vec.h"
#include <stdexcept>

// Default constructor
Vec::Vec() {
	mySize = 0;
	myArray = NULL;
}

// Explicit constructor
Vec::Vec(unsigned size) {
	mySize = size;
	if (size > 0) {
		myArray = new Item[size]();
	}
	else {
		myArray = NULL;
	}
}

// Copy constructor
Vec::Vec(const Vec& original) {
	mySize = original.mySize;
	if (original.mySize > 0) {
		myArray = new Item[original.mySize];
		for (unsigned i = 0; i < original.mySize; i++) {
			myArray[i] = original.myArray[i];
		}
	} else { myArray = NULL; }
}

// "=" operator overloading
Vec& Vec::operator=(const Vec& original) {
	if (this == &original) {
		return *this;
	}
	else {
		if (original.mySize == 0) {
			myArray = NULL;
		}
		if (mySize != original.mySize) {
			mySize = original.mySize;
		}
		if (mySize > 0) {
			delete [] myArray;
			myArray = NULL;
		}
		if (original.mySize > 0) {
			myArray = new Item[original.mySize];
		}
	}
	for (unsigned i = 0; i < mySize; i++) {
		myArray[i] = original.myArray[i];
	}
   return *this;
}

/* Set an item of the vector to a new item
 * @param unsigned index: the index in the vector to change
 * @param const Item& it: the item to change the index to
 *
 * precondition: the vector is constructed and has values
 * postcondition: the value of the index will be changed
 */
void Vec::setItem(unsigned index, const Item& it) {
	if (mySize == 0) { throw range_error("Vector is empty!"); }
	if (mySize < index + 1){
		throw range_error("Index beyond range of vector");
	}
	else {
		myArray[index] = it;
	}
}

/* Get the item in the vector
 * @param unsigned index: the index of the item to be returned
 *
 * precondition: vector is defined and not empty
 * postcondition: None (const)
 * returns: the item at the specified index
 */
Item Vec::getItem(unsigned index) const {
	if (mySize != 0) {
		if (index > mySize - 1) {
			throw range_error("Index greater than size of vector");
		}
		else {
			return myArray[index];
		}
	}
	throw range_error("Vector's size is 0");
}

/* Dynamically set the size of the vector
 * @param unsigned newSize: the desired size of the vector
 *
 * precondition: vector is defined and not empty
 * postcondition: the vector's size will be changed, aka
 * 				  extended with Item's default value or
 * 				  truncated to the new size
 */
void Vec::setSize(unsigned newSize) {
	if (newSize != mySize) {
		if (newSize == 0) {
			delete [] myArray;
			myArray = NULL;
			mySize = 0;
		} else {
			Item * newArray = new double[newSize]();
			if (mySize < newSize) {
				for (unsigned i = 0; i < mySize; i++) {
					newArray[i] = myArray[i];
				}
			} else {
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

// "==" operator overloading
bool Vec::operator==(const Vec& v2) const {
	if (v2.mySize == mySize) {
		for (unsigned i = 0; i < mySize; i++) {
			if (v2.myArray[i] != myArray[i]) {
				return false;
			}
		}
		return true;
	}
	return false;
}

/* Write to ostream object
 * @param ostream& out: the ostream object to send the values
 * 						of the vector to
 * precondition: vector is defined and not empty
 * postcondition: vector's values will be written to the ostream
 */
void Vec::writeTo(ostream& out) const {
	if (mySize > 0) {
		for (unsigned i = 0; i < mySize; i++) {
			out << myArray[i] << '\t' << flush;
		}
	}
}

/* Read from an istream object
 * @param istream& in: the istream object to be written to
 *
 * precondition: vector is defined
 * postcondition: the values of the vector will be filled
 * 				  with those from the ostream
 */
void Vec::readFrom(istream& in) const {
	for (unsigned i = 0; i < mySize; i++) {
		in >> myArray[i];
	}
}

// Destructor
Vec::~Vec() {
	myArray = NULL;
	mySize = 0;
	delete [] myArray;
}
