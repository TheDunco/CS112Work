/*
 * TUI.h
 * Header file for TUI.cpp file
 *
 *  Created on: Feb 9, 2019
 *      Author: Duncan Van Keulen
 */

#ifndef TUI_H_
#define TUI_H_

#include <string>
#include "PlayList.h"
#include <fstream>
using namespace std;

class TUI {
public:
	TUI();
	void printMenu();
	void loop();
	void searchByArtistUI();
	void searchByYearUI();
	void searchByTitlePhraseUI();
	void addNewSongUI();
	void removeSongUI();
	void saveUI();
	unsigned choice;
	string pListName;
	void printResults(vector<Song>&) const;
private:
	bool quit;
};

#endif /* TUI_H_ */
