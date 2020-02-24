/*
 * List.cpp
 *
 *  Created on: Mar 5, 2019
 *      Author: Duncan Van Keulen (djv78)
 *
 *  Project Methods:
 *  @author: Duncan Van Keulen
 *  	operator== (and test)
 *  	readFrom(stream) (and test)
 *  	writeTo(file) (and test)
 *  	prepend() (and test)
 *  	insert(item, index) (and test)
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

/* Equality operator overloading
 * @param const List& rhs: The list object to be compared with
 * precondition: Both lists have to exists
 * returns: Will return a boolean value indicating whether the lists
 * 										        contain all the same items
 * @author: Duncan Van Keulen
 */
bool List::operator==(const List& rhs) {
	if (rhs.mySize == mySize) {
		Node* myPtr = myFirst;
		Node* itsPtr = rhs.myFirst;

		while (myPtr != NULL || itsPtr != NULL) {
			if (myPtr->myItem == itsPtr->myItem) {
				myPtr = myPtr->myNext;
				itsPtr = itsPtr->myNext;
			} else { return false; }
		}
		return true;
	}
	return false;
}

/* Read from a stream
 * Reads values separated by whitespace into the list from a stream
 * 													until a newline
 * @param istream& in: The stream to read from
 * precondition: Stream exists and can be read from
 * postcondition: List will be filled with the items from one line of the stream
 * @author: Duncan Van Keulen
 */
void List::readFrom(istream& in) {
	Item thing;
	while (in >> thing) {
		append(thing);
	}
}

/* Write to a file
 * Writes the contents of a list to the specified file
 * @param const string& filename: The name of the file to be written to
 * @param string separator: The desired separator between the items of the list
 * 						    Defaults to "\t"
 * precondition: List exists and has items
 * postcondition: The contents of the list will be written to the file
 * @author: Duncan Van Keulen
 */
void List::writeTo(const string& filename, string separator) {
	Node* myPtr = myFirst;
	ofstream fout(filename.c_str());
	assert( fout.is_open() );
	for (unsigned i = 0; i < mySize; ++i) {
		fout << myPtr->myItem << separator;
		myPtr = myPtr->myNext;
	}
	fout.close();
}

/* Prepend an item to the beginning of the list
 * @param const Item& it: The item to be prepended to the list
 * precondition: The list has to exist
 * postcondition: The item will be added to the beginning of the list
 * @author: Duncan Van Keulen
 */
void List::prepend(const Item& it) {
	if (mySize == 0) {
		myFirst = myLast = new Node(it, NULL);
	} else {
		myFirst = new Node(it, myFirst);
	}
	mySize++;
}

/* Insert an item to a specified index of the list
 * @param constItem& it: The item to be inserted
 * @param unsigned index: The index to be inserted to
 * precondition: List has to exist
 * postcondition: The item will be inserted at the specified index (started at 0)
 * @author: Duncan Van Keulen
 */
void List::insert(const Item& it, unsigned index) {
	if (index == 0) {
		prepend(it);
	} else if (index > mySize - 1 ) {
		append(it);
	} else {
		Node* traverse = myFirst;
		for (unsigned i = 0; i < (index - 1); i++) {
			traverse = traverse->myNext;
		}
		Node* insPtr = new Node(it, traverse->myNext);
		traverse->myNext = insPtr;
		mySize++;
	}
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
