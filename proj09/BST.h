/* BST.h declares a "classic" binary search tree template of linked nodes.
 * Joel Adams, for CS 112 at Calvin College.
 * Student Name: Duncan Van Keulen
 * Date: 23 April 2019
 * 
 * Class Invariant:
 *   myNumItems == 0 && myRoot == NULL ||
 *   myNumItems > 0 && 
 *     myRoot stores the address of a Node containing an item &&
 *       all items in myRoot->myLeft are less than myRoot->myItem &&
 *       all items in myRoot->myRight are greater than myRoot->myItem.
 */

#ifndef BST_H_
#define BST_H_

#include "Exception.h"
#include <iostream>
using namespace std;

template <class Item>

class BST {
public:

	virtual ~BST();
	bool isEmpty() const;
	unsigned getNumItems() const;

	void traverseInorder();
	void traversePreorder();
	void traversePostorder();

	void insert(const Item& it);
	BST();
	bool contains(const Item& it) const;

	unsigned getHeight() const;

private:
	struct Node {
		Node(const Item& it);
		virtual ~Node();

		void nodeInsert(const Item& it);
		bool nodeContains(const Item& it) const;

		unsigned nodeGetHeight() const;

		void traverseInorder();
		void traversePreorder();
		void traversePostorder();
		virtual void processItem();

		Item myItem;
		Node* myLeft;
		Node* myRight;
	};
	
	Node* myRoot;
	unsigned myNumItems;
	friend class BST_Tester;
};


#include "BST.h"


template <class Item>
BST<Item>::BST() {
	myNumItems = 0;
	myRoot = NULL;
}

template <class Item>
BST<Item>::~BST() {
	delete myRoot;
	myRoot = NULL;
	myNumItems = 0;
}

template <class Item>
BST<Item>::Node::Node(const Item& it) {
   myItem = it;
   myLeft = NULL;
   myRight = NULL;
}

template <class Item>
BST<Item>::Node::~Node() {
	delete myLeft;
	delete myRight;
}

template <class Item>
bool BST<Item>::isEmpty() const {
	return myNumItems == 0;
}

template <class Item>
unsigned BST<Item>::getNumItems() const {
	return myNumItems;
}


// Traversal methods...

/* Process the item ( in this case, cout it)
 * postcondition: Item will be processed
 */
template <class Item>
void BST<Item>::Node::processItem() {
		cout << ' ' << myItem;
}

/* BST Preorder Traversal
 * Initiate Node perorder traversal recursion
 */
template <class Item>
void BST<Item>::traversePreorder() {
	if ( !isEmpty() ) {
		myRoot->traversePreorder();
	}
}

/* Node Preorder Traversal
 * 1. Process Item
 * 2. Recurse left
 * 3. Recurse right
 */
template <class Item>
void BST<Item>::Node::traversePreorder() {
	processItem();
	if (myLeft != NULL) {
		myLeft->traversePreorder();
	}
	if (myRight != NULL) {
		myRight->traversePreorder();
	}
}

/* BST Postorder Traversal
 * Initiate Node postorder traversal recursion
 */
template <class Item>
void BST<Item>::traversePostorder() {
	if ( !isEmpty() ) {
		myRoot->traversePostorder();
	}
}
/* Node Postorder Traversal
 * 1. Recurse right
 * 2. Recurse left
 * 3. Process Item
 */
template <class Item>
void BST<Item>::Node::traversePostorder() {
	if (myLeft != NULL) {
		myLeft->traversePostorder();
	}
	if (myRight != NULL) {
		myRight->traversePostorder();
	}
	processItem();
}

/* BST Inorder Traversal
 * Initiate Node Inorder traversal recursion
 */
template <class Item>
void BST<Item>::traverseInorder() {
	if ( !isEmpty() ) {
		myRoot->traverseInorder();
	}
}

/* Node Inorder Traversal
 * 1. Recurse left
 * 2. Process Item
 * 3. Recurse right
 */
template <class Item>
void BST<Item>::Node::traverseInorder() {
	if (myLeft != NULL) {
		myLeft->traverseInorder();
	}
	processItem();
	if (myRight != NULL) {
		myRight->traverseInorder();
	}
}

/* Insert an item into the BST
 * @param const Item& it: The item to be added to the BST
 * precondition: Item cannot already be in the BST
 * postcondition: Item will be added to the BST
 * @author: Duncan Van Keulen (lab)
 */
template <class Item>
void BST<Item>::insert(const Item& it) {
	if ( isEmpty() ) {
		myRoot = new Node(it);
	} else {
		myRoot->nodeInsert(it);
	}
	myNumItems++;
}

/* Node insert method
 * @param const Item& it: The item to be added to the BST
 * precondition: Item cannot already be in a Node in the BST
 * postcondition: If it is greater than the item in the node,
 * 		it will be added to the left, and if it is greater, it
 * 		will be added to the right (if the pointer is NULL,
 * 		otherwise it will recurse to the next node)
 * @author: Duncan Van Keulen (lab)
 */
template <class Item>
void BST<Item>::Node::nodeInsert(const Item& it) {
	if ( it < myItem) {
		if ( myLeft == NULL ) {
			myLeft = new Node(it);
		} else {
			myLeft->nodeInsert(it);
		}
	}
	else if ( it > myItem) {
		if ( myRight == NULL ) {
			myRight = new Node(it);
		} else {
			myRight->nodeInsert(it);
		}
	}
	else {
		throw Exception("BST::Node::nodeInsert()", "item is already in the tree!\n");
	}
}

/* Check to see if an Item is in a BST
 * @param const Item& it: The Item to check the BST for
 * precondition: BST must exist
 * @return: A boolean indicating whether or not the
 * 			Item was found in the BST
 * @author: Duncan Van Keulen (lab)
 */
template <class Item>
bool BST<Item>::contains(const Item& it) const {
	if ( isEmpty() ) { return false; }
	else if ( myRoot->myItem == it ){
		return true;
	} else {
		return myRoot->nodeContains(it);
	}
}

/* Check to see if an Item is in a Node
 * @param const Item& it: The Item to check the Node for
 * precondition: Node must exist
 * @return: A boolean indicating whether or not the
 * 			Item was found in the Node
 * @author: Duncan Van Keulen (lab)
 */
template <class Item>
bool BST<Item>::Node::nodeContains(const Item& it) const {
	if ( it == myItem ) { return true; }
	else if ( it < myItem ) {
		if ( myLeft == NULL ) { return false; }
		else {
			myLeft->nodeContains(it);
		}
	}
	else if ( it > myItem ) {
		if ( myRight == NULL ) { return false; }
		else {
			myRight->nodeContains(it);
		}
	}
}

/* Get the height of the tree
 * precondition: tree must have a root node
 * @return the height of the tree
 * @author: Duncan Van Keulen (project)
 */
template <class Item>
unsigned BST<Item>::getHeight() const { // @suppress("No return")
	unsigned myLeftHeight;
	unsigned myRightHeight;

	if ( isEmpty() ) { return 0; }
	else if ( myRoot->myLeft == NULL && myRoot->myRight == NULL ) {
		return 1;
	}

	// if there is a left node, start recursing left to find the height
	if ( myRoot->myLeft != NULL ) {
		myLeftHeight = myRoot->myLeft->nodeGetHeight();
	}
	// if there is a right node, start recursing right to find the height
	if ( myRoot->myRight != NULL ) {
		myRightHeight = myRoot-> myRight->nodeGetHeight();
	}

	// return the greater of the two heights
	if ( myLeftHeight == myRightHeight ) { return myLeftHeight + 1; }
	else if ( myLeftHeight > myRightHeight ) { return myLeftHeight + 1; }
	else if ( myLeftHeight < myRightHeight ) { return myRightHeight + 1; }
}

/* Get the height of a node
 * precondition: node must exist
 * @returns: recursively returns how many nodes are below the current node
 * @author: Duncan Van Keulen (project)
 */
template <class Item>
unsigned BST<Item>::Node::nodeGetHeight() const {
	unsigned myLeftHeight = 0;
	unsigned myRightHeight = 0;

	if ( myLeft == NULL && myRight == NULL ) { return 1; } // base case

	// recurse left
	if ( myLeft != NULL ) {
		myLeftHeight = myLeftHeight + myLeft->nodeGetHeight();
	}
	// recurse right
	if ( myRight != NULL ) {
		myRightHeight = myRightHeight + myRight->nodeGetHeight();
	}
	// return the greater of the two values
	if ( myLeftHeight == myRightHeight ) { return myLeftHeight + 1; }
	else if ( myLeftHeight > myRightHeight ) { return myLeftHeight + 1; }
	else if ( myLeftHeight < myRightHeight ) { return myRightHeight + 1; }
}


#endif /*BST_H_*/

