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

namespace facade_legacy {

class Large {
public:
	const char* ego() { return " I'm"; }
	const char* size() { return " lots"; }
};
class Complicated {
public:
	const char* town() { return " Fairbanks"; }
	const char* moola() { return " money"; }
	const char* iq() { return " smarter"; }
	const char* count() { return " thousand"; }
	const char* manufactor() { return " Made"; }
};
class Obtuse {
public:
	const char* item() { return " ice machines"; }
	const char* chiefNerd() { return " Sheldon"; }
};

void demo() {
	cout << "  Large, complicated and obtuse enterprise MIS.\n";
	cout << "  How do I use this monstrosity?\n";

	cout << endl;
}

}

namespace facade_problem {

using namespace facade_legacy;

Complicated comp;	// Unused static variable.

void demo() {
	Obtuse		obtuse;	// Unused local variable.
	Large		large;
	Complicated	complicated;

	Obtuse* ptr = new Obtuse();
	cout << " " << large.ego();
	cout << large.size();
	cout << complicated.iq() << " than";
	cout << " another";
	if(true) {
		Complicated* comp = new Complicated;
		cout << comp->count();
	}
	cout << Complicated().moola() << ".\n";	// Inconsistent use.
	cout << " " << complicated.manufactor();
	cout << ptr->chiefNerd();	// Unnecessary indirection.
	cout << complicated.town();
	cout << Obtuse().item();
	cout << ".\n";

	cout << endl;
}

}

namespace facade_solution {

using namespace facade_legacy;

class FacadeSales {
	Complicated complicated;
	Obtuse		obtuse;
public:
	void close() {
		cout << "  Sales: Another";
		cout << complicated.count() << obtuse.item();
		cout << " for" << complicated.town() << ".\n";
	}
};

class FacadeRnD {
	Large		large;
	Complicated complicated;
	Obtuse		obtuse;
public:
	void patents() {
		cout << "  R&D:  " << large.ego() << complicated.iq();
		cout << " than" << obtuse.chiefNerd() << ".\n";
	}
};

class FacadeCorp {
	Large		large;
	Complicated complicated;
public:
	void bottomLine() {
		cout << "  Corp: " << complicated.manufactor() << large.size();
		cout << " of" << complicated.moola() << ".\n";
	}
};

void demo() {
	FacadeSales	sales;
	FacadeRnD	rnd;
	FacadeCorp	pres;
	sales.close();
	rnd.patents();
	pres.bottomLine();

	cout << endl;
}

}

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
