/* Matrix.cpp defines Matrix class methods.
 * Student Name: Duncan Van Keulen
 * Date: 26 February 2019
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 */

#include "Matrix.h"

Matrix::Matrix() {
	myRows = myColumns = 0;
}

Matrix::Matrix(unsigned rows, unsigned columns) {
	myRows = rows;
	myColumns = columns;
	myVec.setSize(rows);
	for (unsigned i = 0; i < rows; i++) {
		myVec[i].setSize(columns);
	}
}

// Read subscript operator overloading
Vec<Item>& Matrix::operator[](unsigned index) {
	if (index > myVec.getSize()) {
		throw range_error("Matrix[] read: Index out of range");
	}
	else {
		return myVec[index];
	}
}

// Write subscript operator overloading
const Vec<Item>& Matrix::operator[](unsigned index) const {
	if (index > myVec.getSize()) {
		throw range_error("Matrix[] write: Index out of range");
	}
	else {
		return myVec[index];
	}
}

// Overload the equality operator
bool Matrix::operator==(const Matrix& m2) const {
	if ( myRows != m2.getRows() || myColumns != m2.getColumns() ) {
		return false;
	} else {
		return myVec == m2.myVec;
	}
}
