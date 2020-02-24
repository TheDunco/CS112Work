/* Stack.h provides a (dynamic-array-based) Stack class.
 * Joel Adams, for CS 112 at Calvin College.
 * Student Name: Duncan Van Keulen
 * Date: 26 March 2019
 * 
 * Invariant: mySize == 0 && isEmpty() && !isFull()
 *         || mySize == myCapacity && !isEmpty() && isFull()
 *         || mySize > 0 && mySize < myCapacity && !isEmpty() && !isFull().
 * Notes: 
 * 1. Member mySize always contains the index of the next empty space in myArray
 *        (the index of the array element into which the next pushed item will be placed).
 * 2. Sending push() to a full Stack throws the exception Stack::Overflow.
 * 3. Sending pop() or peekTop() to an empty Stack throws the exception Stack::Underflow.
 */

#ifndef STACK_H_
#define STACK_H_

#include "StackException.h"
#include <cstring>
#include <string>
#include <iostream>
using namespace std;

template<class Item>

class Stack {
public:
	Stack(unsigned capacity);
	Stack(const Stack<Item>& original);
	~Stack();
	Stack<Item>& operator=(const Stack<Item>& original);
	bool isEmpty() const;
	bool isFull() const;
	Item peekTop() const;
	void push(Item it);
	Item pop();
	unsigned getSize() const { return mySize; }
	unsigned getCapacity() const { return myCapacity; }
	void setCapacity(unsigned newCapacity);
	
protected:
	void makeCopyOf(const Stack<Item>& original);
	
private:
	unsigned myCapacity;
	unsigned mySize;
	Item*    myArray;
	friend class StackTester;
};

/* explicit-value constructor
 * Parameter: capacity, an unsigned value.
 * Precondition: capacity > 0.
 * Postcondition: mySize == 0 && myCapacity == capacity
 *              && myArray contains the address of a dynamic array of 'capacity' entries.
 */
template<class Item>
Stack<Item>::Stack(unsigned capacity) {
	if ( !(capacity > 0) ) {
		throw StackException(
				"Stack(capacity)", "capacity must be positive!");
	}
   mySize = 0;
   myCapacity = capacity;
   myArray = new Item[capacity];
}

/* copy constructor
 * Parameter: original, a Stack (const reference).
 * Postcondition: I am a copy of original.
 */
template<class Item>
Stack<Item>::Stack(const Stack<Item>& original) {
	makeCopyOf(original);
}

/* utility method containing code refactored from
 *  the copy constructor and operator=.
 * Parameter: original, a Stack (const reference).
 * Precondition: original.myCapacity > 0.
 * Postcondition: I am a copy of original.
 */
template<class Item>
void Stack<Item>::makeCopyOf(const Stack<Item>& original) {
	myCapacity = original.myCapacity;
	myArray = new Item[myCapacity];

	for (unsigned i = 0; i < myCapacity; i++) {
		myArray[i] = original.myArray[i];
	}
	mySize = original.mySize;
}

/*
 * Tests if the stack is empty
 * precondition: Stack must exist
 * returns: a boolean value indicating if whether or not the
 * 			stack is empty
 * @author (lab): Duncan Van Keulen
 */
template<class Item>
bool Stack<Item>::isEmpty() const {
	return mySize == 0;
}

/*
 * Tests if the stack is full
 * precondition: Stack must exist
 * returns: a boolean value indicating if whether or not the
 * 			stack is full
 * @author (lab): Duncan Van Keulen
 */
template<class Item>
bool Stack<Item>::isFull() const {
	return mySize >= myCapacity;
}

/*
 * Returns the item at the top of the stack
 * precondition: The stack must exist and not be empty
 * returns: The item that was last pushed to the stack
 * @author (lab): Duncan Van Keulen
 */
template<class Item>
Item Stack<Item>::peekTop() const {
	if ( isEmpty() ) {
		throw StackException("PeekTop()", "stack is empty");
	}
	else {
		return myArray[mySize - 1];
	}
}

/*
 * Pushes an item to the stack
 * @param Item it: The item to be pushed to the stack
 * precondition: Stack must exist and not be full
 * postcondition: Item will be pushed to stack and
 * 				  mySize will be incremented
 * @author (lab): Duncan Van Keulen
 */
template<class Item>
void Stack<Item>::push(Item it) {
	if ( isFull() ) {
		throw StackException("push()", "stack is full");
	}
	myArray[mySize] = it;
	mySize++;
}

/*
 * Pops an item from the list (removes and returns)
 * precondition: The stack must exist and not be empty
 * postcondition: The last item pushed will be removed and returned
 * Returns: The item that was removed
 * @author (lab): Duncan Van Keulen
 */
template<class Item>
Item Stack<Item>::pop() {
	if ( isEmpty() ) {
		throw StackException("pop():", "stack is empty");
	}
	--mySize;
	return myArray[mySize];
}

/*
 * Sets the capacity of the Stack
 * precondition: newCapacity must be greater than current capacity
 * @param unsigned newCapacity: The new capacity for the Stack
 * postcondition: The items in the Stack will be preserved but
 * 				  the capacity will be increased
 * @author: Duncan Van Keulen
 */
template<class Item>
void Stack<Item>::setCapacity(unsigned newCapacity) {
	// don't do anything if it's already at the correct capacity
	if (newCapacity == myCapacity) { return; }
	// error case handling
	if (newCapacity < getCapacity()) {
		throw invalid_argument(
		"Stack::setCapacity: newCapacity is less than current capacity");
	}
	// setting capacity logic
	Item* newArray = new Item[newCapacity];
	for (unsigned i = 0; i < myCapacity; i++) {
		newArray[i] = myArray[i];
	}
	delete [] myArray;
	myArray = newArray;
	myCapacity = newCapacity;

}

/* destructor
 * Postcondition: myCapacity == 0 && mySize == 0
 *             && myArray has been deallocated.
 */
template<class Item>
Stack<Item>::~Stack() {
	delete [] myArray;
	myArray = NULL;
	myCapacity = 0;
	mySize = 0;
}

/* assignment operator
 * Parameter: original, a Stack (const reference).
 * Postcondition: I am a copy of original
 *              && I have been returned.
 */
template<class Item>
Stack<Item>& Stack<Item>::operator=(const Stack<Item>& original) {
	if (this != &original) {
		delete [] myArray;
		makeCopyOf(original);
	}
	return *this;
}

#endif

