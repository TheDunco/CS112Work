/* PlayList.cpp defines the PlayList methods.
*
* Student Name: Duncan Van Keulen
* Date: 7 Feb 2019
* Begun by: Joel Adams, for CS 112 at Calvin College.
*/

#include "PlayList.h"
#include <fstream>		// ifstream
#include <cassert>		// assert()
#include <iostream>
#include <cstring>
using namespace std;

/* PlayList constructor
* @param: fileName, a string
* Precondition: fileName contains the name of a playlist file.
*/
PlayList::PlayList(const string& fileName) {
	pListFileName = fileName;

	// open a stream to the playlist file
	ifstream fin( fileName.c_str() );
	assert( fin.is_open() );

	// read each song and append it to mySongs
	Song s;
	string separator;
	while (true) {
		s.readFrom(fin);
		if ( !fin ) { break; }
		getline(fin, separator);
		mySongs.push_back(s);
	}

	// close the stream
	fin.close();
}

/* Retrieve length of the playlist
* Return: the number of songs in the playlist.
*/
unsigned PlayList::getNumSongs() const {
	return mySongs.size();
}

/* Retrieve the vector of songs that are stored as the playlist
* Return: a vector containing the songs that are in the playlist
*/
vector<Song> PlayList::getSongs() const {
	return mySongs;
}

/* Search by artist
* @param: artist, a string.
* Return: a vector containing all the Songs in mySongs by artist.
*/
vector<Song> PlayList::searchByArtist(const string& artist) const {
	vector<Song> v;

	// iterate through songs in playlist and append the ones that match to vector v
	for (unsigned i = 0; i < mySongs.size(); i++) {
		if ( mySongs[i].getArtist().find(artist) != string::npos ) {
			v.push_back( mySongs[i] );
		}
	}
  return v;
}

/* Search by year
* @param: year, unsigned
* Return: a vector containing all the Songs in mySongs by year.
*/
vector<Song> PlayList::searchByYear(unsigned year) {
	vector<Song> v1;

	// iterate through all songs in playlist and append the ones that match to vector v1
	for (unsigned i = 0; i < mySongs.size(); i++) {
		if ( mySongs[i].getYear() == year ) {
			v1.push_back( mySongs[i] );
		}
	}
	return v1;
}

/* Search a phrase in the title
* @param: phrase, a string
* Return: a vector containing all the Songs in mySongs by title phrase.
*/
vector<Song> PlayList::searchByTitlePhrase(const string& phrase) {
	vector<Song> v2;

	// iterate through all songs in playlist and append the ones that match to vector v2
	for (unsigned i = 0; i < mySongs.size(); i++) {
		if ( mySongs[i].getTitle().find(phrase) != string::npos ) {
			v2.push_back( mySongs[i] );
		}
	}
  return v2;
}

/* Add a song to the playlist
* @param: Song, a Song object
* @param: newSong, a Song object
* postcondition: playlist vector should have one more song
*/
void PlayList::addSong(const Song& newSong) {
	mySongs.push_back(newSong);
}

/* Remove ONLY ONE song from the playlist
* @param: Song, a Song object
* @param: remSong, a Song object
* precondition: to function, the song has to be inside the playlist
* postcondition: playlist vector should have one less song
*/
void PlayList::removeSong(const Song& remSong) {
	// iterate through the songs in mySongs and if remSong matches one, remove it and exit
	for (unsigned i = 0; i < mySongs.size(); i++) {
		if ( mySongs[i] == remSong ) {
			mySongs.erase(mySongs.begin()+i);
			break;
		}
	}
}

/* Save the playlist to the file it was created from
 * precondition: presumably changes have been made to the playlist (but they don't have to be)
 * postcondition: playlist file should be updated by songs added and removed
 */
void PlayList::save() const {
	// open an ofstream object with the filename that was stored when the object was created
	ofstream fout( pListFileName.c_str() );

	// make sure that file is open
    assert( fout.is_open() );

    // iterate through all of the songs in the playlist and write them to the file
	for (unsigned i = 0; i < mySongs.size(); i++) {
		mySongs[i].writeTo(fout);
		fout << '\n';
	}
	fout.close();
}


