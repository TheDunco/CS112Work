/* PlayListTester.h tests the PlayList class.
* Student Name: Duncan Van Keulen
* Date: 7 Feb 2019
* Begun by: Joel Adams, for CS 112 at Calvin College.
*/

#ifndef PLAYLISTTESTER_
#define PLAYLISTTESTER_

#include <string>
using namespace std;

// prototype declaration of the PlayListTester class
class PlayListTester {
public:
   void runTests();
   void testConstructors();
   void testGetNumSongs();
   void testGetSongs();
   void testSearchByArtist();
   void testSearchByYear();
   void testSearchByTitlePhrase();
   void testAddRemoveSong();
   void testSave() const;
};

#endif /*PLAYLISTTESTER_*/
