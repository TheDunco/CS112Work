/* ListTester.cpp defines the test methods for class List.
 * Joel Adams, for CS 112 at Calvin College.
 *
 * Student: Duncan Van Keulen (djv78)
 * Date: 17 March 2019 (Updated for CongaLine)
 */


#include "ListTester.h" // ListTester
#include "List.h"       // List
#include "CongaLine.h"	// CongaLine
#include <iostream>     // cin, cout
#include <fstream> 	// fin
#include <cassert>      // assert()
#include <cstdlib>      // exit()
#include <stdexcept>    // underflow_error
using namespace std;

void ListTester::runTests() {
	cout << "Running List tests..." << endl;
	testDefaultConstructor();
	testNodeDefaultConstructor();
	testNodeExplicitConstructor();
	testAppend();
	testDestructor();
	testCopyConstructor();
	testAssignment();
	testEquality();
	testReadFrom();
	testWriteToString();
	testPrepend();
	testInsert();
	testInequality();
	testWriteToStream();
	testReadFromFile();
	testGetIndex();
	testRemove();

	cout << endl << "Testing Conga Line operations..." << endl;
	testInsertAfter();
	testInsertBefore();
	testInsertionOperator();

	cout << "All tests passed!" << endl << endl;
}

void ListTester::testDefaultConstructor() {
	cout << "Testing List default constructor... " << flush;
	List<double> aList;
	assert( aList.mySize == 0 );
	assert( aList.myFirst == NULL );
	assert( aList.myLast == NULL );
	cout << "Passed!" << endl;
}

void ListTester::testNodeDefaultConstructor() {
	cout << "Testing Node default constructor... " << flush;
	List<double>::Node aNode;
	assert( aNode.myItem == double() );
	assert( aNode.myNext == NULL );
	cout << "Passed!" << endl;
}

void ListTester::testNodeExplicitConstructor() {
	cout << "Testing Node explicit constructor... " << flush;
	List<double>::Node n1(11, NULL);
	assert( n1.myItem == 11 );
	assert( n1.myNext == NULL );
	cout << " 1 " << flush;

	List<double>::Node *n3 = new List<double>::Node(33, NULL);
	List<double>::Node n2(22, n3);
	assert( n2.myItem == 22 );
	assert( n2.myNext == n3 );
	cout << " 2 " << flush;
	cout << "Passed!" << endl;
}

void ListTester::testAppend() {
	cout << "Testing append()... " << flush;
	// empty List
	List<double> aList;
	assert( aList.getSize() == 0 );
	assert( aList.myFirst == NULL );
	assert( aList.myLast == NULL );
	try {
		aList.getFirst();
		cerr << "getFirst() worked on empty list" << endl;
		exit(1);
	} catch (underflow_error&) {
		cout << " 0a " << flush;
	}
	try {
		aList.getLast();
		cerr << "getLast() worked on empty list" << endl;
		exit(1);
	} catch (underflow_error&) {
		cout << " 0b " << flush;
	}
	// append to empty list
	aList.append(11);
	assert( aList.getSize() == 1 );
	assert( aList.myFirst != NULL );
	assert( aList.myLast == aList.myFirst );
	assert( aList.getFirst() == 11 );
	assert( aList.getLast() == 11 );
	assert( aList.myFirst->myNext == NULL );
	cout << " 1 " << flush;
	// append to a list containing 1 Item
	aList.append(22);
	assert( aList.getSize() == 2 );
	assert( aList.myFirst != NULL );
	assert( aList.myLast != NULL );
	assert( aList.myFirst != aList.myLast );
	assert( aList.getFirst() == 11 );
	assert( aList.getLast() == 22 );
	assert( aList.myFirst->myNext != NULL );
	assert( aList.myLast->myNext == NULL );
	cout << " 2 " << flush;
	// append to a list containing 2 Items
	aList.append(33);
	assert( aList.getSize() == 3 );
	assert( aList.myFirst != NULL );
	assert( aList.myLast != NULL );
	assert( aList.getFirst() == 11 );
	assert( aList.getLast() == 33 );
	assert( aList.myFirst->myNext->myItem == 22 );
	assert( aList.myLast->myNext == NULL );
	cout << " 3 " << flush;
	cout << "Passed!" << endl;
}

void ListTester::testDestructor() {
	cout << "Testing destructor... " << flush;
	List<double> aList;
	aList.~List();
	assert( aList.getSize() == 0 );
	assert( aList.myFirst == NULL );
	assert( aList.myLast == NULL );
	cout << " 1 " << flush;

	aList.append(11);
	aList.append(22);
	aList.append(33);
	aList.~List();
	assert( aList.getSize() == 0 );
	assert( aList.myFirst == NULL );
	assert( aList.myLast == NULL );
	cout << " 2 " << flush;
	cout << "Passed!  But double-check for memory leaks!" << endl;
}

void ListTester::testCopyConstructor() {
	cout << "Testing copy constructor... " << flush;
	// copy empty list
	List<double> list1;
	List<double> list2(list1);
	assert( list2.getSize() == 0 );
	assert( list2.myFirst == NULL );
	assert( list2.myLast == NULL );
	cout << " 1 " << flush;

	// copy nonempty list
	List<double> list3;
	list3.append(11);
	list3.append(22);
	list3.append(33);
	List<double> list4(list3);
	assert( list4.getSize() == 3 );
	assert( list4.getFirst() == 11 );
	assert( list4.getLast() == 33 );
	assert( list4.myFirst->myNext->myItem == 22 );
	assert( list4.myFirst != list3.myFirst );
	assert( list4.myLast != list3.myLast );
	cout << " 2 " << flush;
	cout << "Passed!" << endl;
}

void ListTester::testAssignment() {
	cout << "Testing assignment... " << flush;
	// empty to empty assignment
	List<double> list1;
	List<double> list2;
	list2 = list1;
	assert( list2.getSize() == 0 );
	assert( list2.myFirst == NULL );
	assert( list2.myLast == NULL );
	cout << " 1 " << flush;

	// non-empty to empty assignment
	List<double> list3;
	list3.append(11);
	list3.append(22);
	list3.append(33);
	List<double> list4;
	list4 = list3;
	assert( list4.getSize() == 3 );
	assert( list4.getFirst() == 11 );
	assert( list4.getLast() == 33 );
	assert( list4.myFirst->myNext->myItem == 22 );
      // check that nodes are distinct
	assert( list4.myFirst != list3.myFirst );
	assert( list4.myFirst->myNext != list3.myFirst->myNext );
	assert( list4.myLast != list3.myLast );
	cout << " 2 " << flush;

	// equal-sized non-empty to non-empty assignment
	List<double> list5;
	list5.append(44);
	list5.append(55);
	list5.append(66);
	list5 = list3;
	assert( list5.getSize() == 3 );
	assert( list5.getFirst() == 11 );
	assert( list5.getLast() == 33 );
	assert( list5.myFirst->myNext->myItem == 22 );
      // check that nodes are distinct
	assert( list5.myFirst != list3.myFirst );
	assert( list5.myFirst->myNext != list3.myFirst->myNext );
	assert( list5.myLast != list3.myLast );
	cout << " 3 " << flush;

	// empty to non-empty assignment
	List<double> list6;
	list6.append(44);
	list6.append(55);
	list6.append(66);
	List<double> list7;
	list6 = list7;
	assert( list6.getSize() == 0 );
	assert( list6.myFirst == NULL );
	assert( list6.myLast == NULL );
	cout << " 4 " << flush;

	// unequal-sized non-empty to non-empty assignment
	List<double> list8;
	list8.append(44);
	list8.append(55);
	list8.append(66);
	list8.append(77);
	list8 = list3;
	assert( list8.getSize() == 3 );
	assert( list8.getFirst() == 11 );
	assert( list8.getLast() == 33 );
	assert( list8.myFirst->myNext->myItem == 22 );
      // check that nodes are distinct
	assert( list8.myFirst != list3.myFirst );
	assert( list8.myFirst->myNext != list3.myFirst->myNext );
	assert( list8.myLast != list3.myLast );
	cout << " 5 " << flush;

	// assignment chaining
	List<double> list9;
	list9.append(44);
	list9.append(55);
	list9.append(66);
	list9.append(77);
	List<double> list10;
	list10 = list9 = list8;
	assert( list10.getSize() == 3 );
	assert( list10.getFirst() == 11 );
	assert( list10.getLast() == 33 );
	assert( list10.myFirst->myNext->myItem == 22 );
	cout << " 6 " << flush;

	// self-assignment (stupid, but possible)
	List<double> list11;
	list11.append(11);
	list11.append(22);
	list11.append(33);
	list11 = list11;
	assert( list11.getSize() == 3 );
	assert( list11.getFirst() == 11 );
	assert( list11.getLast() == 33 );
	assert( list11.myFirst->myNext->myItem == 22 );
	cout << " 7 " << flush;

	cout << "Passed!  But double-check for memory leaks!" << endl;
}

void ListTester::testEquality() {
	cout << "Testing equality... " << flush;

	// Empty cases
	List<double> list12;
	List<double> list13;
	assert( list12 == list13 );
	assert( list12 == list12);
	assert( list13 == list13);
	cout << " 0 " << flush;

	// Empty to non-empty (should not work)
	list12.append(100);
	assert( !(list12 == list13 ) );
	cout << " 1 " << flush;

	// Non-emtpy to non-emtpy
	list13.append(100);
	assert( list12 == list13);
	list12.append(111);
	list13.append(111);
	assert( list12 == list13);
	cout << " 3 " << flush;

	// Same size (>1), different values
	list13.append(99); list13.append(1);
	list12.append(100); list12.append(2);
	assert( !(list12 == list13) );

	cout << " Passed!" << endl;
}

void ListTester::testReadFrom() {
	cout << "Testing readFrom(stream)... " << flush;

	List<double> list14;
	List<double> list15;
	ifstream fin("istreamTest.txt");
	assert( fin.is_open() );

	// test by reading from a file using an ifstream
	list14.readFrom(fin);	// should read 10, 11, 12 from file
	assert( !(list14 == list15) );	// make sure that changed something
	assert( list14.getSize() == 3 );
	// make sure all the items from the file are there and in the correct spot
	assert( list14.myFirst->myItem == 10 );
	assert( list14.myFirst->myNext->myItem == 11 );
	assert( list14.myLast->myItem == 12 );
	list15.append(10); list15.append(11); list15.append(12);
	assert( list14 == list15 );		// they should now be equal
	cout << " 0 " << flush;


	cout << " Passed!" << endl;
}

void ListTester::testWriteToString() {
	cout << "Testing writeTo(string)... " << flush;

	// create a list and append some values to it
	List<double> list16;
	list16.append(11); list16.append(22); list16.append(33);
	list16.writeTo("writeToTest.txt", "\t");

	// create a new list, reading from the file stream...
	List<double> list17;
	ifstream fin("writeToTest.txt");
	assert( fin.is_open() );
	list17.readFrom(fin);
	fin.close();

	// ...and make sure the lists are equal to each other.
	assert( list17 == list16 );
	cout << " 0 " << flush;


	cout << " Passed!" << endl;
}

void ListTester::testPrepend() {
	cout << "Testing prepend()... " << flush;

	List<double> list17;
	List<double> list18;

	// Empty list
	list17.prepend(1);
	assert( list17.getSize() == 1 );
	assert( !(list17 == list18) );
	assert( list17.myFirst->myItem == 1 );
	assert( list17.myFirst == list17.myLast );
	assert( list17.myLast->myNext == NULL );
	cout << " 0 " << flush;

	// First one is same as append
	list18.append(1);
	assert( list17 == list18 );
	cout << " 1 " << flush;

	// Multiple items already there
	list17.append(2); list17.append(3);
	List<double> list19;
	list19.append(0); list19.append(1);
	list19.append(2); list19.append(3);
	assert( !(list17 == list19) );
	list17.prepend(0);
	assert( list17.getSize() == 4);
	assert( list17 == list19 );
	cout << " 2 " << flush;

	cout << " Passed!" << endl;
}

void ListTester::testInsert() {
	cout << "Testing insert()... " << flush;
	List<double> list18;
	list18.append(12); list18.append(34); list18.append(78);
	list18.insert(56, 2);

	// empty list
	List<double> list19;
	list19.insert(12, 0);
	assert( list19.mySize == 1 );
	assert( list19.myFirst->myItem == 12 );
	cout << " 0 " << flush;

	// multiple items, inserting in middle
	assert( list18.mySize == 4 );
	assert( list18.myFirst->myItem == 12 );
	assert( list18.myFirst->myNext->myItem == 34 );
	assert( list18.myFirst->myNext->myNext->myItem == 56 );
	assert( list18.myFirst->myNext->myNext->myNext->myItem == 78 );
	cout << " 1 " << flush;

	// mutliple items, insterting at the end
	list18.insert(910, 4);
	assert( list18.mySize == 5 );
	assert( list18.myLast->myItem == 910 );
	cout << " 2 " << flush;

	// multiple items, inserting past the end
	list18.insert(1112, 9);
	assert( list18.mySize == 6 );
	assert( list18.myLast->myItem == 1112 );
	cout << " 3 " << flush;

	// multiple items, inserting at beginning
	list18.insert(1, 0);
	assert( list18.mySize == 7 );
	assert( list18.myFirst->myItem == 1 );
	cout << " 4 " << flush;

	cout << " Passed!" << endl;
}

void ListTester::testInequality(){
	List<double> l1;
	l1.append(11);
	l1.append(22);
	l1.append(33);
	List<double> l2;
	l2.append(11);
	l2.append(22);
	l2.append(33);
	List<double> l3;
	List<double> l4;
	l4.append(11);
	l4.append(22);
	l4.append(23);
	List<double> l5;
	l5.append(11);
	l5.append(25);
	l5.append(33);

	cout << "Testing Inequality... " << flush;

	assert ( (l1 != l2) == false);
	cout << " 0 " << flush;

	assert ( l1 != l3 );
	assert ( l2 != l3 );
	cout << " 1 " << flush;

	assert ( l1 != l4 );
	cout << " 2 " << flush;

	assert( l2 != l5 );
	cout << " 3 " << flush;

	cout << "Passed!" << endl;

}

void ListTester::testWriteToStream(){
	cout << "Testing WriteToStream... " << flush;
	List<double> l1;
	l1.append(11);
	l1.append(33);
	l1.append(55);
	ofstream fout("WriteToTest.txt");
	assert(fout.is_open());
	l1.writeTo(fout, "\n");
	fout.close();

	List<double> l2;
	l2.readFrom("WriteToTest.txt");
	assert(l2.mySize == 3);
	assert(l2.myFirst->myItem == 11);
	assert(l2.myLast->myItem == 55);
	cout << " 0 " << flush;


	cout << " Passed!"<< endl;


}

void ListTester::testReadFromFile(){
	cout << "Testing readFrom(file)... ";
	List<double> l1;
	l1.readFrom("ReadFromTest.txt");
	assert(l1.myFirst->myItem == 19);
	assert(l1.myLast->myItem == 23);
	assert(l1.mySize == 5);
	cout << " 0 " << flush;

	List<double> l2;
	l2.readFrom("ReadFromTest2.txt");
	assert( l2.mySize == 0);

	cout << "Passed!" << endl;
}

void ListTester::testGetIndex(){
	cout << "Testing getIndexOf... " << flush;
	List<double> l1;
	l1.readFrom("ReadFromTest.txt");
	assert( l1.getIndexOf(19) == 0 );
	assert( l1.getIndexOf(20) == 1 );
	cout << " 0 " << flush;

	assert(l1.getIndexOf(23) == 4);
	assert(l1.getIndexOf(21) == 2);
	cout << " 1 " << flush;

	try {
		l1.getIndexOf(99);
		cerr << "Index passed with an Item that is not in the list";
		exit(1);
	} catch(invalid_argument&) {
		cout << " 2 " << flush;
	}

	cout << " Passed! " << endl;
}

void ListTester::testRemove() {
	cout << "Testing Remove... " << flush;
	List<double> l1;
	l1.readFrom("ReadFromTest.txt");
	l1.remove(2);
	assert(l1.mySize == 4);
	cout << " 0 " << flush;
	assert(l1.getIndexOf(22) == 2);
	cout << " 1 " << flush;

	l1.remove(0);
	assert(l1.mySize == 3);
	cout << " 2 " << flush;
	assert(l1.getIndexOf(20) == 0);
	cout << " 3 " << flush;

	cout << " Passed!" << endl;
}

void ListTester::testInsertAfter() {
	cout << "Testing insertAfter... " << flush;
	CongaLine groove("Ann", "Charlie");

	// make sure the constructor worked properly...
	assert( groove.myLine.mySize == 2 );
	assert( groove.myFirstPerson == "Ann" );
	assert( groove.myLine.myFirst->myItem == "Ann" );
	assert( groove.mySecondPerson == "Charlie" );
	assert( groove.myLine.myLast->myItem == "Charlie" );
	cout << " 0 " << flush;

	// normal case inserting after the first person
	groove.myLine.insertAfter("Ann", "Bob");
	assert( groove.myLine.mySize == 3 );
	assert( groove.myLine.myFirst->myItem == "Ann" );
	assert( groove.myLine.myFirst->myNext->myItem == "Bob" );
	assert( groove.myLine.myLast->myItem == "Charlie" );
	cout << " 1 " << flush;

	// try inserting after a non-existent member
	if (!groove.myLine.insertBefore("Ian", "Henry")) {
		cout << " 2a " << flush;
	} else {
		cerr << "Insert after worked on a non-existent member" << flush;
	}
	// this all should still be true:
	// invalid insertAfter shouldn't have changed anything
	assert( groove.myLine.mySize == 3 );
	assert( groove.myLine.myFirst->myItem == "Ann" );
	assert( groove.myLine.myFirst->myNext->myItem == "Bob" );
	assert( groove.myLine.myLast->myItem == "Charlie" );
	cout << " 2b " << flush;

	// test inserting after the last member
	groove.myLine.insertAfter("Charlie", "DJ");
	assert( groove.myLine.mySize == 4 );
	assert( groove.myLine.myFirst->myItem == "Ann" );
	assert( groove.myLine.myFirst->myNext->myItem == "Bob" );
	assert( groove.myLine.myFirst->myNext->myNext->myItem == "Charlie" );
	assert( groove.myLine.myLast->myItem == "DJ" );
	cout << " 3 " << flush;


	cout << " Passed!" << endl;
}

void ListTester::testInsertBefore() {
	cout << "Testing insertBefore... " << flush;
	CongaLine groovy("Bob", "DJ");

	// make sure the constructor worked properly...
	assert( groovy.myLine.mySize == 2 );
	assert( groovy.myFirstPerson == "Bob" );
	assert( groovy.myLine.myFirst->myItem == "Bob" );
	assert( groovy.mySecondPerson == "DJ" );
	assert( groovy.myLine.myLast->myItem == "DJ" );
	cout << " 0 " << flush;

	// normal case inserting before the first person
	groovy.myLine.insertBefore("Bob", "Ann");
	assert( groovy.myLine.mySize == 3 );
	assert( groovy.myLine.myFirst->myItem == "Ann" );
	assert( groovy.myLine.myFirst->myNext->myItem == "Bob" );
	assert( groovy.myLine.myLast->myItem == "DJ" );
	cout << " 1 " << flush;

	// try inserting after a non-existent member
	if (!groovy.myLine.insertBefore("Ian", "Henry")) {
		cout << " 2a " << flush;
	} else {
		cerr << "Insert after worked on a non-existent member" << flush;
	}
	// this all should still be true:
	// invalid insertBefore shouldn't have changed anything
	assert( groovy.myLine.mySize == 3 );
	assert( groovy.myLine.myFirst->myItem == "Ann" );
	assert( groovy.myLine.myFirst->myNext->myItem == "Bob" );
	assert( groovy.myLine.myLast->myItem == "DJ" );
	cout << " 2b " << flush;

	// test inserting before the last member
	groovy.myLine.insertBefore("DJ", "Charlie");
	assert( groovy.myLine.mySize == 4 );
	assert( groovy.myLine.myFirst->myItem == "Ann" );
	assert( groovy.myLine.myFirst->myNext->myItem == "Bob" );
	assert( groovy.myLine.myFirst->myNext->myNext->myItem == "Charlie" );
	assert( groovy.myLine.myLast->myItem == "DJ" );
	cout << " 3 " << flush;


	cout << " Passed!" << endl;
}

void ListTester::testInsertionOperator() {
	cout << "Testing operator<<... " << flush;
	CongaLine line("Alpha", "Bravo");
	line.myLine.insertAfter("Bravo", "Charlie");

	// write the CongaLine's List to cout to make sure it matches what is expected
	cout << endl << line.myLine << endl;

	cout << " ^^^ Expecting..." << endl << "'Alpha=Bravo=Charlie='" << flush;
	cout << " 0 " << flush;


	cout << " Passed!" << endl;
}
