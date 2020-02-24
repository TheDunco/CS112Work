/* ArrayQueue.h declares a Queue class using a dynamic array.
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 * Student name: Duncan Van Keulen
 * Date: 11 April 2019
 * 
 * Class Invariant: 
 *    mySize == 0 ||
 *    mySize > 0 && myArray[myFirst] == getFirst()
 *               && myArray[myLast] == getLast().
 * 
 *  (When I am not empty:
 *     myFirstIndex is the index of my oldest value;
 *     myLastIndex is the index of my newest value.)
 */

#ifndef ARRAY_QUEUE_H_
#define ARRAY_QUEUE_H_

#include "QueueException.h"
#include <cstring>      // memcpy()
using namespace std;

template<class Item>
class ArrayQueue {
public:
	ArrayQueue(const int& cap);
	Item getFirst() const;
	Item getLast() const;
	void append(const Item& it);
	Item remove();
	void setCapacity(const unsigned& newCapacity);

	ArrayQueue(const ArrayQueue<Item>& original);
	virtual ~ArrayQueue();
	ArrayQueue& operator=(const ArrayQueue<Item>& original);
	unsigned getSize() const;
	unsigned getCapacity() const;
	bool isEmpty() const;
	bool isFull() const;

protected:
	virtual void makeCopyOf(const ArrayQueue& original);
private:
	unsigned mySize;       // number of items I contain
	unsigned myCapacity;   // how many items I can store
	unsigned myFirstIndex; // index of oldest item (if any)
	unsigned myLastIndex;  // index of newest item (if any)
	Item*    myArrayPtr;   // dynamic array of items

	friend class ArrayQueueTester;
};

/* Explicit capacity constructor
 * @param const int& cap: The desired dynamic array capacity
 * Postcondition: All array instance variables will be initialized to appropriate values
 * @author: Duncan Van Keulen (lab)
 */
template<class Item>
ArrayQueue<Item>::ArrayQueue(const int& cap) {
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
template<class Item>
ArrayQueue<Item>::ArrayQueue(const ArrayQueue<Item>& original) {
	makeCopyOf(original);
}

/* utility method to build copies
 * @param: original, the ArrayQueue to be copied.
 * Postcondition: I am a deep copy of original.
 */
template<class Item>
void ArrayQueue<Item>::makeCopyOf(const ArrayQueue<Item>& original) {
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
template<class Item>
ArrayQueue<Item>::~ArrayQueue() {
	delete [] myArrayPtr;
	myArrayPtr = NULL;
	mySize = myFirstIndex = myLastIndex = 0;
}

/* assignment operator
 * @param: aQueue, an ArrayQueue/
 * @return: myself.
 * Postcondition: I am a deep copy of aQueue.
 */
template<class Item>
ArrayQueue<Item>& ArrayQueue<Item>::operator=(const ArrayQueue<Item>& aQueue) {
	if (this != &aQueue) {
		delete [] myArrayPtr;
		makeCopyOf(aQueue);
	}
	return *this;
}

/* Am I empty?
 * @return: true if I am empty, false othewise.
 */
template<class Item>
bool ArrayQueue<Item>::isEmpty() const {
	return mySize == 0;
}

/* Am I full?
 * @return: true if I am full, false othewise.
 */
template<class Item>
bool ArrayQueue<Item>::isFull() const {
	return getSize() == myCapacity;
}

/* accessor for myCapacity
 * @return myCapacity.
 */
template<class Item>
unsigned ArrayQueue<Item>::getCapacity() const {
	return myCapacity;
}

/* accessor for mySize
 * @return mySize.
 */
template<class Item>
unsigned ArrayQueue<Item>::getSize() const {
	return mySize;
}

/* First item accessor
 * precondition: Queue must not be empty
 * @return: The item in the array at index myFirstIndex
 * @author: Duncan Van Keulen (lab)
 */
template<class Item>
Item ArrayQueue<Item>::getFirst() const {
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
template<class Item>
Item ArrayQueue<Item>::getLast() const {
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
template<class Item>
void ArrayQueue<Item>::append(const Item& it) {
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
template<class Item>
Item ArrayQueue<Item>::remove() {
	if ( isEmpty() ) {
		throw EmptyQueueException("ArrayQueue::remove()");
	}
	Item temp = myArrayPtr[myFirstIndex];
	myFirstIndex = (myFirstIndex + 1) % myCapacity;
	--mySize;
	return temp;
}

/* Dynamically set a new capacity for the array
 * @param const unsigned& newCapacity: The desired new capacity
 * 									   for the array to be set to
 * precondition: newCapacity must not be 0 or less than mySize
 * postcondition: Values from old array will be copied into a new array
 * 				  of the desired capacity in order, starting at index 0
 * 				  (dealing with the wrap-around)
 * @author: Duncan Van Keulen (project)
 */
template<class Item>
void ArrayQueue<Item>::setCapacity(const unsigned& newCapacity) {
	// throw exceptions if newCapcity is 0 or less than current capacity
	if ( newCapacity == 0 ) {
		throw QueueException("ArrayQueue<Item>::setCapacity",
				"Can't set capacity to 0");
	} else if ( newCapacity < getSize() ) {
		throw QueueException("ArrayQueue<Item>::setCapacity",
						"Can't set capacity less than current capacity");
	}

	/* create a new temporary array and copy myArrayPtr's items into it
	 * putting them in order in the new temporary array, negating the need to
	 * deal with the wrap around later
	 */
	Item* temp = new Item[newCapacity];
	for (unsigned i = 0; i < mySize; ++i) {
		temp[i] = myArrayPtr[(myFirstIndex + i) % myCapacity];
	}

	// update the indexes of the first and last item of the queue
	myFirstIndex = 0;
	myLastIndex = mySize - 1;

	// delete myArrayPtr to avoid a memory leak
	delete [] myArrayPtr;

	// set myArrayPtr to the temp array and update myCapacity
	myCapacity = newCapacity;
	myArrayPtr = temp;
}



#endif /*ARRAY_QUEUE_H_*/
