#ifndef LINKEDQUEUETESTER_H_
#define LINKEDQUEUETESTER_H_

#include "LinkedQueue.h"
#include <cassert>
using namespace std;

class LinkedQueueTester {
public:
	void runTests();
	void testConstructor();
	void testAppend();
	void testRemove();
	void testCopyConstructor();
	void testAssignment();
};

#endif /*LINKEDQUEUETESTER_H_*/
