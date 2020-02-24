/* ArrayQueue.cpp defines the methods for class ArrayQueue.
 * Joel Adams, for CS 112 at Calvin College.
 * Student name: Duncan Van Keulen
 * Date: 11 April 2019
 */

#include "ArrayQueue.h"
#include <cstring>      // memcpy()
using namespace std;

/* Explicit capacity constructor
 * @param const int& cap: The desired dynamic array capacity
 * Postcondition: All array instance variables will be initialized to appropriate values
 * @author: Duncan Van Keulen (lab)
 */
ArrayQueue::ArrayQueue(const int& cap) {
	if (cap < 1) {
		throw QueueException("ArrayQueue::ArrayQueue", "Cannot have capacity zero");
	}
	mySize = myFirstIndex = 0;
	myLastIndex = cap - 1;
	myCapacity = cap;
	myArrayPtr = new Item[cap];
}

/* copy constructor
 * @param: original, the ArrayQueue to be copied.
 * Postcondition: I am a deep copy of original.
 */
ArrayQueue::ArrayQueue(const ArrayQueue& original) {
	makeCopyOf(original);
}

/* utility method to build copies
 * @param: original, the ArrayQueue to be copied.
 * Postcondition: I am a deep copy of original.
 */
void ArrayQueue::makeCopyOf(const ArrayQueue& original) {
	mySize = original.mySize;
	myCapacity = original.myCapacity;
	myFirstIndex = original.myFirstIndex;
	myLastIndex = original.myLastIndex;
	myArrayPtr = new Item[myCapacity];
	memcpy(myArrayPtr, original.myArrayPtr, myCapacity*sizeof(Item) );
}

/* destructor
 * Postcondition: my dynamic array has been deallocated.
 */
ArrayQueue::~ArrayQueue() {
	delete [] myArrayPtr;
	myArrayPtr = NULL;
	mySize = myFirstIndex = myLastIndex = 0;
}

/* assignment operator
 * @param: aQueue, an ArrayQueue/
 * @return: myself.
 * Postcondition: I am a deep copy of aQueue.
 */
ArrayQueue& ArrayQueue::operator=(const ArrayQueue& aQueue) {
	if (this != &aQueue) {
		delete [] myArrayPtr;
		makeCopyOf(aQueue);
	}
	return *this;
}

/* Am I empty?
 * @return: true if I am empty, false othewise.
 */
bool ArrayQueue::isEmpty() const {
	return mySize == 0;
}

/* Am I full?
 * @return: true if I am full, false othewise.
 */
bool ArrayQueue::isFull() const {
	return getSize() == myCapacity;
}

/* accessor for myCapacity
 * @return myCapacity.
 */
unsigned ArrayQueue::getCapacity() const {
	return myCapacity;
}

/* accessor for mySize
 * @return mySize.
 */
unsigned ArrayQueue::getSize() const {
	return mySize;
}

/* First item accessor
 * precondition: Queue must not be empty
 * @return: The item in the array at index myFirstIndex
 * @author: Duncan Van Keulen (lab)
 */
Item ArrayQueue::getFirst() const {
	if ( isEmpty() ) {
		throw EmptyQueueException("ArrayQueue::getFirst()");
	}
	return myArrayPtr[myFirstIndex];
}

/* Last item accessor
 * precondition: Queue must not be empty
 * @return: The item in the array at index myLastIndex
 * @author: Duncan Van Keulen (lab)
 */
Item ArrayQueue::getLast() const {
	if ( isEmpty() ) {
		throw EmptyQueueException("ArrayQueue::getLast()");
	}
	return myArrayPtr[myLastIndex];
}

/* Append an item to the tail of the queue
 * @param const Item& it: The item to be appended to the queue
 * precondition: Queue must not be full
 * postcondition: The Item will be appended to the tail of the queue
 * 				  in wrap-around fashion
 * @author: Duncan Van Keulen
 */
void ArrayQueue::append(const Item& it) {
	if ( isFull() ) {
		throw FullQueueException("ArrayQueue::append()");
	}
	myLastIndex = (myLastIndex + 1 ) % myCapacity;
	myArrayPtr[myLastIndex] = it;
	++mySize;
}

/* Remove an Item from the head of the queue
 * precondition: Queue must not be empty
 * postcondition: The first Item will be removed from the queue
 * 				  in wrap-around fashion
 * @return: The Item that was removed from the queue
 * @author: Duncan Van Keulen
 */
Item ArrayQueue::remove() {
	if ( isEmpty() ) {
		throw EmptyQueueException("ArrayQueue::remove()");
	}
	Item temp = myArrayPtr[myFirstIndex];
	myFirstIndex = (myFirstIndex + 1) % myCapacity;
	--mySize;
	return temp;
}
