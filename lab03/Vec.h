/* Vec.h provides a simple vector class named Vec.
 * Student Name: Duncan Van Keulen
 * Date: 19 February 2019
 * Begun by: Joel C. Adams, for CS 112 at Calvin College.
 */

#ifndef VEC_H_
#define VEC_H_

#include <iostream>
using namespace std;

typedef double Item;

class Vec {
public:
	// constructors
	Vec();
	Vec(unsigned size);
	Vec(const Vec& original);

	// = operator overloading
	Vec& operator=(const Vec& original);
	bool operator==(const Vec& v2) const;

	// accessors
	unsigned getSize() const { return mySize; }
	Item getItem(unsigned index) const;

	// mutators
	void setItem(unsigned index, const Item& it);
	void setSize(unsigned newSize);

	// I/O
	void writeTo(ostream& out) const;
	void readFrom(istream& in) const;

	// destructor
	virtual ~Vec();
	
private:
	unsigned mySize;
	Item * myArray;
	friend class VecTester;

};

#endif /*VEC_H_*/
