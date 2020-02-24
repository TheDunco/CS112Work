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
using namespace std;

typedef double Item;

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

#endif /*VEC_H_*/
