/*
 * facade.cpp
 *
 *  Created on: Feb 2, 2015
 *      Author: aldgoff
 */

#include <iostream>
using namespace std;

namespace skeleton {

class LegacyClassA {};
class LegacyClassB {};
class LegacyClassC {};
//...
class LegacyClassZ {};

class Facade {			// If the API's are varying...
protected:
	LegacyClassA	legacyClassA;
	LegacyClassB	legacyClassB;
	LegacyClassC	legacyClassC;
	// ...
	LegacyClassZ	legacyClassZ;
};

class API1 : public Facade {
public:
	void simpleAPI1() { cout << "  simpleAPI1\n"; }
	// ...
	void easyAPI1() { cout << "  easyAPI1\n"; }
};
class API2 : public Facade {
public:
	void simpleAPI2() { cout << "  simpleAPI2\n"; }
	// ...
	void easyAPI2() { cout << "  easyAPI2\n"; }
};
class API3 : public Facade {
public:
	void simpleAPI3() { cout << "  simpleAPI3\n"; }
	// ...
	void easyAPI3() { cout << "  easyAPI3\n"; }
};

void clientFacade() {
	API1 facade1;	facade1.simpleAPI1();
					facade1.easyAPI1();
	API2 facade2;	facade2.simpleAPI2();
					facade2.easyAPI2();
	API3 facade3;	facade3.simpleAPI3();
					facade3.easyAPI3();
	cout << endl;
}

}
