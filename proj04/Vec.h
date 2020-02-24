/* Vec.h provides a simple vector class named Vec.
 * Date: 2-19-19
 * Begun by: Joel C. Adams, for CS 112 at Calvin College.
 * @author: Josh Ridder (jmr59)
 * @author: Duncan Van Keulen (djv78)
 *  * Josh Ridder:
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

#ifndef VEC_H_
#define VEC_H_

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
#include <cassert>
using namespace std;

template<class Item>

class Vec {
public:
	Vec();
	virtual ~Vec();
	Vec(unsigned size);
	Vec(const Vec& original);
	Vec& operator=(const Vec& original);
	unsigned getSize() const {return mySize;}
	void setItem(unsigned index, const Item& it);
	Item getItem(unsigned index) const;
	void setSize(unsigned newSize);
	bool operator==(const Vec& v2) const;
	void writeTo(ostream& out) const;
	void readFrom(istream& in);
	Vec operator=(const unsigned& num);
	
	const Item& operator[](unsigned i) const;
	Item& operator[](unsigned i);
	bool operator!=(const Vec& v2);
	void readFrom(const string& fileName);
	void writeTo(const string& fileName);
	Vec operator+(const Vec& v2) const;
	Vec operator-(const Vec& v2) const;
	double operator*(const Vec& v2) const;

private:
	unsigned mySize;
	Item* myArray;
	friend class VecTester;
};


// From Vec.cpp, Vec method definitions...

template<class Item>
Vec<Item>::Vec() {
	mySize = 0;
	myArray = NULL;
}

template<class Item>
Vec<Item>::~Vec() {
	delete [] myArray;  // return the array's memory to the system
	myArray = NULL;
	mySize = 0;
}

template<class Item>
Vec<Item>::Vec(unsigned size) {
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

template<class Item>
Vec<Item>::Vec(const Vec<Item>& original) {
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

template<class Item>
Vec<Item>& Vec<Item>::operator=(const Vec<Item>& original) {
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

template<class Item>
void Vec<Item>::setItem(unsigned index, const Item& it) {
	if (index < mySize){
		myArray[index] = it;
	}
	else {
		throw range_error("Invalid index given to setItem method");
	}
}

template<class Item>
Item Vec<Item>::getItem(unsigned index) const {
	if (index < mySize) {
		return myArray[index];
	}
	else {
		throw range_error("Invalid index given to getItem method");
	}
}

template<class Item>
void Vec<Item>::setSize(unsigned newSize) {
	if (mySize != newSize) {
		if (newSize == 0) {
			delete [] myArray;
			myArray = NULL;
			mySize = 0;
		}
		else {
			Item* newArray = new Item[newSize]();
			if (mySize < newSize) {
				for (unsigned i = 0; i < mySize; i++) {
					newArray[i] = myArray[i];
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

template<class Item>
bool Vec<Item>::operator==(const Vec& v2) const {
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

template<class Item>
void Vec<Item>::writeTo(ostream& out) const {
	for (unsigned i = 0; i < mySize; i++) {
		out << myArray[i] << endl;
	}
}

template<class Item>
void Vec<Item>::readFrom(istream& in) {
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
template<class Item>
const Item& Vec<Item>::operator[](unsigned i) const {
	if (i < mySize) {
		return myArray[i];
	}
	else {
		throw range_error("Invalid index given to index operator");
	}
}

template<class Item>
Item& Vec<Item>::operator[](unsigned i) {
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
template<class Item>
bool Vec<Item>::operator!=(const Vec& v2) {
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
template<class Item>
void Vec<Item>::readFrom(const string& fileName) {
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
template<class Item>
void Vec<Item>::writeTo(const string& fileName) {
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
template<class Item>
Vec<Item> Vec<Item>::operator+(const Vec<Item>& v2) const {
	if (v2.mySize == mySize) {
		Vec<Item> newVec(mySize);
		for (unsigned i = 0; i < mySize; i++) {
			newVec.myArray[i] = (myArray[i] + v2.myArray[i]);
		}
		return newVec;
	}
	throw invalid_argument("Vectors are not the same size");
}

// overload the "-" operator to support vectors
template<class Item>
Vec<Item> Vec<Item>::operator-(const Vec<Item>& v2) const {
	if (v2.mySize == mySize) {
		Vec<Item> newVec(mySize);
		for (unsigned i = 0; i < mySize; i++) {
			newVec.myArray[i] = (myArray[i] - v2.myArray[i]);
		}
		return newVec;
	}
	throw invalid_argument("Vectors are not the same size");
}

// overload the "*" operator to support vectors
template<class Item>
double Vec<Item>::operator*(const Vec<Item>& v2) const {
	if (v2.mySize == mySize) {
		double product = 0;
		for (unsigned i = 0; i < mySize; i++) {
			product += (myArray[i] * v2.myArray[i]);
		}
		return product;
	}
	throw invalid_argument("Vectors are not the same size");
}

#endif /*VEC_H_*/
