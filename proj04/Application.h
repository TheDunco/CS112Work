/*
 * Application.h
 *
 *  Created on: Mar 4, 2019
 *      Author: Ben Brower (bpb9)
 *      Author: Duncan Van Keulen (djv78)
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_
#include "Matrix.h"
#include <iostream>
#include <cstdlib>
namespace std {

class Application {
public:
	void Menu();
	void addMatrices();
	void subtractMatrices();
	void transposeMatrices();
	virtual ~Application();
};

} /* namespace std */

#endif /* APPLICATION_H_ */
