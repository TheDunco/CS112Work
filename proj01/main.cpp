/*
 * main.cpp: Tests the classes in he project
 * Student name: Duncan Van Keulen (djv78)
 * Created on: Feb 5, 2019
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 *
 */

#include "SongTester.h"
#include "PlayListTester.h"
#include "TUI.h"

// run the tests for the song and playlist classes
int main() {
	SongTester sTester;
	sTester.runTests();
	PlayListTester plTester;
	plTester.runTests();
	TUI UI;
}
