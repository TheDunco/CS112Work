/* Experiment0.h declares a class that times the vector subscript operation.
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 * Student name: Duncan Van Keulen
 * Date: 12 March 2019
 */
 
#ifndef EXPERIMENT0_H_
#define EXPERIMENT0_H_

#include "NanoTimer.h"
#include <vector>
using namespace std;

class Experiment0 {
public:
	void run();
	void timeAccessesForVectorOfSize(int size);
	void timeAccessAtIndex(int index);
private:
	enum repetitions {REPS = 5};
	NanoTimer myTimer;
	vector<int> myVector;
};

#endif /*EXPERIMENT0_H_*/
