/* BST.cpp defines binary search tree methods.
 * Joel Adams, for CS 112 at Calvin College.
 * Student Name: Duncan Van Keulen
 * Date: 23 April 2019
 */
 
#include "BST.h"


BST::BST() {
	myNumItems = 0;
	myRoot = NULL;
}

BST::~BST() {
	delete myRoot;
	myRoot = NULL;
	myNumItems = 0;
}

BST::Node::Node(const Item& it) {
   myItem = it;
   myLeft = NULL;
   myRight = NULL;
}

BST::Node::~Node() {
	delete myLeft;
	delete myRight;
}

bool BST::isEmpty() const {
	return myNumItems == 0;
}

unsigned BST::getNumItems() const {
	return myNumItems;
}


// Traversal methods...

/* Process the item ( in this case, cout it)
 * postcondition: Item will be processed
 */
void BST::Node::processItem() {
		cout << ' ' << myItem;
}

/* BST Preorder Traversal
 * Initiate Node perorder traversal recursion
 */
void BST::traversePreorder() {
	if ( !isEmpty() ) {
		myRoot->traversePreorder();
	}
}

/* Node Preorder Traversal
 * 1. Process Item
 * 2. Recurse left
 * 3. Recurse right
 */
void BST::Node::traversePreorder() {
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
void BST::traversePostorder() {
	if ( !isEmpty() ) {
		myRoot->traversePostorder();
	}
}
/* Node Postorder Traversal
 * 1. Recurse right
 * 2. Recurse left
 * 3. Process Item
 */
void BST::Node::traversePostorder() {
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
void BST::traverseInorder() {
	if ( !isEmpty() ) {
		myRoot->traverseInorder();
	}
}

/* Node Inorder Traversal
 * 1. Recurse left
 * 2. Process Item
 * 3. Recurse right
 */
void BST::Node::traverseInorder() {
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
void BST::insert(const Item& it) {
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
void BST::Node::nodeInsert(const Item& it) {
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
bool BST::contains(const Item& it) const {
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
bool BST::Node::nodeContains(const Item& it) const {
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


