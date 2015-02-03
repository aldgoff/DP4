/*
 * strategy.cpp
 *
 *  Created on: Feb 2, 2015
 *      Author: aldgoff
 */

#include <iostream>
using namespace std;

#define COUNT(x) (sizeof(x)/sizeof(*x))

namespace skeleton {

class Strategy {		// If the algorithms are varying...
public:	virtual ~Strategy() {}
public:
	virtual void compute() {}
};

class Algorithm1 : public Strategy {
public:
	void compute() { cout << "  Algorithm1\n"; }
};
class Algorithm2 : public Strategy {
public:
	void compute() { cout << "  Algorithm2\n"; }
};
class Algorithm3 : public Strategy {
public:
	void compute() { cout << "  Algorithm3\n"; }
};

void clientStrategy() {
	cout << "Strategy\n";
	Strategy* algorithms[] = { new Algorithm1, new Algorithm2, new Algorithm3 };
	for(size_t i=0; i<COUNT(algorithms); i++) {
		algorithms[i]->compute();
	}
	cout << endl;
}

}
