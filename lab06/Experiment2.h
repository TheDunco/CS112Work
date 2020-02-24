/* Experiment2.h declares a class that times the vector and list prepend operations.
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 * Student name: Duncan Van Keulen
 * Date: 12 March 2019
 */
#ifndef EXPERIMENT2_H_
#define EXPERIMENT2_H_

#include "NanoTimer.h"

class Experiment2 {
public:
	void run();
	void timePrependToVectorOfSize(unsigned size);	
	void timeRepeatedPrependUntilVectorIsSize(unsigned maxSize);
	void timePrependToListOfSize(unsigned size);
	void timeRepeatedPrependUntilListIsSize(unsigned maxSize);

private:
	enum repetitions {REPS = 5};
	NanoTimer myTimer;
};

#endif /*EXPERIMENT2_H_*/
