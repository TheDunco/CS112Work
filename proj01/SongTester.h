/*
 * SongTester.h declares a test-class for class song
 * Student name: Duncan Van Keulen (djv78)
 * Created on: Feb 5, 2019
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 *
 */

#ifndef SONGTESTER_H_
#define SONGTESTER_H_

// prototype declaration of the SongTester class
class SongTester {
public:
	void runTests();
	void testConstructors();
	void testReadFrom();
	void testWriteTo();
	void testEqualityOperator();
};

#endif /* SONGTESTER_H_ */
