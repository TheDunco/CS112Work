/* ListTester.h declares the test-class for class List.
 * Joel Adams, for CS 112 at Calvin College.
 *
 * Student: Duncan Van Keulen (djv78)
 * Date: 17 March 2019 (Updated for CongaLine)
 */

#ifndef LISTTESTER_H_
#define LISTTESTER_H_

class ListTester {
public:
	void runTests();
	void testDefaultConstructor();
	void testNodeDefaultConstructor();
	void testNodeExplicitConstructor();
	void testAppend();
	void testDestructor();
	void testCopyConstructor();
	void testAssignment();
	void testEquality();
	void testReadFrom();
	void testWriteToString();
	void testPrepend();
	void testInsert();
	void testInequality();
	void testReadFromFile();
	void testWriteToStream();
	void testGetIndex();
	void testRemove();
	void testInsertAfter();
	void testInsertBefore();
	void testInsertionOperator();
};

#endif /*LISTTESTER_H_*/
