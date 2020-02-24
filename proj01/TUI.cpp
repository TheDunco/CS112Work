/*
 * TUI.cpp is a Text/Terminal User Interface for the PlayList class
 *
 *  Created on: Feb 9, 2019
 *      Author: Duncan Van Keulen
 */

#include "TUI.h"
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include "Song.h"
#include "PlayList.h"
using namespace std;

PlayList uiPList("UIPlayList.txt");

// constructor for TUI class
TUI::TUI() {
	// initialize quit boolean to false
	quit = false;

	// start the loop
	loop();
}

// simply print the menu
void TUI::printMenu() {
	cout << '\n' << "Please enter: " << endl;
	cout << "  0 - to quit" << endl;
	cout << "  1 - to search the playlist for songs by a given artist" << endl;
	cout << "  2 - to search the playlist for songs from a given year" << endl;
	cout << "  3 - to search the playlist for songs with a given phrase in their title " << endl;
	cout << "  4 - to add a new song to the playlist" << endl;
	cout << "  5 - to remove a song from the playlist" << endl;
	cout << "  6 - to save the playlist" << endl;
}

// method for printing out a vector of songs to the console
void TUI::printResults(vector<Song>& searchResult) const {
	cout << "Results:\n\n" << "----------\n\n";
	for (unsigned i = 0; i < searchResult.size(); i++) {
		cout
		<< searchResult[i].getTitle() << endl
		<< searchResult[i].getArtist() << endl
		<< searchResult[i].getYear() << endl << "\n---\n";
	}
	cout << "----------" << endl;
}

// print out the results of searching by an artist
void TUI::searchByArtistUI() {
	string searchArtist;
	cout << "Enter artist name: " << flush;

	// get input from the user
	getline(cin, searchArtist);

	cout << "Searching for: " << searchArtist << endl;

	// create a vector of Songs as the search result
	vector<Song> searchResult;

	// use the PlayList::searchByArtist method to search for songs that match the user's input
	searchResult = uiPList.searchByArtist(searchArtist);

	// print out the results using TUI::printResults
	this->printResults(searchResult);
}

// print out the results of searching by a year
void TUI::searchByYearUI() {
	unsigned searchYear;

	cout << "Enter year: " << flush;
	// ask user for input
	cin >> searchYear;

	// create a vector of songs for the search result
	vector<Song> searchResult;
	// use the PlayList::searchByYear method to search for songs that match the user's input
	searchResult = uiPList.searchByYear(searchYear);

	// use the TUI::printResults method to print out the results
	this->printResults(searchResult);
}

// print out the results of searching by a phrase in the title
void TUI::searchByTitlePhraseUI() {
	string phrase;

	cout << "Enter phrase: " << flush;
	// get the users input
	getline(cin, phrase);

	// create a vector of songs to store the search result...
	vector<Song> searchResult;
	// ...and assign it the result of searching for the phrase
	searchResult = uiPList.searchByTitlePhrase(phrase);

	// print out those results using the TUI::printResults method
	this->printResults(searchResult);
}

/* Add a new song to the playlist
*  postcondition: a new song should be added to the playlist
*/
void TUI::addNewSongUI() {
	string title;
	string artist;
	unsigned year;

	// get user input for title
	cout << "Enter title: " << flush;
	getline(cin, title);

	// get user input for artist
	cout << "Enter artist: " << flush;
	getline(cin, artist);

	// get user input for year
	cout << "Enter year: " << endl;
	cin >> year;

	// create a song from the users inputs to add to the playlist
	Song plusSong = Song(title, artist, year);
	uiPList.addSong(plusSong);

	cout << "\nSong added successfully!" << endl;
}

/* Remove a song by dynamically asking the user which song
 * 									   they want to remove
 * postcondition: There will be one less song in uiPList
 */
void TUI::removeSongUI() {
	string title;

	// get the users input for the title of the song they want to remove
	cout << "Which song do you want to remove (title)? ";
	getline(cin, title);

	// search for songs with that title
	vector<Song> result = uiPList.searchByTitlePhrase(title);

	/* if there is only one song with that title, remove it and exit
	 * if there are more than one song witht that title,
	 * ask the user which one they want to remove after printing out their options
	 *
	 * (they should enter a number that's the index of the song they want to remove
	 * in the vector starting at 0)
	 */
	if (result.size() >= 2) {
		cout << "Remove which '" << title << "' (0, 1, 2...)?" << endl;

		// print the user's options
		printResults(result);

		// get their input for which one they want to delete/remove from the playlist
		unsigned deleteSelection;
		cin >> deleteSelection;

		// make sure it's possible to delete the selection they made
		if (deleteSelection > result.size()) {
			cout << "Invalid selection";
		}

		// remove the song of their selection selection
		uiPList.removeSong( result[deleteSelection] );

	}

	// if there was no conflict, remove the only song that matches their title query
	else {
		uiPList.removeSong( result[0] );
	}

	cout << "Song removed successfully" << endl;
}

/* Save the playlist state to the file it was created from
 * Postcondition: file will reflect any changes made to the playlist
 */
void TUI::saveUI() {
	uiPList.save();
	cout << "Playlist saved successfully";
}

// Loops though the menu options until the user wants to exit
void TUI::loop(){
	while ( !(quit) ) {
		this->printMenu();

		cin >> choice;
		cin.ignore();

		// exit if choice is zero
		if (choice == 0) {
			break;
		}

		// if choice is 1, call the method for handling choice 1
		else if (choice == 1) {
			cout << "Option 1: Search by artist" << endl;
			searchByArtistUI();
		}

		// if choice is 2, call the method for handling choice 2
		else if (choice == 2) {
			cout << "Option 2: Search by year" << endl;
			searchByYearUI();
		}

		// if choice is 3, call the method for handling choice 3
		else if (choice == 3) {
			cout << "Option 3: Search by title phrase" << endl;
			searchByTitlePhraseUI();
		}

		// if choice is 4, call the method for handling choice 4
		else if (choice == 4) {
			cout << "Option 4: Add new song" << endl;
			addNewSongUI();
		}

		// if choice is 5, call the method for handling choice 5
		else if (choice == 5) {
			cout << "Option 5: Remove song" << endl;
			removeSongUI();
		}

		// if choice is 6, call the method for handling choice 6
		else if (choice == 6) {
			cout << "Option 6: Save playlist" << endl;
			saveUI();
		}
		else {
			cout << "Invalid selection";
		}
	}

	cout << "Goodbye!" << endl;
}
