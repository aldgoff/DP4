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
 *  URLs:
 *  	http://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Facade
 *  	http://www.dofactory.com/net/facade-design-pattern
 *  	http://www.netobjectives.com/resources/books/design-patterns-explained/review-questions#Chapter6
 *  	http://sourcemaking.com/design_patterns/facade
 */

#ifndef FACADE_H_
#define FACADE_H_

namespace lecture {

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
//	Obtuse		obtuse;	// Unused local variable.
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

}

namespace homework {

/* Consider a smart house.
 * The interface starts simple but it's a hit in the market place,
 * so new features are added, and new clients.
 * However, most clients only utilize a couple of use cases.
 * Refactor with the Facade pattern to simplify the clients' code.
 */

namespace facade_common {

class Alarm {
public:
	void on() {
		cout << "  Alarm on." << endl;
	}
	void off() {
		cout << "  Alarm off." << endl;
	}
};
class AC {
public:
	void on() {
		cout << "  AC on." << endl;
	}
	void off() {
		cout << "  AC off." << endl;
	}
};

}

namespace facade_legacy {	// Smart house with large, complicated interface.

using namespace facade_common;

void client() {
	Alarm	alarm;
	AC		ac;
	// Seam point 1 - insert new device, violates open/closed principle.

	cout << " Leaving...\n";
	alarm.on();
	ac.off();
	// Seam point 2 - insert call to new device, violates open/closed principle.

	cout << " Returning...\n";
	alarm.off();
	ac.on();
	// Seam point 3 - insert call to new device, violates open/closed principle.
}

void demo() {
	client();

	cout << endl;
}

}

namespace facade_new_specs {

class TV {
public:
	void on() {
		cout << "  TV on." << endl;
	}
	void off() {
		cout << "  TV off." << endl;
	}
};
class Lights {
public:
	void on() {
		cout << "  Lights on." << endl;
	}
	void off() {
		cout << "  Lights off." << endl;
	}
};
// ... ad infinitum

}

namespace facade_problem {	// Have to change client code in multiple places.

using namespace facade_common;
using namespace facade_new_specs;

void client1() {
	Alarm	alarm;
	AC		ac;
	TV		tv;
	Lights	lights;
	// Seam point 1 - insert new device, violates open/closed principle.

	cout << " Leaving...\n";
	alarm.on();
	ac.off();
	tv.off();
	lights.off();
	// Seam point 2 - insert call to new device, violates open/closed principle.

	cout << " Returning...\n";
	alarm.off();
	ac.on();
	tv.on();
	lights.on();
	// Seam point 3 - insert call to new device, violates open/closed principle.
}

void client2() {
	Alarm	alarm;
	AC		ac;
	TV		tv;
	Lights	lights;
	// Seam point 1 - insert new device, violates open/closed principle.

	cout << " Leaving...\n";
	alarm.on();
	ac.off();
	tv.off();
	lights.off();
	// Seam point 2 - insert call to new device, violates open/closed principle.

	cout << " Returning...\n";
	alarm.off();
	ac.on();
	tv.on();
	lights.on();
	// Seam point 3 - insert call to new device, violates open/closed principle.
}

void client3() {
	Alarm	alarm;
	AC		ac;
	TV		tv;
	Lights	lights;
	// Seam point 1 - insert new device, violates open/closed principle.

	cout << " Leaving...\n";
	alarm.on();
	ac.off();
	tv.off();
	lights.off();
	// Seam point 2 - insert call to new device, violates open/closed principle.

	cout << " Returning...\n";
	alarm.off();
	ac.on();
	tv.on();
	lights.on();
	// Seam point 3 - insert call to new device, violates open/closed principle.
}

void demo() {
	client1();	cout << endl;
	client2();	cout << endl;
	client3();	cout << endl;
}

}

namespace facade_solution {	// Simpler interface encapsulates more complex one.

using namespace facade_common;
using namespace facade_new_specs;

class Facade {
	Alarm	alarm;
	AC		ac;
	TV		tv;
	Lights	lights;
	// Seam point 1 - insert new device, violates open/closed principle.
public:	// Use cases.
	void goToWork() {
		cout << " Leaving...\n";
		alarm.on();
		ac.off();
		tv.off();
		lights.off();
		// Seam point 2 - insert call to new device, violates open/closed principle.
	}
	void comeHome() {
		cout << " Returning...\n";
		alarm.off();
		ac.on();
		tv.on();
		lights.on();
		// Seam point 3 - insert call to new device, violates open/closed principle.
	}
};

void client1() {
	Facade house;
	house.goToWork();
	house.comeHome();
}

void client2() {
	Facade house;
	house.goToWork();
	house.comeHome();
}

void client3() {
	Facade house;
	house.goToWork();
	house.comeHome();
}

void demo() {
	client1();	cout << endl;
	client2();	cout << endl;
	client3();	cout << endl;
}

}

}

#endif /* FACADE_H_ */
