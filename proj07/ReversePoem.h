/*
 * ReversePoem.h is the header file of the ReversePoem class.
 *
 *  Created on: Mar 31, 2019
 *      Author: Duncan Van Keulen
 */

#ifndef REVERSEPOEM_H_
#define REVERSEPOEM_H_

#include "Stack.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
using namespace std;

class ReversePoem {
public:
	ReversePoem(const string& filename);
	string getTitle() { return title; }
	string getAuthor() { return author; }
	string getBody() { return body; }
	string getBodyReversed() { return reverseBody; }
private:
	string title;
	string author;
	string body;
	string reverseBody;

	friend class ReversePoemTester;
};

#endif /* REVERSEPOEM_H_ */
