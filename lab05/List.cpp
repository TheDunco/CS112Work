/*
 * List.cpp
 *
 *  Created on: Mar 5, 2019
 *      Author: Duncan Van Keulen (djv78)
 */

#include "List.h"

// Default List constructor
List::List() {
	mySize = 0;
	myFirst = myLast = NULL;

}

// Function to make a copy of a List
void List::makeCopyOf(const List& original) {
	myFirst = myLast = NULL; //  set pointers
	mySize = 0; //   and size to 'empty' values
	Node* oPtr = original.myFirst; //  start at the first node
	while (oPtr != NULL) {
		//  while there are nodes to copy:
		append(oPtr->myItem); //   append the item in that node
		oPtr = oPtr->myNext; //   advance to next node
	}
}

// List copy constructor
List::List(const List& original) {
	makeCopyOf(original);
}

// Node Default constructor
List::Node::Node() {
	myItem = Item();
	myNext = NULL;
}

// Node explicit constructor
List::Node::Node(Item it, Node* next) {
	myItem = it;
	myNext = next;
}

// Accessor for the first Item of the list
Item List::getFirst() const {
	if (mySize < 0 || myLast == NULL) {
		throw underflow_error("An attempt was made to access an empty list item");
	}
	return myFirst->myItem;
}

// Accessor for the last Item of the list
Item List::getLast() const {
	if (mySize < 0 || myLast == NULL) {
		throw underflow_error("An attempt was made to access an empty list item");
	}
	return myLast->myItem;
}

// Function to append Items to the back of the list
void List::append(const Item& it) {
	Node* nodePtr = new Node(it, NULL);
	if (mySize == 0) {
		myFirst = nodePtr;
	} else {
		myLast->myNext = nodePtr;
	}
	mySize++;
	myLast = nodePtr;
}

// Overload the assignment operator
List& List::operator=(const List& original) {
	if (this != &original) {
		this->~List();				  // Invoke the List's destructor to clean up
		makeCopyOf(original);
	}
	return *this;
}

//List::~List() {
//   Node* first = myFirst;     // initialize both to point at the first node
//   Node* next = first;
//   while (first != NULL) {    // while there are nodes to be processed:
//      next = first->myNext;   //   save the address of the next node
//      delete first;           //   delete the first node
//      first = next;           //   make first point to the next node
//   }
//   myFirst = myLast = NULL;
//   mySize = 0;
//}

// List destructor
List::~List() {
   delete myFirst;          // delete first node, invoking ~Node() (does nothing if myFirst == NULL)
   myFirst = myLast = NULL; // clear myFirst and myLast (optional)
   mySize = 0;              // clear mySize (optional)
}

// Node destructor
List::Node::~Node() {
//   cout << "~Node() is deallocating the node containing item "
//			 << myItem << endl;
   delete myNext;       // delete the next node, invoking ~Node() in it
                        // (does nothing if myNext == NULL)
}
