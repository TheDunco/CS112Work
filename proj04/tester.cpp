/* tester.cpp drives the testing of our Vec template and Matrix class.
 * Student: Duncan Van Keulen
 * Date: 26 February 2019
 * Begun by: Joel C. Adams, for CS 112 at Calvin College.
 */

#include "VecTester.h"
#include "MatrixTester.h"
#include "Application.h"

int main() {
//	VecTester vt;
//	vt.runTests();
	MatrixTester mt;
	mt.runTests();
	Application app;
	app.Menu();
}
