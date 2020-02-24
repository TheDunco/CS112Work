/* PlayListTester.cpp defines the PlayList test-methods.
* Student Name: Duncan Van Keulen
* Date: 7 Feb 2019
* Begun by: Joel Adams, for CS 112 at Calvin College.
*/

#include "PlayListTester.h"
#include "PlayList.h"
#include <iostream>
#include <cassert>
#include "Song.h"
#include <fstream>
using namespace std;

// run the PlayList tests
void PlayListTester::runTests() {
  cout << "\nTesting class PlayList..." << endl;
  PlayList pList("testSongs.txt");
  testConstructors();
  testGetNumSongs();
  testGetSongs();
  testSearchByArtist();
  testSearchByYear();
  testSearchByTitlePhrase();
  testAddRemoveSong();
  testSave();
  cout << "All tests passed!" << endl;
}

// test the constructors for the PlayList class
void PlayListTester::testConstructors() {
   cout << "- constructors..." << flush;

   // make sure it created 4 songs
   PlayList pList("testSongs.txt");
   assert( pList.getNumSongs() == 4 );
   cout << " 0 " << flush;

   cout << " Passed!" << endl;
}

void PlayListTester::testGetNumSongs() {
	cout << "- testGetNumSongs()...";
	PlayList pList00("testSongs.txt");

	// make sure it created 4 songs
	assert( pList00.getNumSongs() == 4 );
	cout << " 0 " << flush;

	cout << " Passed!" << endl;
}

void PlayListTester::testGetSongs() {
	cout << "- testGetSongs()..." << flush;
	PlayList pList01("testSongs.txt");

	// make sure the first song has the correct title
	assert( pList01.getSongs()[0].getTitle() == "Call Me Maybe");
	cout << " 0 " << flush;

	// make sure the first song has the correct artist
	assert( pList01.getSongs()[0].getArtist() == "Carly Rae Jepsen" );
	cout << " 1 " << flush;

	// make sure the first song has the correct year
	assert( pList01.getSongs()[0].getYear() == 2012 );
	cout << " 2 " << flush;

	// make sure the second song has the correct artist
	assert( pList01.getSongs()[1].getArtist() == "The Beatles" );
	cout << " 3 " << flush;

	// make sure the second song has the correct title
	assert( pList01.getSongs()[1].getTitle() == "Let It Be" );
	cout << " 4 " << flush;

	// make sure the second song has the correct year
	assert( pList01.getSongs()[1].getYear() == 1967 );
	cout << " 5 " << flush;

	cout << " Passed!" << endl;

}

void PlayListTester::testSearchByArtist() {
   cout << "- testSearchByArtist()... " << flush;

   // load a playlist with test songs
   PlayList pList("testSongs.txt");

   // empty case (0)
   vector<Song> searchResult = pList.searchByArtist("Cream");
   assert( searchResult.size() == 0 );
   cout << " 0 " << flush;

   // case of 1
   searchResult = pList.searchByArtist("Baez");
   assert( searchResult.size() == 1 );
   assert( searchResult[0].getTitle() == "Let It Be" );
   cout << " 1 " << flush;

   // case of 2
   searchResult = pList.searchByArtist("Beatles");
   assert( searchResult.size() == 2 );
   assert( searchResult[0].getTitle() == "Let It Be" );
   assert( searchResult[1].getTitle() == "Penny Lane" );
   cout << " 2 " << flush;

   cout << " Passed!" << endl;
}

void PlayListTester::testSearchByYear() {
	PlayList pList1("testSongs.txt");

	cout << "- testSearchByYear()..." << flush;

	// test with no songs that match (2015)
	vector<Song> yearSearchResult = pList1.searchByYear(2015);
	assert( yearSearchResult.size() == 0);
	cout << " 0 " << flush;

	//test with one song that match/es (2012)
	yearSearchResult = pList1.searchByYear(2012);
	assert( yearSearchResult.size() == 1);
	cout << " 1 " << flush;

	//test with two songs that match (1967)
	yearSearchResult = pList1.searchByYear(1967);
	assert( yearSearchResult.size() == 2);
	cout << " 2 " << flush;

	cout << " Passed!" << endl;
}

void PlayListTester::testSearchByTitlePhrase() {
	PlayList pList2("testSongs.txt");

	cout << "- testSearchByTitlePhrase()..." << flush;

	// test with songs that have no match
	vector<Song> phraseSearchResult = pList2.searchByTitlePhrase("xyz");
	assert( phraseSearchResult.size() == 0 );
	cout << " 0 " << flush;

	// test  with one match
	phraseSearchResult = pList2.searchByTitlePhrase("Call Me");
	assert( phraseSearchResult.size() == 1 );
	cout << " 1 " << flush;

	// test with multiple matches
	phraseSearchResult = pList2.searchByTitlePhrase("Let It Be");
	assert( phraseSearchResult.size() == 2 );
	cout << " 2 " << flush;

	cout << " Passed!" << endl;

}

void PlayListTester::testAddRemoveSong() {
	PlayList pList3("testSongs.txt");

	Song newSong = Song("Killer Queen", "Queen", 1974);

	cout << "- testAddRemoveSong()..." << flush;

	// Test adding a song...
	// add a song to the playlist
	pList3.addSong(newSong);

	// check that there is now 5 songs in the playlist
	assert( pList3.getNumSongs() == 5 );
	cout << " 0 " << flush;

	// check that song 5 (element 4) is the one we just added
	assert( pList3.getSongs()[4].getTitle() == "Killer Queen" );
	cout << " 1 " << flush;

	assert( pList3.getSongs()[4].getArtist() == "Queen" );
	cout << " 2 " << flush;

	assert( pList3.getSongs()[4].getYear() == 1974 );
	cout << " 3 " << flush;

	// Test removing a song...
	// remove a song
	pList3.removeSong(newSong);
	cout << " 4 " << flush;

	// test that there is now 4 songs in the playlist
	assert( pList3.getNumSongs() == 4 );
	cout << " 5 " << flush;

	cout << " Passed!" << endl;
}

void PlayListTester::testSave() const {
	PlayList pList4("saveTesting.txt");

	Song newSong = Song("Killer Queen", "Queen", 1974);

	cout << "- testSave()..." << flush;

	// make a variable of how many songs the playlist starts with
	unsigned initNumSongs = pList4.getNumSongs();
	assert( pList4.getNumSongs() == initNumSongs );
	cout << " 0 " << flush;

	// add a song to the playlist
	pList4.addSong(newSong);
	cout << " 1 " << flush;

	// save the playlist
	pList4.save();

	// make a variable of the new number of songs the playlist should have (+1)
	unsigned newNumSongs = initNumSongs + 1;

	// make a new playlist from the same file of the saved playlist
	PlayList pList5("saveTesting.txt");

	// make sure that playlist has the same number of songs it should have saved with
	assert( pList5.getNumSongs() == newNumSongs );
	cout << " 2 " << flush;

	cout << " Passed!" << endl;

}
