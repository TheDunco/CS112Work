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
  vector<Song> searchByArtist(const string& artist) const;
private:
  vector<Song> mySongs;
};

#endif /*PLAYLIST_H_*/
