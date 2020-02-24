/* array.h declares "C style" array operations.
 * Name: Duncan Van Keulen
 * Date: 17 February 2019
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 */

#include <iostream>
#include <cassert>
#include <string>
using namespace std;

void initialize(double *a, unsigned size);

void print(double *a, unsigned size);

double average(double *a, unsigned size);

// project functions
double sum(double *a, unsigned size);
void read(istream& in, double *a, unsigned size);
void fill(const string& fileName, double *&a, int &numValues);
void resize(double *&a, unsigned oldSize, unsigned newSize);
void concat(double *a1, int size1, double *a2, int size2, double *&a3, int &size3);
