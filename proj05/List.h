/*
 * List.h <Template>
*  Created on: Mar 5, 2019
 *      Author: Duncan Van Keulen (djv78)
 *      Author: Andrew Vrieland (ajv234)
 *
 *  Project Methods:
 *  @author: Duncan Van Keulen
 *  	operator== (and test)
 *  	readFrom(stream) (and test)
 *  	writeTo(file) (and test)
 *  	prepend() (and test)
 *  	insert(item, index) (and test)
 *  @author: Andrew Vrieland (ajv234)
 *  	inequality (and test)
 *  	writeTo(stream) (and test)
 *  	readFrom(stream) (and test)
 *  	getIndexOf() (and test)
 *  	remove() (and test)
 */

#ifndef LIST_H_
#define LIST_H_

#include <iostream>
#include <stdexcept>
#include <cassert>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

template<class Item>

class List {
public:
	List();
	List(const List<Item>& original);
	List<Item>& operator=(const List<Item>& original);
	void append(const Item& item);
	virtual ~List();
	unsigned getSize() const { return mySize; }
	Item getFirst() const;
	Item getLast() const;
	bool operator==(const List<Item>& rhs);
	void readFrom(istream& in);
	void writeTo(const string& str, string separator = "\t");
	void prepend(const Item& it);
	void insert(const Item& it, unsigned index);
	bool operator!=(const List<Item>& l2);
	void writeTo(ostream& out, string seperator);
	void readFrom(string fileName);
	unsigned getIndexOf(Item it);
	void remove(unsigned index);

private:
	struct Node{
		Node();
		Node(Item it, Node* next);
		~Node();

		Item myItem;
		Node* myNext;
	};

	unsigned mySize;
	Node* myFirst;
	Node* myLast;

	void makeCopyOf(const List& original);

	friend class ListTester;
};

// Default List constructor
template<class Item>
List<Item>::List() {
	mySize = 0;
	myFirst = myLast = NULL;

}

// Function to make a copy of a List
template<class Item>
void List<Item>::makeCopyOf(const List<Item>& original) {
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
template<class Item>
List<Item>::List(const List<Item>& original) {
	makeCopyOf(original);
}

// Node Default constructor
template<class Item>
List<Item>::Node::Node() {
	myItem = Item();
	myNext = NULL;
}

// Node explicit constructor
template<class Item>
List<Item>::Node::Node(Item it, Node* next) {
	myItem = it;
	myNext = next;
}

// Accessor for the first Item of the list
template<class Item>
Item List<Item>::getFirst() const {
	if (mySize < 0 || myLast == NULL) {
		throw underflow_error("An attempt was made to access an empty list item");
	}
	return myFirst->myItem;
}

// Accessor for the last Item of the list
template<class Item>
Item List<Item>::getLast() const {
	if (mySize < 0 || myLast == NULL) {
		throw underflow_error("An attempt was made to access an empty list item");
	}
	return myLast->myItem;
}

// Function to append Items to the back of the list
template<class Item>
void List<Item>::append(const Item& it) {
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
template<class Item>
List<Item>& List<Item>::operator=(const List<Item>& original) {
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
template<class Item>
bool List<Item>::operator==(const List<Item>& rhs) {
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
template<class Item>
void List<Item>::readFrom(istream& in) {
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
template<class Item>
void List<Item>::writeTo(const string& filename, string separator) {
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
template<class Item>
void List<Item>::prepend(const Item& it) {
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
template<class Item>
void List<Item>::insert(const Item& it, unsigned index) {
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


/*
 * Checks inequality between two lists
 * Precondition: Both lists have to exist
 * Postcondition: returns a boolean, true if not equal, false if they are equal
 *
 * Author: AJ Vrieland (ajv234)
 */
template<class Item>
bool List<Item>::operator!=(const List& l2){
	if (mySize != l2.mySize) {
		return true;
	}
	Node* mPtr = myFirst;
	Node* l2Ptr = l2.myFirst;
	for (unsigned i = 0; i < mySize; ++i) {
		if (mPtr->myItem != l2Ptr->myItem){
			return true;
		} else {
			mPtr = mPtr->myNext;
			l2Ptr = l2Ptr->myNext;
		}

	}
	return false;
}

/*
 * Writes to an ostream
 * Precondition: ostream must be open
 * Postcondition: contents of the list will be writen into the stream
 *
 * Author AJ Vrieland (ajv234)
 */
template<class Item>
void List<Item>::writeTo(ostream& out, string seperator) {
	Node* nPtr = myFirst;
	for (unsigned i = 0; i < mySize; ++i){
		out << nPtr->myItem << seperator;
		nPtr = nPtr->myNext;
	}
}

/*
 * Reads a list from a file
 * Precondition: the file must exist
 * Postcondition: a new list is created with the contents of the file
 *
 * Author AJ Vrieland (ajv234)
 */
template<class Item>
void List<Item>::readFrom(string fileName){
	fstream fin(fileName.c_str());
	assert(fin.is_open());
	string tempStr = " ";
	Item tempItem;
	getline(fin, tempStr);
	tempItem = atoi(tempStr.c_str());
	while ( tempStr != ""){
		append(tempItem);
		getline(fin, tempStr);
		tempItem = atoi(tempStr.c_str());
	}
	fin.close();
}

/*
 * Returns the Index of the item given
 * Precondition: The list must exist
 * Postcondition: The index of the given Item is returned
 *
 * Author AJ Vrieland (ajv234)
 */
template<class Item>
unsigned List<Item>::getIndexOf(Item it){
	Node* nPtr = myFirst;
	unsigned index = 0;
	while (nPtr->myItem != it){
		nPtr = nPtr->myNext;
		++index;
		if (nPtr->myItem == myLast->myItem){
			if (nPtr->myItem != it){
				throw invalid_argument("Item does not exist");
			}
		}
	}
	return index;
}

/*
 * Removes a node at a given Index
 * Precondition: the Index must be within the boundaries
 * Postcondition: the node at a give Index is removed and all other Nodes move down one index
 *
 * Author AJ Vrieland (ajv234)
 */
template<class Item>
void List<Item>::remove(unsigned index){
	Node* nPtr1 = myFirst;
	Node* nPtr2 = myFirst;
	if (index == 0){
		myFirst = nPtr1->myNext;

	}else{
		for (unsigned i = 0; i < index; ++i) {
			nPtr1 = nPtr1->myNext;
		}
		for (unsigned i = 0; i < index - 1; ++i) {
			nPtr2 = nPtr2->myNext;
		}
		nPtr2->myNext = nPtr1->myNext;
	}
	nPtr1->myNext = NULL;
	mySize = mySize - 1;
	delete nPtr1;
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
template<class Item>
List<Item>::~List() {
   delete myFirst;          // delete first node, invoking ~Node() (does nothing if myFirst == NULL)
   myFirst = myLast = NULL; // clear myFirst and myLast (optional)
   mySize = 0;              // clear mySize (optional)
}

// Node destructor
template<class Item>
List<Item>::Node::~Node() {
//   cout << "~Node() is deallocating the node containing item "
//			 << myItem << endl;
   delete myNext;       // delete the next node, invoking ~Node() in it
                        // (does nothing if myNext == NULL)
}

#endif /* LIST_H_ */
