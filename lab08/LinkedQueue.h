/* LinkedQueue.h declares a Queue class using linked nodes.
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 * Student name: Duncan Van Keulen
 * Date: 11 April 2019
 * 
 * Class Invariant: 
 *    mySize == 0 && myFirstPtr == NULL && myLastPtr == NULL ||
 *    mySize > 0 && myFirstPtr == the address of a node containing the oldest item
 *               && myLastPtr == the address of a node containing the newest item.
 */

#ifndef LINKED_QUEUE_H_
#define LINKED_QUEUE_H_

#include "QueueException.h"

typedef int Item;

class LinkedQueue {
public:
	LinkedQueue();
	Item getFirst() const;
	Item getLast() const;
	void append(const Item& it);
	Item remove();

	LinkedQueue(const LinkedQueue& original);
	virtual ~LinkedQueue();
	LinkedQueue& operator=(const LinkedQueue& original);
	unsigned getSize() const { return mySize; }
	bool isEmpty() const { return mySize == 0; }
	bool isFull() const { return false; }

protected:
	void makeCopyOf(const LinkedQueue& original);
private:
	unsigned mySize;
	struct Node {
		Item myItem;
		Node * myNextPtr;
		
		Node(const Item& it, Node* nextPtr) { myItem = it; myNextPtr = nextPtr; }
		~Node() { delete myNextPtr; }
	};
	Node * myFirstPtr;
	Node * myLastPtr;

	friend class LinkedQueueTester;
};

#endif /*LINKED_QUEUE_H_*/

