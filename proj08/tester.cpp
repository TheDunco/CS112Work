/* tester.cpp drives the testing of the Queue classes.
 * Joel Adams, for CS 112 at Calvin College.
 */

#include "ArrayQueueTester.h"
#include "PalindromeDetectorTester.h"
 
 int main() {
 	ArrayQueueTester aqt;
 	aqt.runTests();
 	PalindromeDetectorTester pdt;
 	pdt.runTests();
 }
