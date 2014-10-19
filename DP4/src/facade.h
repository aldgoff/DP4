/*
 * facade.h
 *
 * Desc: Define a simpler interface to a set of interfaces making them easier to use.
 *
 * Category: Structural
 *
 *  Created on: Mar 8, 2014
 *      Author: aldgoff
 *
 *  URL: http://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Facade
 */

#ifndef FACADE_H_
#define FACADE_H_

namespace legacy {	// Smart house with large, complicated interface.

class Alarm {
public:
	void on() {
		cout << "Alarm on." << endl;
	}
	void off() {
		cout << "Alarm off." << endl;
	}
};

class AC {
public:
	void on() {
		cout << "AC on." << endl;
	}
	void off() {
		cout << "AC off." << endl;
	}
};

class TV {
public:
	void on() {
		cout << "TV on." << endl;
	}
	void off() {
		cout << "TV off." << endl;
	}
};

// ... ad infinitum

}

namespace facade {	// A simpler interface which encapsulates a more complex one.

using namespace legacy;

class Facade {
	Alarm	alarm;
	AC		ac;
	TV		tv;
public:
	void goToWork() {
		alarm.on();
		ac.off();
		tv.off();
		// ...
	}
	void comeHome() {
		alarm.off();
		ac.on();
		tv.on();
		// ...
	}
};

}

#endif /* FACADE_H_ */
