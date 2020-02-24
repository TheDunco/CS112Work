/*
 * List.h
 *
 *  Created on: Mar 5, 2019
 *      Author: Duncan Van Keulen (djv78)
 */

#ifndef LIST_H_
#define LIST_H_

#include <iostream>
#include <stdexcept>
using namespace std;

typedef double Item;

class List {
public:
	List();
	List(const List& original);
	List& operator=(const List& original);
	void append(const Item& item);
	virtual ~List();
	unsigned getSize() const { return mySize; }
	Item getFirst() const;
	Item getLast() const;
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


#endif /* LIST_H_ */
