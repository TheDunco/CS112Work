/* LinkedQueue.cpp defines the methods for class LinkedQueue.
 * Joel Adams, for CS 112 at Calvin College.
 * Student name: Duncan Van Keulen
 * Date: 11 April 2019
 */

#include "LinkedQueue.h"

LinkedQueue::LinkedQueue() {
	mySize = 0;
	myFirstPtr = myLastPtr = nullptr;
}

LinkedQueue::LinkedQueue(const LinkedQueue& original) {
	makeCopyOf(original);
}

void LinkedQueue::makeCopyOf(const LinkedQueue& original) {
	mySize = original.mySize;
	if ( mySize == 0 ) {
		myFirstPtr = myLastPtr = NULL;
	} else {
		myFirstPtr = new Node(original.getFirst(), NULL);
		Node * temp0 = original.myFirstPtr->myNextPtr;
		Node * temp1 = myFirstPtr;
		while (temp0 != NULL) {
			temp1->myNextPtr = new Node(temp0->myItem, NULL);
			temp1 = temp1->myNextPtr;
			temp0 = temp0->myNextPtr;
		}
		myLastPtr = temp1;
	}
}

LinkedQueue::~LinkedQueue() {
	delete myFirstPtr;
	myFirstPtr = myLastPtr = NULL;
	mySize = 0;
}

LinkedQueue& LinkedQueue::operator=(const LinkedQueue& aQueue) {
	if (this != &aQueue) {
		delete myFirstPtr;    // invokes recursive ~Node()
		makeCopyOf(aQueue);
	}
	return *this;
}


/* Getter for the first item
 * precondition: Queue must not be empty
 * @return: The item that is first in the queue
 * @author: Duncan Van Keulen (lab)
 */
Item LinkedQueue::getFirst() const {
	if ( isEmpty() ) {
		throw EmptyQueueException("LinkedQueue::getFirst()");
	}
	return myFirstPtr->myItem;
}

/* Getter for the last item
 * precondition: Queue must not be empty
 * @return: The item that is last in the queue
 * @author: Duncan Van Keulen (lab)
 */
Item LinkedQueue::getLast() const {
	if ( isEmpty() ) {
		throw EmptyQueueException("LinkedQueue::getLast()");
	}
	return myLastPtr->myItem;
}

/* Appends an Item to the end of the queue
 * @param const Item& it: The Item that will be in the appended node
 * Precondition: Queue program must not be out of memory (full)
 * Postcondition: A node with myItem Item will be appended to the back of the queue
 * @author: Duncan Van Keulen (lab)
 */
void LinkedQueue::append(const Item& it) {
//	try {
	Node* nPtr = new Node(it, nullptr);
//	} catch( const bad_alloc& ) {
//		throw FullQueueException("LinkedQueue::append");
//	}
	if ( isEmpty() ) {
		myFirstPtr = nPtr;
	} else {
		myLastPtr->myNextPtr = nPtr;
	}
	myLastPtr = nPtr;
	++mySize;
}

/* Remove an Item from the beginning of the queue
 * Precondition: Queue must not be empty
 * Postcondition: The node at the head of the queue will be deleted
 * @return: The Item that was in the node that was deleted
 * @author: Duncan Van Keulen (lab)
 */
Item LinkedQueue::remove() {
	if ( isEmpty() ) {
		throw EmptyQueueException("LinkedQueue::remove()");
	}
	// temporarily store the Item and address of next node
	Item tempIt = myFirstPtr->myItem;
	Node* tempPtr = myFirstPtr->myNextPtr;


	myFirstPtr->myNextPtr = nullptr; // break node from chain
	delete myFirstPtr; 		   		 // delete node
	myFirstPtr = tempPtr;	   		 // make the previous next node the first node

	--mySize;				   		 // decrement mySize

	return tempIt;
}


