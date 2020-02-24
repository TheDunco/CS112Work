/* tester.cpp is the driver file for the BST class
 */
#include "BST_Tester.h"
#include "Experiment.h"

int main() {
	BST_Tester bstt;
	bstt.runTests();	

	Experiment exp;
	exp.loop();
}
