/* ArrayQueueTester.h declares the class that tests class ArrayQueue.
 * Joel Adams, for CS 112 at Calvin College.
 */
 
#ifndef QUEUETESTER_H_
#define QUEUETESTER_H_

#include "ArrayQueue.h"
#include <cassert>
#include <cstdlib>
using namespace std;

class ArrayQueueTester {
public:
	void runTests();
	void testConstructor();
	void testAppend();
	void testRemove();
	void testCopyConstructor();
	void testAssignment();
	void testSetCapacity();
};

#endif /*QUEUETESTER_H_*/
