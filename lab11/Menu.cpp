/* Menu.cpp defines the Menu class operations.
 * Joel Adams, for CS 112 at Calvin College.
 *
 * Student: Duncan Van Keulen (djv78)
 */
 
 #include "Menu.h"

char Menu::QUIT = 'q';

/* constructor
 * Postcondition: myValue contains my menu &&
 *                 myValidChoices contains my choices
 */
Menu::Menu() {
   // initialize myValue
   myValue = "Please choose one of the following items:";
   myValue += "\n a - Add new user+password";
   myValue += "\n b - Change a user's user-name";
   myValue += "\n c - Change a user's password";
   myValue += "\n d - delete user+password";
   myValue += "\n q - quit";
   myValue += "\n --> ";\

   // initialize myValideChoices
   myValidChoices.insert('a');
   myValidChoices.insert('b');
   myValidChoices.insert('c');
   myValidChoices.insert('d');
   myValidChoices.insert('q');
}

/* get string representation of my menu.
 * Postcondition: return-value == myValue.
 */
string Menu::asString() const {
	return myValue;	
}

/* output method
 * Parameters: out, an ostream.
 * Precondition: out.good()
 * Postcondition: out contains my menu.
 */
void Menu::print(ostream& out) const {
	out << asString();
}

/* convenience method
 * Parameters: choice, a char.
 * Postcondition: return-value == true 
 *                 iff choice is an element of myValidChoices.
 */
bool Menu::containsChoice(char choice) const {
	return ( myValidChoices.find(choice) != myValidChoices.end() );
}

