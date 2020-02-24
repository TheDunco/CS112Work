/* The header file for the BST height experiment
 * Experiment.h
 *
 *  Created on: Apr 27, 2019
 *      Author: Duncan Van Keulen (djv78)
 */

#ifndef EXPERIMENT_H_
#define EXPERIMENT_H_

#include <cstring>
#include <iostream>
#include <cassert>
#include <fstream>
#include <cstdlib>
#include "BST.h"
using namespace std;

class Experiment {
public:
	void setFileName();
	void run();
	void loop();

private:
	string myFile;
	BST<long> myBST;
};

#endif /* EXPERIMENT_H_ */
