/*
 * ReversePoem.cpp is the implementation of the ReversePoem class
 *
 *  Created on: Mar 31, 2019
 *      Author: Duncan Van Keulen (djv78)
 */

#include "ReversePoem.h"

/*
 * ReversePoem constructor
 * @param const string& filename: The name of the file for the
 * 							       poem to be constructed from
 * precondition: Creation file has to exist
 * postcondition: Title, author, body, and reverseBody will be
 * 				  filled with the appropriate information from the file
 * @author: Duncan Van Keulen (djv78)
 */
ReversePoem::ReversePoem(const string& filename) {
	// open the file and make sure it's open
	ifstream fin( filename.c_str() );
	assert( fin.is_open() );

	// get and store the title and author
	getline(fin, title);
	getline(fin, author);

	// compensate for the empty line
	string nada;
	getline(fin, nada);

	// initialize a stack for the body and temporary line variable
	Stack<string> bodyStack(2);
	string line;

	// loop until fin reaches eof
	while(fin) {
		getline(fin, line);

		/* Try to push the the line to bodyStack.
		 * If the capacity is not enough, double capacity and continue
		 */
		try {
			bodyStack.push(line);
		} catch (const StackException& se) {
			bodyStack.setCapacity( (bodyStack.getCapacity() * 2) );
			bodyStack.push(line);
		}

		// append the next line to the body string
		body.append(line);
		body.append( "\n");
	}
	fin.close();

	// pop() the bodyStack to store in reversed body string variable
	while( !bodyStack.isEmpty() ) {
		reverseBody.append( bodyStack.pop() );
		reverseBody.append( "\n" );
	}
}

