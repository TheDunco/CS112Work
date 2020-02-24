/* StackTester.cpp defines test-methods for the 
 *  dynamically allocated (array) Stack operations
 * Joel Adams, for CS 112 at Calvin College
 */

#include "StackTester.h"
#include "Stack.h"
#include <iostream>  // cout, cerr, ...
#include <cassert>   // assert()
#include <cstdlib>   // exit()
using namespace std;

void StackTester::runTests() {
	cout << "Testing Stack class..." << endl;
	testConstructor();
	testIsEmpty();
	testPushPeekTopAndIsFull();
	testPop();
	testCopyConstructor();
	testAssignment();
	testDestructor();
	testGetterMethods();
	cout << "All tests passed!" << endl << endl;
}

void StackTester::testConstructor() {
	cout << "- Testing constructor... " << flush;
	// invalid parameter
	try {
		Stack<double> s1(0);
		cerr << "\nConstructed stack of size 0\n";
		exit(1);
	} catch (const StackException& se) {
		cout << se << flush;
		cout << " 0 " << flush;
	}
	// valid parameter
	Stack<double> s2(3);
	cout << " 1 " << flush;
	cout << " Passed!" << endl;
}

void StackTester::testIsEmpty() {
	cout << "- Testing isEmpty()... " << flush;
	// capacity 1
	Stack<double> s1(1);
	assert( s1.isEmpty() );
	cout << " 1 " << flush;
	// capacity > 1
	Stack<double> s2(3);
	assert( s2.isEmpty() );
	cout << " 2 " << flush;
	cout << " Passed!" << endl;
}


void StackTester::testPushPeekTopAndIsFull() {
	cout << "- Testing push()... " << flush;
	// test with capacity 1
	Stack<double> s1(1);
	s1.push(11);
	assert( s1.peekTop() == 11 );
	assert( !s1.isEmpty() );
	assert( s1.isFull() );
	try {
		s1.push(22);
		cerr << "\npush() worked on a full stack (size 1)\n";
		exit(1);
	} catch (const StackException& se) {
		cout << " 1 " << flush;
	}
	// test with capacity > 1
	Stack<double> s2(3);
	s2.push(11);
	assert( s2.peekTop() == 11 );
	s2.push(22);
	assert( s2.peekTop() == 22 );
	s2.push(33);
	assert( s2.peekTop() == 33 );
	try {
		s2.push(44);
		cerr << "\npush() worked on a full stack (size 3)\n";
		exit(1);
	} catch (const StackException& se) {
		cout << " 2 " << flush;
	}
	cout << " Passed! " << endl;
}

void StackTester::testPop() {
	cout << "- Testing pop()... " << flush;
	// try empty, capacity 1
	Stack<double> s1(1);
	assert( s1.isEmpty() );
    try {
            s1.peekTop();
            cerr << "\npeekTop() worked on empty stack (size 1)\n";
            exit(1);
    } catch (const StackException& se) {
            cout << " 0a " << flush;
    }
	try {
		s1.pop();
		cerr << "\npop() worked on empty stack (size 1)\n";
		exit(1);
	} catch (const StackException& se) {
		cout << " 0b " << flush;
	}

//	 try empty, capacity > 1
	Stack<double> s2(3);
	try {
		s2.pop();
		cerr << "\npop() worked on empty stack (size 3)\n";
		exit(1);
	} catch (const StackException& se) {
		cout << " 1a " << flush;
	}
    try {
            s2.peekTop();
            cerr << "\npeekTop() worked on empty stack (size 3)\n";
            exit(1);
    } catch (const StackException& se) {
            cout << " 1b " << flush;
    }

	// try non-empty, capacity 1
	Stack<double> s3(1);
	s3.push(11);
	assert( s3.peekTop() == 11 );
	assert( s3.pop() == 11 );
	cout << " 2 " << flush;
	try {
		s3.pop();
		cerr << "\ns3.pop() worked on empty stack (size 1)\n";
		exit(1);
	} catch (const StackException& se) {
		cout << " 2a " << flush;
	}
    try {
            s3.peekTop();
            cerr << "\ns3.peekTop() worked on empty stack (size 1)\n";
            exit(1);
    } catch (const StackException& se) {
            cout << " 2b " << flush;
    }

	// try non-empty, capacity > 1
	Stack<double> s4(3);
	s4.push(11);
	s4.push(22);
	s4.push(33);
	assert( s4.peekTop() == 33 );
	assert( s4.pop() == 33 );
	assert( s4.peekTop() == 22 );
	assert( s4.pop() == 22 );
	assert( s4.peekTop() == 11 );
	assert( s4.pop() == 11 );
	cout << " 3 " << flush;
	try {
		s4.pop();
		cerr << "\ns4.pop() worked on empty stack (size 3)\n";
		exit(1);
	} catch (const StackException& se) {
		cout << " 3a " << flush;
	}
    try {
            s4.peekTop();
            cerr << "\ns4.peekTop() worked on empty stack (size 3)\n";
            exit(1);
    } catch (const StackException& se) {
            cout << " 3b " << flush;
    }

	cout << " Passed!" << endl;
}

void StackTester::testCopyConstructor() {
	cout << "- Testing copy constructor... " << flush;
	// minimal empty Stack
	Stack<double> s1(1);
	Stack<double> s2(s1);
	assert( s2.isEmpty() );
	assert( s2.myArray != NULL );
	assert( s2.myCapacity == 1 );
	assert( s2.myArray != s1.myArray );
	cout << " 1 " << flush;
	// minimal non-empty Stack
	Stack<double> s3(1);
	s3.push(11);
	Stack<double> s4(s3);
	assert( !s4.isEmpty() );
	assert( s4.isFull() );
	assert( s4.peekTop() == 11 );
	assert( s4.myArray != s3.myArray );
	cout << " 2 " << flush;
	// non-minimal, non-empty stack
	Stack<double> s5(3);
	s5.push(11);
	s5.push(22);
	s5.push(33);
	Stack<double> s6(s5);
	assert( s6.myCapacity == s5.myCapacity );
	assert( s6.mySize == s5.mySize );
	assert( s6.myArray != s5.myArray );
	assert( s6.pop() == 33 );
	assert( s6.pop() == 22 );
	assert( s6.pop() == 11 );
	assert( s5.peekTop() == 33 );
	cout << " 3 " << flush;
	cout << "Passed!" << endl;
}

void StackTester::testAssignment() {
	cout << "- Testing assignment... " << flush;
	// minimal empty Stacks, same size
	Stack<double> s1(1);
	Stack<double> s2(1);
	s2 = s1;
	assert( s2.isEmpty() );
	assert( s2.myArray != NULL );
	assert( s2.myArray != s1.myArray );
	assert( s2.myCapacity == 1 );
	cout << " 1 " << flush;
	// minimal non-empty Stack to empty Stack, same capacity
	Stack<double> s3(1);
	s3.push(11);
	Stack<double> s4(1);
	s4 = s3;
	assert( !s4.isEmpty() );
	assert( s4.isFull() );
	assert( s4.peekTop() == 11 );
	assert( s4.myArray != s3.myArray );
	cout << " 2 " << flush;
	// minimal empty stack to non-empty stack, same capacity
	Stack<double> s5(1);
	Stack<double> s6(1);
	s6.push(11);
	s6 = s5;
	assert( s6.isEmpty() );
	assert( s6.myArray != NULL );
	assert( s6.myArray != s5.myArray );
	assert( s6.myCapacity == 1 );
	cout << " 3 " << flush;
	// non-minimal non-empty stack to empty stack, different capacities
	Stack<double> s7(3);
	s7.push(11);
	s7.push(22);
	s7.push(33);
	Stack<double> s8(2);
	s8 = s7;
	assert( s8.myArray != s7.myArray );
	assert( s8.myCapacity == s7.myCapacity );
	assert( s8.mySize == s7.mySize );
	assert( s8.pop() == 33 );
	assert( s8.pop() == 22 );
	assert( s8.pop() == 11 );
	assert( s7.peekTop() == 33 );
	cout << " 4 " << flush;
	// non-minimal, empty stack to non-empty stack, different capacities
	Stack<double> s9(2);
	Stack<double> s10(3);
	s10.push(11);
	s10.push(22);
	s10.push(33);
	s10 = s9;
	assert( s10.isEmpty() );
	assert( s10.myArray != s9.myArray );
	assert( s10.myCapacity == s10.myCapacity );
	cout << " 5 " << flush;
	// self-assignment, minimal size
	Stack<double> s11(1);
	s11.push(11);
	s11 = s11;
	assert( s11.isFull() );
	assert( !s11.isEmpty() );
	cout << " 6 " << flush;
	// chaining
	Stack<double> s12(2);
	s12.push(11);
	s12.push(22);
	Stack<double> s13(1);
	Stack<double> s14(1);
	s14 = s13 = s12;
	assert( s14.isFull() );
	assert( s14.myArray != s13.myArray );
	assert( s14.myArray != s12.myArray );
	assert( s14.pop() == 22 );
	assert( s14.pop() == 11 );
	assert( s14.isEmpty() );
	cout << " 7 " << flush;
      // self-assignment, non-minimal size
      s13 = s13;
	assert( !s13.isEmpty() );
	assert( s13.isFull() );
	assert( s13.pop() == 22 );
	assert( s13.pop() == 11 );
	assert( s13.isEmpty() );
	cout << " 8 " << flush;
	cout << "Passed!" << endl;
}

void StackTester::testDestructor() {
	cout << "- Testing destructor..." << flush;
	// minimal, empty
	Stack<double> s1(1);
	s1.~Stack();
	assert( s1.isEmpty() );
	assert( s1.myArray == NULL );
	assert( s1.myCapacity == 0 );
	cout << " 1 " << flush;
	// minimal, non-empty
	Stack<double> s2(1);
	s2.push(11);
	s2.~Stack();
	assert( s2.isEmpty() );
	assert( s2.myArray == NULL );
	assert( s2.myCapacity == 0 );
	cout << " 2 " << flush;
	// non-minimal, empty
	Stack<double> s3(3);
	s3.~Stack();
	assert( s3.isEmpty() );
	assert( s3.myArray == NULL );
	assert( s3.myCapacity == 0 );
	cout << " 3 " << flush;
	// non-minimal, non-empty
	Stack<double> s4(3);
	s4.push(11);
	s4.push(22);
	s4.push(33);
	s4.~Stack();
	assert( s4.isEmpty() );
	assert( s4.myArray == NULL );
	assert( s4.myCapacity == 0 );
	cout << " 4 " << flush;
	cout << " Passed!" << endl;
}

void StackTester::testGetterMethods() {
	cout << "- Testing Getter Methods..." << endl;

	cout << "- Testing getSize()... " << flush;
	// empty stack
	Stack<double> aStack(2);
	assert( aStack.getSize() == 0 );
	// one item, size should be 1
	aStack.push(11);
	assert( aStack.getSize() == 1 );
	// two items, size should be 2
	aStack.push(22);
	assert( aStack.getSize() == 2 );
	// remove an item and make sure size is again 1
	assert( aStack.pop() == 22 );
	assert( aStack.getSize() == 1 );
	cout << " 0 " << flush;

	cout << " Passed!" << endl;


	cout << "- Testing getCapacity()... " << flush;
	// make sure the capacity of aStack from above is 2
	assert( aStack.getCapacity() == 2 );
	cout << " 0 " << flush;
	Stack<double> anotherStack(3);
	assert( anotherStack.getCapacity() == 3 );
	anotherStack.push(99); anotherStack.push(88);
	assert( anotherStack.getCapacity() == 3 );
	anotherStack.push(77);
	assert( anotherStack.getCapacity() == 3 );
	cout << " 1 " << flush;

	cout << " Passed!" << endl;


	cout << "- Testing setCapacity(newCapacity)... " << flush;
	// setting the capacity with nothing in the stack
	Stack<double> stack0(2);
	assert( stack0.getCapacity() == 2 );
	stack0.setCapacity(5);
	assert( stack0.getCapacity() == 5 );
	assert( stack0.isEmpty() );
	assert( !stack0.isFull() );
	stack0.push(11); stack0.push(22); stack0.push(33);
	stack0.push(44); stack0.push(55);
	assert( stack0.isFull() );

	cout << " 0 " << flush;

	// setting the capacity with one thing in the stack
	Stack<double> stack1(1);
	stack1.push(11);
	assert( stack1.getCapacity() == 1 );
	assert( stack1.peekTop() == 11 );
	assert( stack1.isFull() );
	assert( !stack1.isEmpty() );
	stack1.setCapacity(3);
	assert( stack1.getCapacity() == 3 );
	stack1.push(22); stack1.push(33);
	assert( stack1.isFull() );
	assert( stack1.pop() == 33 );
	assert( stack1.pop() == 22 );
	assert( stack1.pop() == 11 );
	assert( stack1.isEmpty() );

	cout << " 1 " << flush;

	// setting the capacity with multiple things in the stack
	Stack<double> stack2(2);
	stack2.push(11);
	stack2.push(22);
	assert( stack2.isFull() );
	assert( !stack2.isEmpty() );
	assert( stack2.getCapacity() == 2 );
	stack2.setCapacity(4);
	assert( stack2.getCapacity() == 4 );
	stack2.push(33); stack2.push(44);
	assert( stack2.isFull() );
	assert( stack2.pop() == 44 );
	assert( stack2.pop() == 33 );
	assert( stack2.pop() == 22 );
	assert( stack2.pop() == 11 );
	assert( stack2.isEmpty() );

	cout << " 2 " << flush;

	// setting the capacity to 0 (should throw an error)
	Stack<double> stack3(10);
	assert( stack3.getCapacity() == 10 );
	stack3.push(99); stack3.push(88);
	try {
		stack3.setCapacity(0); // should throw an error
		cerr << "setCapacity(0) worked..." << flush;
		exit(1);
	} catch (const invalid_argument& ia) {
		assert( stack3.getCapacity() == 10 );
		assert( stack3.pop() == 88 );
		assert( stack3.pop() == 99 );
		assert( stack3.isEmpty() );

		cout << " 3 " << flush;
	}

	// try setting the capacity to something less than the current capacity
	Stack<double> stack4(4);
	assert( stack4.getCapacity() == 4 );
	stack4.push(99); stack4.push(88);
	try {
		stack4.setCapacity(3); // should throw an error
		cerr << "setCapacity(<getSize()) worked..." << flush;
		exit(1);
	} catch (const invalid_argument& ia) {
		assert( stack4.getCapacity() == 4 );
		assert( stack4.pop() == 88 );
		assert( stack4.pop() == 99 );
		assert( stack4.isEmpty() );

		cout << " 4 " << flush;
	}

	cout << " Passed!" << endl;
}

