/* Matrix.h provides a class for manipulating 2-dimensional vectors.
 * Student Name: Duncan Van Keulen
 * Date: 26 February 2019
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 */

#ifndef MATRIX
#define MATRIX

#include "Vec.h"

template<class Item>
class Matrix {
public:
	Matrix();
	Matrix(unsigned rows, unsigned columns);
	unsigned getRows() const { return myRows; }
	unsigned getColumns() const { return myColumns; }
	const Vec<Item>& operator[](unsigned index) const;
	Vec<Item>& operator[](unsigned index);
	bool operator==(const Matrix& m2) const;
	void readFrom(const string& filename);
	void writeTo(ostream& out, const string& separator = "\t");
	Matrix<Item> operator-(const Matrix<Item>& rhs);
	Matrix<Item> getTranspose();
	bool operator!=(const Matrix<Item>& m2) const;
	void readFrom(istream& in);
	Matrix<Item> operator+(const Matrix<Item>& m2);
	void writeTo(const string& filename, const string& separator = "\t");



private:
	unsigned 		 myRows;
	unsigned 		 myColumns;
	Vec< Vec<Item> > myVec;

	friend class MatrixTester;
};

// Default constructor
template<class Item>
Matrix<Item>::Matrix() {
	myRows = myColumns = 0;
}

// Explicit constructor
template<class Item>
Matrix<Item>::Matrix(unsigned rows, unsigned columns) {
	myRows = rows;
	myColumns = columns;
	myVec.setSize(rows);
	for (unsigned i = 0; i < rows; i++) {
		myVec[i].setSize(columns);
	}
}

// Read subscript operator overloading
template<class Item>
Vec<Item>& Matrix<Item>::operator[](unsigned index) {
	if (index > myVec.getSize()) {
		throw range_error("Matrix[] read: Index out of range");
	}
	else {
		return myVec[index];
	}
}

// Write subscript operator overloading
template<class Item>
const Vec<Item>& Matrix<Item>::operator[](unsigned index) const {
	if (index > myVec.getSize()) {
		throw range_error("Matrix[] write: Index out of range");
	}
	else {
		return myVec[index];
	}
}

// Overload the equality operator
template<class Item>
bool Matrix<Item>::operator==(const Matrix<Item>& m2) const {
	if ( myRows != m2.getRows() || myColumns != m2.getColumns() ) {
		return false;
	} else {
		return myVec == m2.myVec;
	}
}

/*
 * Read from a file
 * @param string filename: the name of the file. File's first line should be
 * 											  values of the rows and columns
 * precondition: File exists and the first line should be values of the rows and columns
 * @author: Duncan Van Keulen
 */
template<class Item>
void Matrix<Item>::readFrom(const string& filename) {
	ifstream fin;

	fin.open(filename.c_str());
	assert( fin.is_open() );

	fin >> myRows;
	fin >> myColumns;

	myVec.setSize(myRows);
	for (unsigned i = 0; i < myRows; i++) {
		myVec[i].setSize(myColumns);
	}

	for (unsigned i = 0; i < myRows; i++) {
		for (unsigned j = 0; j < myColumns; j++) {
			fin >> myVec[i][j];
		}
	}

	fin.close();
}

/*
 * Write to a stream
 * @param ostream& out: The out stream to be written to
 * @param const string& separator: Defaults to "\t", separator between columns
 * precondition: Stream needs to exist
 * @author: Duncan Van Keulen
 */
template<class Item>
void Matrix<Item>::writeTo(ostream& out, const string& separator) {
	for (unsigned i = 0; i < myRows; i++) {
		for (unsigned j = 0; j < myColumns; j++) {
			out << myVec[i][j] << separator;
		}
		out << '\n';
	}
}

/*Overload the subtraction operator
 * Returns: Matrix of subtracted values
 * @author: Duncan Van Keulen
 */
template<class Item>
Matrix<Item> Matrix<Item>::operator-(const Matrix<Item>& rhs) {
	if (myRows == rhs.myRows && myColumns == rhs.myColumns) {
		Matrix mat(myRows, myColumns);
		for (unsigned i = 0; i < myRows; i++) {
			for (unsigned j = 0; j < myColumns; j++) {
				mat[i][j] = myVec[i][j] - rhs.myVec[i][j];
			}
		}
	return mat;
	}
	throw invalid_argument("Matrix::operator-: Number of rows or columns does not match");
}

/*
 * Transposes the matrix; switches columns and rows
 * postcondition: Rows and columns
 * Returns: Matrix of transposed values
 */
template<class Item>
Matrix<Item> Matrix<Item>::getTranspose() {
	Matrix<Item> mat(myColumns, myRows);
	for (unsigned i = 0; i < myRows; i++) {
		for (unsigned j = 0; j < myColumns; j++) {
			mat[j][i] = myVec[i][j];
		}
	}
	return mat;
}

/*Boolean Inequality Operator
 * Checks to see if the rows and columns are the same,
 * and then uses the Vec boolean operator to compare the vecs.
 * If the vecs are not equal, it returns true immediately.
 * Written by: Ben Brouwer
 */
template<class Item>
bool Matrix<Item>::operator!=(const Matrix& m2) const {
	if ( myRows == m2.getRows() and myColumns == m2.getColumns() ) {
		for (unsigned i = 0; i < myRows; i++) {
			for (unsigned j = 0; j < myColumns; j++) {
				if (myVec[i][j] == m2.myVec[i][j]) {
				}
				else{
					return true;
				}
			}
		}
		return false;
	}
	else {
		return true;
	}
}

/*Read From Method
 * Recieves an istream and returns each line of it into places in the matrix
 * Written by: Ben Brouwer
 */
template<class Item>
void Matrix<Item>::readFrom(istream& in) {
	for (unsigned i = 0; i < myRows; i++) {
		for (unsigned j = 0; j < myColumns; j++) {
			in >> myVec[i][j];
		}
	}
}

/*Addition Operator
 * Checks to see if the matrices entered are the same.  If so, throw an invalid argument error.
 * Checks to see if they are null matrices.  If so, just return a null matrix.
 * Otherwise, fill a new matrix m3 with the sums of the corresponding values in the original matrices.
 * Written by: Ben Brouwer
 */
template<class Item>
Matrix<Item> Matrix<Item>::operator+(const Matrix<Item>& m2) {
	if ( myRows != m2.getRows() or myColumns != m2.getColumns() ) {
		throw invalid_argument("Matrices are not of the same dimensions");
	}
	Matrix<Item> m3(myRows, myColumns);
	if ( myRows == 0 or myColumns == 0 ) {
		return m3;
	}
	else {
		for (unsigned i = 0; i < myRows; i++) {
			for (unsigned j = 0; j < myColumns; j++) {
				m3[i][j] = myVec[i][j] + m2[i][j];
			}
		}
		return m3;
	}
}

/*
 * Write to a stream
 * @param string& filename: Name of the file to be written to
 * @param const string& separator: Defaults to "\t", separator between columns
 * @author: Ben Brower with Duncan Van Keulen
 */
template<class Item>
void Matrix<Item>::writeTo(const string& filename, const string& separator) {
	ofstream fin(filename.c_str());
	fin << myRows << separator << myColumns << endl;
	for (unsigned i = 0; i < myRows; i++) {
		for (unsigned j = 0; j < myColumns; j++) {
			fin << myVec[i][j] << separator;
		}
		 fin << '\n';
	}
}

#endif
