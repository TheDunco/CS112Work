/* Stack.cpp defines the dynamically allocated (array-based ) Stack operations.
 * Joel Adams, for CS 112 at Calvin College.
 * Student Name: Duncan Van Keulen
 * Date: 26 March 2019
 */

#include "Stack.h"

/* explicit-value constructor
 * Parameter: capacity, an unsigned value.
 * Precondition: capacity > 0.
 * Postcondition: mySize == 0 && myCapacity == capacity
 *              && myArray contains the address of a dynamic array of 'capacity' entries.
 */
Stack::Stack(unsigned capacity) {
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
Stack::Stack(const Stack& original) {
	makeCopyOf(original);
}

/* utility method containing code refactored from
 *  the copy constructor and operator=.
 * Parameter: original, a Stack (const reference).
 * Precondition: original.myCapacity > 0.
 * Postcondition: I am a copy of original.
 */
void Stack::makeCopyOf(const Stack& original) {
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
bool Stack::isEmpty() const {
	return mySize == 0;
}

/*
 * Tests if the stack is full
 * precondition: Stack must exist
 * returns: a boolean value indicating if whether or not the
 * 			stack is full
 * @author (lab): Duncan Van Keulen
 */
bool Stack::isFull() const {
	return mySize >= myCapacity;
}

/*
 * Returns the item at the top of the stack
 * precondition: The stack must exist and not be empty
 * returns: The item that was last pushed to the stack
 * @author (lab): Duncan Van Keulen
 */
Item Stack::peekTop() const {
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
void Stack::push(Item it) {
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
Item Stack::pop() {
	if ( isEmpty() ) {
		throw StackException("pop():", "stack is empty");
	}
	--mySize;
	return myArray[mySize];
}

/* destructor
 * Postcondition: myCapacity == 0 && mySize == 0
 *             && myArray has been deallocated.
 */
Stack::~Stack() {
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
Stack& Stack::operator=(const Stack& original) {
	if (this != &original) {
		delete [] myArray;
		makeCopyOf(original);
	}
	return *this;
}

