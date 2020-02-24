/* PlayList.h declares class PlayList.
* Student Name: Duncan Van Keulen
* Date: 7 Feb 2019
* Begun by: Joel Adams, for CS 112 at Calvin College.
*/

#ifndef PLAYLIST_H_
#define PLAYLIST_H_

#include "Song.h"
#include <vector>   // STL vector
#include <string>
using namespace std;

// prototype declaration of the PlayList class
class PlayList {
public:
  PlayList(const string& fileName);
  unsigned getNumSongs() const;
  vector<Song> getSongs() const;
  void save() const;

  // search functions
  vector<Song> searchByArtist(const string& artist) const;
  vector<Song> searchByYear(unsigned year);
  vector<Song> searchByTitlePhrase(const string& phrase);

  // mutators
  void addSong(const Song& newSong);
  void removeSong(const Song& remSong);
private:
  vector<Song> mySongs;
  string pListFileName;
};

#endif /*PLAYLIST_H_*/
