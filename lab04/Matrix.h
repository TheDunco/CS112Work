/* Matrix.h provides a class for manipulating 2-dimensional vectors.
 * Student Name: Duncan Van Keulen
 * Date: 26 February 2019
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 */

#ifndef MATRIX
#define MATRIX

#include "Vec.h"

typedef double Item;

class Matrix {
public:
	Matrix();
	Matrix(unsigned rows, unsigned columns);
	unsigned getRows() const { return myRows; }
	unsigned getColumns() const { return myColumns; }
	const Vec<Item>& operator[](unsigned index) const;
	Vec<Item>& operator[](unsigned index);
	bool operator==(const Matrix& m2) const;

private:
	unsigned 		 myRows;
	unsigned 		 myColumns;
	Vec< Vec<Item> > myVec;

	friend class MatrixTester;
};

#endif
