/* manageUserAccounts.cpp contains the "driver" for class AccountManager.
 * Joel Adams, for CS 112 at Calvin College.
 *
 * Student: Duncan Van Keulen (djv78)
 */

#include "AccountManager.h"

int main() {
	AccountManager manager("accountInfo.txt");
	manager.run();
}
