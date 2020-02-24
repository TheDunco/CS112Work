/*
 * Song.h declares a class for storing song information.
 * Student name: Duncan Van Keulen (djv78)
 * Created on: Feb 5, 2019
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 *
 */

#ifndef SONG_H_
#define SONG_H_

#include <string>
using namespace std;

// prototype declaration of Song class
class Song {
public:
	Song();
	Song(const string& title, const string& artist, unsigned year);
	string getTitle() const;
	string getArtist() const;
	unsigned getYear() const;
	void readFrom(istream& in);
	void writeTo(ostream& out) const;
private:
	string myTitle;
	string myArtist;
	unsigned myYear;
};

#endif /* SONG_H_ */
